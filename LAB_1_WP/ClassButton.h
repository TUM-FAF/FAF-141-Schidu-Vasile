//
// Created by sckee on 2/18/2016.
//

#ifndef WINAPI_BUTTON_H
#define WINAPI_BUTTON_H

#include <windows.h>
#include <string>
using namespace std;

class ClassButton {
private:
    HWND hWndButton;
    char *text;
    int posX;
    int posY;
    int width;
    int height;
    int id;
    HWND parent;

public:

    ClassButton(char* text, int posX, int posY, int width, int height, HWND parent, int id );
    int getId();
    int getPosX();
    int getPosY();
    int getHeight();
    int getWidth();
    void setPos(int x, int y);
    void setFont();

};


#endif //WINAPI_BUTTON_H