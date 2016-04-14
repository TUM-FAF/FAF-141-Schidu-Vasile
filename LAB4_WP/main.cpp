#include <windows.h>
#include <time.h>
#include <thread>
#include <c++/iostream>
#include <vector>


#define WIDTH 1000
#define HEIGTH 600
#define DELTA 2

#define TIMER_ID 1


class Figure {
public :
    int width;
    int heigth;
    int x;
    int y;
    int r, g, b;
    bool circle = true;
    int dir;
    int velocity;

public:
    Figure(int x, int y, int width, int height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->heigth = height;
    }
    void setDimension(int width, int height) {
        this->width = width;
        this->heigth = height;
    }

    void setColor(int r, int g, int b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    int getHeight() {
        return this->heigth;
    }

    int getWidth() {
        return this->width;
    }

    void setPosition(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int getX() {
        return this->x;
    }

    int getY() {
        return this->y;
    }


    int getR() {
        return this->r;
    }

    int getG() {
        return this->g;
    }

    int getB() {
        return this->b;
    }

    void setCircle(bool circle) {
        this->circle = circle;
    }


    void setDir(int dir) {
        this->dir = dir;
    }

    int getDir() {
        return this->dir;
    }

    void collision(int width, int height) {
        bool collision = false;
        if(y <= 0) {
            switch(dir) {
                case 2:
                    dir = 0;
                    break;
                case 3:
                    dir = 1;
                    break;
            }
        }

        if(x <= 0) {
            switch(dir) {
                case 3:
                    dir = 2;
                    break;
                case 1:
                    dir = 0;
                    break;
            }
            if (circle){
                circle = false;
            }
            else{
                circle = true;
            }
        }

        if(x + this->width >= width ) {
            switch(dir) {
                case 0:
                    dir = 1;
                    break;
                case 2:
                    dir = 3;
                    break;
            }
            circle ? circle = false : circle = true;
        }

        if(y + this->heigth >= height) {
            switch(dir) {
                case 1:
                    dir = 3;
                    break;
                case 0:
                    dir = 2;
                    break;
            }
        }
    }


    bool trueCollision(int X, int Y) {
        bool collision = false;
        if(y <= Y + heigth && y > Y && x <= X + width && x >= X  ) {
            collision = true;
        }
        return collision;
    }

    void setVelocity(int velocity) {
        this->velocity = velocity;
    }

    int getVelocity() {
        return this->velocity;
    }

    bool trueCircle() {
        return this->circle;
    }
};

static PAINTSTRUCT ps;
static HDC hdc;
static RECT rect;
static HBRUSH hBrush;
int vectorSize = 5;
int velocity = 0;

int x, y;

std::vector<Figure> vec;

RECT rc;
HDC hdcMem;
HBITMAP hbmMem, hbmOld;
HBRUSH hbrBkGnd;
HFONT hfntOld;

void initFigures() {

    srand(time(NULL));
    Figure *figure;
    for(int i = 0; i < vectorSize; i++) {
        figure = new Figure(rand()%rect.right, rand()%rect.bottom, 50, 50);
        figure->setCircle(false);
        figure->setDir(rand()%4);
        figure->setVelocity(rand()%1 + 1);
        figure->setColor(rand()%250, rand()%250, rand()%250);
        figure->setCircle(true);
        vec.push_back(*figure);
    }
}

static void Paint(HWND hWnd, LPPAINTSTRUCT lpPS) {

    GetClientRect(hWnd, &rc);

    hdcMem = CreateCompatibleDC(lpPS->hdc);
    hbmMem = CreateCompatibleBitmap(lpPS->hdc, rc.right-rc.left, rc.bottom-rc.top);
    hbmOld = (HBITMAP) SelectObject(hdcMem, hbmMem);
    hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));

    FillRect(hdcMem, &rc, hbrBkGnd);

