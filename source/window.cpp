#include "window.hpp"
#include "strsafe.h"

Window::Window(short width, short height):
    WIDTH(width),
    HEIGHT(height),
    mConsoleBuffer(nullptr),
    mBgIMG(' ')
{
    windowSize = {0, 0, WIDTH, HEIGHT};
    COORD windowBuffSize = {SHORT(WIDTH + 1), SHORT(HEIGHT + 1)};

    mConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    mConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

    if (!SetConsoleWindowInfo(mConsole, TRUE, &windowSize))
    {
        std::cout << "SetConsoleWindowInfo failed with error " << GetLastError() << std::endl;
    }
    
    if (!SetConsoleScreenBufferSize(mConsole, windowBuffSize))
    {
        std::cout << "SetConsoleScreenBufferSize failed with error " << GetLastError() << std::endl;
    }
    
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = FALSE;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(mConsole, &cursorInfo);

    mConsoleBuffer = new CHAR_INFO[(WIDTH + 1) * (HEIGHT + 1)];
    mDwBufSize.X = WIDTH + 1;
    mDwBufSize.Y = HEIGHT + 1;

    mDwBufCoord.X = 0;
    mDwBufCoord.Y = 0;

    for (int w = 0; w < WIDTH + 1; ++w)
    {
        for (int h = 0; h < HEIGHT + 1; ++h)
        {
            setChar(w, h,  mBgIMG); 
        }
    }
}

Window::~Window()
{
    delete [] mConsoleBuffer;
}

void Window::setChar(int x, int y, wchar_t ch)
{
    mConsoleBuffer[x + (WIDTH + 1) * y].Char.UnicodeChar = ch;
    mConsoleBuffer[x + (WIDTH + 1) * y].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
}

void Window::render()
{
    if(!WriteConsoleOutput(mConsole, mConsoleBuffer, mDwBufSize, mDwBufCoord, &windowSize))
    {
        std::cout << "WriteConsoleOutput failed - " << GetLastError() << std::endl;
    }
}

void Window::refresh()
{
    for (int w = 0; w < WIDTH + 1; ++w)
    {
        for (int h = 0; h < HEIGHT + 1; ++h)
        {
            setChar(w, h,  mBgIMG); 
        }
    }

    setBorders();
}

void Window::setBorders()
{
    for (int w = 0; w < WIDTH + 1; ++w)
    {
        for (int h = 0; h < HEIGHT + 1; ++h)
        {
            if ((h == 0 || h == HEIGHT) && (w > 0 && w < WIDTH))
                setChar(w, h, 205);
            if ((h > 0 && h < HEIGHT) && (w == 0 || w == WIDTH))
                setChar(w, h, 186);
            if (h == 0 && w == 0)
                setChar(w, h, 201);
            if (h == 0 && w == WIDTH)
                setChar(w, h, 187);
            if (h == HEIGHT && w == 0)
                setChar(w, h, 200);
            if (h == HEIGHT && w == WIDTH)
                setChar(w, h, 188);
        }
    }
}

void Window::setTitle(const char* title)
{
    TCHAR  szbuff[255];
    StringCchPrintf(szbuff, 255, TEXT("%s"), title);
    SetConsoleTitle(szbuff);
}

void Window::setBgIMG(const wchar_t img)
{
    mBgIMG = img;
}