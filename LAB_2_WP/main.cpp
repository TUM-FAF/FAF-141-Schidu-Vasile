#include <windows.h>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
HWND textField, button1, textBox, button2;
/*  Make the class name into a global variable  */
char szClassName[ ] = "CodeBlocksWindowsApp";
char name[40];

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow){
HWND hwnd;               /* This is the handle for our window */
MSG messages;            /* Here messages to the application are saved */
WNDCLASSEX wincl;        /* Data structure for the windowclass */

/* The Window structure */
wincl.hInstance = hThisInstance;
wincl.lpszClassName = szClassName;
wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
wincl.cbSize = sizeof (WNDCLASSEX);

/* Use default icon and mouse-pointer */
wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
wincl.lpszMenuName = NULL;                 /* No menu */
wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
wincl.cbWndExtra = 0;                      /* structure or the window instance */
/* Use Windows's default colour as the background of the window */
wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

/* Register the window class, and if it fails quit the program */
if (!RegisterClassEx (&wincl))
return 0;

/* The class is registered, let's create the program*/
hwnd = CreateWindowEx (
        0,                   /* Extended possibilites for variation */
        szClassName,         /* Classname */
        "WP Lab#2 | Schidu Vasile",  /* Title Text */
        WS_MINIMIZEBOX | WS_SYSMENU, /* default window */
        CW_USEDEFAULT,       /* Windows decides the position */
        CW_USEDEFAULT,       /* where the window ends up on the screen */
        600,                 /* The programs width */
        400,                 /* and height in pixels */
        HWND_DESKTOP,        /* The window is a child-window to desktop */
        NULL,                /* No menu */
        hThisInstance,       /* Program Instance handler */
        NULL                 /* No Window Creation data */
);

/* Make the window visible on the screen */
ShowWindow (hwnd, nCmdShow);

/* Run the message loop. It will run until GetMessage() returns 0 */
while (GetMessage (&messages, NULL, 0, 0)){
/* Translate virtual-key messages into character messages */
TranslateMessage(&messages);
/* Send message to WindowProcedure */
DispatchMessage(&messages);
}

/* The program return-value is 0 - The value that PostQuitMessage() gave */
return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
switch (message){                  /* handle the messages */
        case WM_DESTROY:
                PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
        case WM_CREATE:
                textField = CreateWindow("STATIC",
                                         "Type yor name here",
                                         WS_VISIBLE | WS_CHILD ,
                                         235, 20, 130,18,
                                         hwnd, NULL, NULL, NULL);
                button1 = CreateWindow("BUTTON",
                                        "EXIT",
                                        WS_VISIBLE | WS_CHILD | WS_BORDER,
                                        250, 300, 100, 20,
                                        hwnd, (HMENU) 1, NULL, NULL);
                textBox = CreateWindow("EDIT",
                                        "",
                                        WS_CHILD | WS_VISIBLE | WS_BORDER,
                                        218, 50, 160, 18,
                                        hwnd,NULL, NULL, NULL);
                button2 = CreateWindow("BUTTON",
                                        "Go",
                                        WS_VISIBLE | WS_CHILD | WS_BORDER,
                                        385, 50, 50, 18,
                                        hwnd, (HMENU) 2, NULL, NULL);

        break;
        case WM_COMMAND:
                switch(LOWORD(wParam)){
                        case 1:
                                ::MessageBeep(MB_ICONERROR);
                                ::MessageBox(hwnd, "So soon ? :(","Exit Message Box" , MB_OK);
                                PostQuitMessage(0);
                        case 2:
                                int gwLoop = 0;
                                gwLoop = GetWindowText(textBox, &name[0], 35);
                                ::MessageBeep(MB_ICONERROR);
                                ::MessageBox(hwnd, name,"Hello Window" , MB_OK);

                }
        break;
        default:                      /* for messages that we don't deal with */


return DefWindowProc (hwnd, message, wParam, lParam);
}

return 0;
}