    for(int i = 0; i < vectorSize; i++){
        x = vec[i].getX();
        y = vec[i].getY();
        hbrBkGnd = CreateSolidBrush(RGB(vec[i].getR(), vec[i].getG(), vec[i].getB()));
        SelectObject(hdcMem, hbrBkGnd);


        for(int j = 0; j < vectorSize; j++){
            if(j != i){
                if(vec[i].trueCollision(vec[j].getX(), vec[j].getY())){
                    vec[i].setColor(rand()%250, rand()%250, rand()%250);
                    vec[j].setColor(rand()%250, rand()%250, rand()%250);

                }
            }
        }

        vec[i].collision(rect.right, rect.bottom);


        switch(vec[i].getDir()) {
            case 0:
                x += vec[i].getVelocity() + velocity;
                y += vec[i].getVelocity() + velocity;
                break;
            case 1:
                x -= vec[i].getVelocity() + velocity;
                y += vec[i].getVelocity() + velocity;
                break;
            case 2:
                x += vec[i].getVelocity() + velocity;
                y -= vec[i].getVelocity() + velocity;
                break;
            case 3:
                x -= vec[i].getVelocity() + velocity;
                y -= vec[i].getVelocity() + velocity;
                break;
        }

        vec[i].setPosition(x, y);
        if(vec[i].trueCircle()){
            Ellipse(hdcMem, vec[i].getX(), vec[i].getY(), vec[i].getX() + vec[i].getWidth(),
                    vec[i].getY() + vec[i].getHeight());
        }else{
            Rectangle(hdcMem, vec[i].getX(), vec[i].getY(), vec[i].getX() + vec[i].getWidth(),
                      vec[i].getY() + vec[i].getHeight());
        }
    }
    DeleteObject(hbrBkGnd);
    SetBkMode(hdcMem, BACKGROUND_BLUE);
    SetTextColor(hdcMem, GetSysColor(COLOR_WINDOWTEXT));


    if (hfntOld) {
        SelectObject(hdcMem, hfntOld);
    }

    BitBlt(lpPS->hdc, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, hdcMem, 0, 0, SRCCOPY);

    SelectObject(hdcMem, hbmOld);
    DeleteObject(hbmMem);
    DeleteDC(hdcMem);

}


LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd) {
    WNDCLASSEX wClass;
    ZeroMemory(&wClass, sizeof(WNDCLASSEX));
    wClass.cbClsExtra = NULL;
    wClass.cbSize = sizeof(WNDCLASSEX);
    wClass.cbWndExtra = NULL;
    wClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wClass.hCursor = LoadCursor(NULL, IDC_ICON);
    wClass.hIcon = LoadIcon(NULL, IDC_ICON);
    wClass.hIconSm = LoadIcon(NULL, IDC_ICON);
    wClass.hInstance = hInst;
    wClass.lpfnWndProc = (WNDPROC) WinProc;
    wClass.lpszClassName = "Window Class";
    wClass.lpszMenuName = NULL;
    wClass.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassEx(&wClass)) {
        int nResult = GetLastError();
        MessageBox(NULL,
                   "Window class creation failed\r\n",
                   "Window Class Failed",
                   MB_ICONERROR);
    }

    HWND hWnd;
    hWnd = CreateWindowEx(NULL,
                          "Window Class",
                          "Lab #4 WP | Schidu Vasile",
                          WS_OVERLAPPEDWINDOW,
                          200,
                          200,
                          WIDTH,
                          HEIGTH,
                          NULL,
                          NULL,
                          hInst,
                          NULL);


    if (!hWnd) {
        int nResult = GetLastError();

        MessageBox(NULL,
                   "Window creation failed\r\n",
                   "Window Creation Failed",
                   MB_ICONERROR);
    }

    ShowWindow(hWnd, nShowCmd);

    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {

        case WM_CREATE: {
            hdc = GetDC(hWnd);
            GetClientRect(hWnd,&rect);
            int ret = SetTimer(hWnd, TIMER_ID, 5, NULL);
            initFigures();
            break;
        }

        case WM_PAINT: {
            BeginPaint(hWnd, &ps);
            Paint(hWnd, &ps);
            EndPaint(hWnd, &ps);

        }
            break;


        case WM_LBUTTONDOWN: {
            Figure *figure;
            figure = new Figure(rand()%rect.right, rand()%rect.bottom, 100, 100);
            figure->setCircle(false);
            figure->setDir(rand()%4);
            figure->setVelocity(rand()%8 + 1);
            figure->setColor(rand()%250, rand()%250, rand()%250);
            vec.push_back(*figure);
            vectorSize++;
            break;
        }

        case WM_MOUSEWHEEL : {
            int deltaZ = (short) HIWORD(wParam);
            if(deltaZ > 0) {
                velocity += 2;
            }else {
                if(velocity > 0)
                    velocity -= 2;
            }
            break;
        }

        case WM_TIMER: {
            InvalidateRect(hWnd, &rect, FALSE);
        }
            break;

        case WM_DESTROY: {
            KillTimer(hWnd, TIMER_ID);
            PostQuitMessage(0);
            return 0;
        }

    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
