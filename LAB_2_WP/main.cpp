#include <windows.h>
#include <stdio.h>


#define BUTTON_ADD_TODO         101
#define BUTTON_DISPLAY_TODO_NR  102
#define INPUT_TEXT_SHOW_TODO    103
#define INPUT_TEXT_ADD_TODO     104
#define IDR_MYMENU 101
#define IDI_MYICON 201

#define ID_FILE_EXIT 9001
#define ID_STUFF_ABOUT 9002
#define ID_EVENT_RED 9003
#define ID_EVENT_GREEN 9004
#define ID_EVENT_BLUE 9005
#define ID_SCROLL_BAR 9006
#define IDC_TODO_LIST  9007
#define IDI_ICON 9008
#define ID_WIDTH_SCROLL 9009
#define ID_HEIGHT_SCROLL 9010
#define IDS_TODONUMBER 9011
#define ID_ACCELERATOR 9431


LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HWND hTODOList;
HWND hInputTODO;
char TODO[500] = "";
char firstText[] = "Ho-ho-ho! My color is chenging!";
int TODONumber = 0;
static int scrollColor = 0;
static int widthScroll = 0;
static int heightScroll = 40;
HINSTANCE hInstance;
static int fontColor[3];





int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR lpCmdLine,int nShowCmd) {

        hInstance = hInst;

        WNDCLASSEX wClass;

        wClass.hInstance = hInst;
        wClass.lpszClassName = "Window Class";
        wClass.lpfnWndProc = (WNDPROC)WinProc;
        wClass.style = CS_HREDRAW|CS_VREDRAW;
        wClass.cbSize = sizeof(WNDCLASSEX);
        wClass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
        wClass.hCursor = LoadCursor(NULL, IDC_HAND);
        wClass.hIconSm = NULL;
        wClass.lpszMenuName  = MAKEINTRESOURCE(IDR_MYMENU);
        wClass.hIcon  = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
        wClass.cbClsExtra = 0;
        wClass.cbWndExtra = 0;

        HMENU hmenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MYMENU));

        wClass.lpszMenuName = NULL;



        if (!RegisterClassEx(&wClass)) {
                GetLastError();
                MessageBox(NULL,
                           "Window class creation failed\r\n",
                           "Window Class Failed",
                           MB_ICONERROR);
        }

        HWND hWnd=CreateWindowEx(NULL,
                                 "Window Class",
                                 "Laboratory Work #2 | Schidu Vasile",
                                 WS_OVERLAPPEDWINDOW,
                                 100,
                                 100,
                                 300,
                                 400,
                                 NULL,
                                 hmenu,
                                 hInst,
                                 NULL);



        if(!hWnd) {
                GetLastError();

                MessageBox(NULL,
                           "Window creation failed\r\n",
                           "Window Creation Failed",
                           MB_ICONERROR);
        }

        ShowWindow(hWnd,nShowCmd);

        MSG msg;
        //ZeroMemory(&msg,sizeof(MSG));




        while (GetMessage (&msg, NULL, 0, 0)) {
                TranslateMessage (&msg) ;
                DispatchMessage (&msg) ;
                //}
        }

        while(GetMessage(&msg,NULL,0,0)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
        }

        return 0;

}

