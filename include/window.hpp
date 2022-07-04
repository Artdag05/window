#pragma once
#include <Windows.h>
#include <iostream>

class Window
{
public:
    Window(short width = 16, short height = 22); 
    ~Window();
    void setChar(int x, int y, wchar_t ch);
    void setTitle(const char* title);
    void setBgIMG(const wchar_t img);
    void setBorders();
    void refresh();
    void render();

private:
    const SHORT WIDTH;
    const SHORT HEIGHT;    

    HANDLE mConsole;
    HANDLE mConsoleIn;

    CHAR_INFO* mConsoleBuffer;
    COORD mDwBufSize;
    COORD mDwBufCoord;
    SMALL_RECT windowSize;

    wchar_t mBgIMG;
};