//
// Created by sckee on 2/18/2016.
//

#include "ClassButton.h"


ClassButton::ClassButton(char *text, int posX, int posY, int width, int height, HWND parent, int id) {

    this->posX = posX;
    this->posY = posY;
    this->width = width;
    this->height = height;
    this->parent = parent;

    hWndButton=CreateWindowEx(NULL,
                              "BUTTON",
                              text,
                              WS_TABSTOP|WS_VISIBLE|
                              WS_CHILD|BS_DEFPUSHBUTTON,
                              posX,
                              posY,
                              width,
                              height,
                              parent,
                              (HMENU)id,
                              GetModuleHandle(NULL),
                              NULL);
}


int ClassButton::getHeight() {return this->height; }
int ClassButton::getId(){return this->id;}
int ClassButton::getWidth(){return this->width;}
int ClassButton::getPosX(){return this->posX;}
int ClassButton::getPosY(){return this->posY;}

void ClassButton::setPos(int x, int y){
    this->posX = x;
    this->posY = y;
    SetWindowPos(hWndButton, HWND_TOP, x, y, x/2, y/2, 1);
    InvalidateRect(hWndButton, NULL, true);
}

void ClassButton::setFont(){
    HFONT hFont = CreateFont (20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Comic Sans MS");
    SendMessage(hWndButton, WM_SETFONT, WPARAM (hFont), TRUE);

}