LRESULT CALLBACK WinProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam) {
        PAINTSTRUCT Ps;
        static HWND hWndList;
        static HWND hWndScroll, hWndWidthScroll, hWndHeightScroll;
        static RECT rcScroll, rcTODOList, rcInputTODO, rcQuantity;
        HBRUSH hBrushStatic;



        SetRect(&rcScroll, 315, 40, 25, 150);
        SetRect(&rcTODOList, 10, 10, 300, 40);
        SetRect(&rcInputTODO, 120, 150, 190, 25);
        SetRect(&rcQuantity, 210, 10, 300, 30);


        switch(msg) {
                case WM_CREATE: {

                        hWndScroll = CreateWindowEx((DWORD)NULL,
                                                    TEXT("scrollbar"),
                                                    NULL,
                                                    WS_CHILD | WS_VISIBLE | SBS_VERT,
                                                    10, 35, 300, 100,
                                                    hWnd,
                                                    (HMENU) ID_SCROLL_BAR,
                                                    hInstance,
                                                    NULL);
                        SetScrollRange(hWndScroll,SB_CTL, 0, 255, FALSE);
                        SetScrollPos(hWndScroll, SB_CTL, 0, TRUE);



                        hWndList = CreateWindowEx((DWORD)NULL,
                                                  TEXT("listbox"),
                                                  "",
                                                  WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | LBS_STANDARD | WS_BORDER,
                                                  10, 150,
                                                  300, 100,
                                                  hWnd,
                                                  (HMENU) IDC_TODO_LIST,
                                                  hInstance,
                                                  NULL);



                        HWND hButtonAddTODO = CreateWindowEx(NULL,
                                                             "BUTTON",
                                                             "Add a task",
                                                             WS_TABSTOP|WS_VISIBLE|
                                                             WS_CHILD|BS_DEFPUSHBUTTON|BS_TOP,
                                                             10,
                                                             260,
                                                             100,
                                                             25,
                                                             hWnd,
                                                             (HMENU)BUTTON_ADD_TODO,
                                                             GetModuleHandle(NULL),
                                                             NULL);

                        HWND hShowTODONumber = CreateWindowEx(NULL,
                                                              "BUTTON",
                                                              "Exit",
                                                              WS_VISIBLE | WS_CHILD,
                                                              10,
                                                              290,
                                                              300,
                                                              40,
                                                              hWnd,
                                                              (HMENU)BUTTON_DISPLAY_TODO_NR,
                                                              NULL,
                                                              NULL);
                        hInputTODO = CreateWindowEx(
                                (DWORD)NULL,
                                TEXT("edit"),
                                "",
                                WS_VISIBLE | WS_CHILD | WS_BORDER,
                                120,
                                260,
                                190,
                                25,
                                hWnd,
                                (HMENU)INPUT_TEXT_ADD_TODO,
                                GetModuleHandle(NULL),
                                NULL);

                }
                break;

                case WM_PAINT: {
                        HDC hdc = BeginPaint(hWnd, &Ps);

                        char TODONrMessage[40];
                        char nr[50];
                        LoadString (hInstance, IDS_TODONUMBER, TODONrMessage, 40) ;
                        wsprintf (nr, TODONrMessage, TODONumber);

                        SetBkMode(hdc, TRANSPARENT);

                        DrawText( hdc, nr, -1, &rcQuantity, DT_SINGLELINE | DT_NOCLIP) ;

                        SetBkMode(hdc, OPAQUE);
                        SetBkColor(hdc, RGB(scrollColor,scrollColor + 70, scrollColor+150));
                        SetTextColor(hdc, RGB(fontColor[0], fontColor[1], fontColor[2]));
                        DrawText(hdc, TEXT(firstText), -1, &rcTODOList, DT_NOCLIP);

                        EndPaint(hWnd, &Ps);
                }
                break;

                case WM_CTLCOLOREDIT: {
                        HDC hdc = (HDC)wParam;
                        HWND hwnd = (HWND)lParam;
                        HBRUSH color;

                        if (GetDlgCtrlID(hwnd) == INPUT_TEXT_ADD_TODO) {
                                color = CreateSolidBrush(RGB(225, 225, 225));
                                SetTextColor(hdc, RGB(0, 0, 255));
                                SetBkMode(hdc, TRANSPARENT);
                                SetBkColor(hdc,(LONG)color);
                        }
                        return (LONG) color;
                }
                break;

                case WM_COMMAND: {
                        switch(LOWORD(wParam)) {
                                case BUTTON_ADD_TODO: {

                                        char buffer[256];
                                        SendMessage(hInputTODO,
                                                    WM_GETTEXT,
                                                    sizeof(buffer)/sizeof(buffer[0]),
                                                    reinterpret_cast<LPARAM>(buffer));


                                        if (strlen(buffer) > 0){
                                                char newInput[255] = "- ";

                                                strcat(newInput, buffer);

                                                SendMessage(hWndList, LB_ADDSTRING, 0, (LPARAM)newInput);
                                                SendMessage(hInputTODO, WM_SETTEXT, NULL, (LPARAM)"");
                                                TODONumber++;
                                                InvalidateRect(hWnd, &rcQuantity, TRUE);

                                        }
                                }
                                break;

                                case BUTTON_DISPLAY_TODO_NR: {
                                        ::MessageBox(hWnd, "So soon ? :( ", "Exit", MB_ICONERROR);
                                        PostQuitMessage(0);
                                }
                                break;
                                case ID_FILE_EXIT: {
                                        PostQuitMessage(0);
                                }
                                break;

                                break;
                                case ID_EVENT_RED: {
                                        fontColor[0] = 255;
                                        fontColor[1] = 0;
                                        fontColor[2] = 0;
                                        InvalidateRect(hWnd, &rcTODOList, TRUE);
                                }
                                break;
                                case ID_EVENT_GREEN: {
                                        fontColor[0] = 0;
                                        fontColor[1] = 255;
                                        fontColor[2] = 0;
                                        InvalidateRect(hWnd, &rcTODOList, TRUE);
                                }
                                break;
                                case ID_EVENT_BLUE: {
                                        fontColor[0] = 0;
                                        fontColor[1] = 0;
                                        fontColor[2] = 255;
                                        InvalidateRect(hWnd, &rcTODOList, TRUE);
                                }
                                break;

                                case IDC_TODO_LIST:{
                                        if (HIWORD(wParam) == LBN_DBLCLK) {
                                                int index = SendMessage(hWndList, LB_GETCURSEL, 0, 0);
                                                SendMessage(hWndList, LB_DELETESTRING, (WPARAM)index, 0);
                                                TODONumber--;
                                                InvalidateRect(hWnd, &rcQuantity, TRUE);
                                        }
                                }
                                break;
                        }
                }
                break;


                case WM_VSCROLL: {
                        switch (LOWORD(wParam)) {

                                case SB_PAGEDOWN: {
                                        scrollColor += 15;
                                }
                                break;
                                case SB_PAGEUP: {
                                        scrollColor -= 15;
                                }
                                break;
                                case SB_BOTTOM: {
                                        scrollColor = 255;
                                }
                                break;
                                case SB_TOP: {
                                        scrollColor = 0;
                                }
                                break;
                                case SB_THUMBPOSITION:
                                case SB_THUMBTRACK: {
                                        scrollColor = HIWORD(wParam);
                                }
                                break;
                        }

                        SetScrollPos(hWndScroll, SB_CTL, scrollColor, TRUE);
                        InvalidateRect(hWnd, &rcTODOList, TRUE);
                }
                break;


                case WM_GETMINMAXINFO: {
                        MINMAXINFO * mmiStruct;
                        mmiStruct = (MINMAXINFO*)lParam;

                        POINT ptPoint;

                        ptPoint.x = 335;    //Minimum width of the window.
                        ptPoint.y = 260;    //Minimum height of the window.
                        mmiStruct->ptMinTrackSize = ptPoint;

                        ptPoint.x = GetSystemMetrics(SM_CXMAXIMIZED);   //Maximum width of the window.
                        ptPoint.y = GetSystemMetrics(SM_CYMAXIMIZED);   //Maximum height of the window.
                        mmiStruct->ptMaxTrackSize = ptPoint;
                }
                break;

                case WM_KEYDOWN: {
                        switch (wParam) {

                                case VK_SPACE : {
                                        if (HIBYTE(GetAsyncKeyState(VK_LCONTROL))) {
                                                scrollColor = 0;
                                                SetScrollPos(hWndScroll, SB_CTL, scrollColor, TRUE);
                                                InvalidateRect(hWnd, &rcTODOList, TRUE);
                                                return 0;
                                        }
                                }
                                break;
                                case VK_F1: {
                                        if (HIBYTE(GetAsyncKeyState(VK_LCONTROL))) {

                                                SendMessage(hWndList, LB_RESETCONTENT, 0, 0);
                                                TODONumber = 0;
                                                InvalidateRect(hWnd, &rcQuantity, TRUE);

                                        }
                                }
                                break;
                        }
                }
                break;

                case WM_SETFOCUS: {
                        SetFocus(hWnd);
                }
                break;
                case WM_DESTROY: {
                        PostQuitMessage(0);
                        return 0;
                }
                break;
        }



        return DefWindowProc(hWnd,msg,wParam,lParam);
}