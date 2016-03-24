#include <windows.h>
#include "ClassButton.h"
#include "TextEdit.h"

#include <time.h>
#include <stdlib.h>
#include <c++/iostream>
#include <thread>
#include <windowsx.h>
#define BKGRND_BTN 3
#define BUTTON_1    1
#define IDC_EDIT_1    11
#define BUTTON_3   3
#define BUTTON_2   2

#define IDC_EDIT_2    22

#define WIDTH 400
#define HEIGTH 600

HWND hEdit;
ClassButton *button;
ClassButton *button1;
ClassButton *button2;
TextEdit *editText1;
TextEdit *editText2;
RECT rect;
int r, g, b;





LPSTR TextArray[] = {
        "I move as you resize the window"
};



LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);



int GetTextSize(LPSTR a0) {
    for (int iLoopCounter = 0; ; iLoopCounter++) {
        if (a0[iLoopCounter] == '\0')
            return iLoopCounter;
    }
}


void generateColor(){
    r = rand() % 250 + 1;
    g = rand() % 250 + 1;
    b = rand() % 250 + 1;

}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd) {
    WNDCLASSEX wClass;
    ZeroMemory(&wClass, sizeof(WNDCLASSEX));
    wClass.cbClsExtra = NULL;
    wClass.cbSize = sizeof(WNDCLASSEX);
    wClass.cbWndExtra = NULL;
    wClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wClass.hIcon = NULL;
    wClass.hIconSm = NULL;
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

    HWND hWnd = CreateWindowEx(NULL,
                               "Window Class",
                               "Windows application",
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
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            GetWindowRect(hWnd, &rect);
            TextOut(hdc,
                    rect.right / 2 - GetTextSize(TextArray[0]) * 5,
                    rect.bottom / 2 - GetTextSize(TextArray[0]) * 2,
                    TextArray[0],
                    GetTextSize(TextArray[0]));
            EndPaint(hWnd, &ps);
        }
            break;

        case WM_CREATE: {

            srand(time(NULL));
            generateColor();

            button = new ClassButton("Close Application", 150,400, 300, 40, hWnd, BUTTON_1);
            button2 = new ClassButton("Change Box Color", 150, 30, 300, 40, hWnd, BUTTON_2);

            editText1 = new TextEdit("", 150, 130, 300, 40, hWnd, IDC_EDIT_1);
            editText2 = new TextEdit("", 150, 80, 300, 40, hWnd, IDC_EDIT_2);
            editText2->setFont();
            button2->setFont();
        }
            break;

        case WM_GETMINMAXINFO:{
            MINMAXINFO *mmi = (MINMAXINFO*) lParam;
            mmi->ptMinTrackSize.x = 600;
            mmi->ptMaxTrackSize.x = 900;
            mmi->ptMinTrackSize.y = 400;
            mmi->ptMaxTrackSize.y = 900;
            return 0;
        }


        case WM_CTLCOLORSTATIC:{
            RECT crect;
            HBRUSH brush;
            COLORREF background_color = RGB(255,0,0);
            HDC hdc = (HDC) BUTTON_2;
            HWND button_handle = (HWND) BUTTON_2;

            GetClientRect(button_handle,&crect);
            SetBkColor(hdc,background_color);
            SetTextColor(hdc,RGB(255,255,255));
            brush = CreateSolidBrush(background_color);

            return (HRESULT) brush;
        }



        case WM_CTLCOLOREDIT: {

            HDC hdcStatic = (HDC) wParam;
            if (GetDlgItem(hWnd, IDC_EDIT_2) == (HWND) lParam) {
                SetTextColor(hdcStatic, RGB(255, 250, 255));
                SetBkColor(hdcStatic, RGB(r, g, b));
                return (LRESULT) CreateSolidBrush(RGB(r, g, b));
            }
        }



        case WM_COMMAND:
            switch (wParam) {

                case BUTTON_2 : {
                    generateColor();
                    HDC hdc;
                    SendMessage(hWnd, WM_CTLCOLOREDIT, (WPARAM) hdc, (LPARAM) BUTTON_2);
                    InvalidateRect(hWnd, NULL, true);
                    return 0;
                }

                case BUTTON_1 : {
                    ::MessageBeep(MB_ICONERROR);
                    ::MessageBox(hWnd, "So soon ? :/", "Exit", MB_OK);
                    PostQuitMessage(0);
                    break;
                }

            }
            break;


        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }


    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}