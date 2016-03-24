//
// Created by sckee on 3/23/2016.
//
#include <windows.h>
#include <windowsx.h>

void updateColorControls(HDC hdc, COLORREF rgb, int xLeft, int yTop)
{
    HBRUSH hBrush = CreateSolidBrush(rgb);
    HPEN hPen = CreatePen(PS_INSIDEFRAME, 2, RGB(10, 40, 140));

    SelectObject(hdc, hBrush);
    SelectObject(hdc, hPen);

    Rectangle(hdc, xLeft, yTop, xLeft + 25, yTop + 20);

    hBrush = CreateSolidBrush(RGB(10, 40, 140));
    SelectObject(hdc, hBrush);

    Rectangle(hdc, xLeft+18, yTop+13, xLeft + 25, yTop + 20);

    DeleteObject(hPen);
    DeleteObject(hBrush);
}

int getFromInput(HWND input)
{
    int result, len;
    len = SendMessage(input, WM_GETTEXTLENGTH, 0, 0);

    char * temp = (char *)malloc(len + 1);
    SendMessage(input, WM_GETTEXT, len + 1, (LPARAM)temp);
    result = atoi(temp);
    free(temp);
    return result;
}

POINT getCurrentPointPosition(int mouseX, int mouseY, RECT limit, int width)
{
    POINT result;
    width = width / 2 + 1;

    if(mouseX + width > limit.right)
        result.x = limit.right - width;
    else if(mouseX - width < limit.left)
        result.x = limit.left + width;
    else
        result.x = mouseX;

    if(mouseY - width < limit.top)
        result.y = limit.top + width;
    else if(mouseY + width > limit.bottom)
        result.y = limit.bottom - width;
    else
        result.y = mouseY;

    return result;
}