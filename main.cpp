#include "window.hpp"

int main()
{
    Window mainWindow(100, 50);
    mainWindow.setBorders();
    mainWindow.setTitle("Ray Casting");
    mainWindow.setBgIMG(0xFA);

    mainWindow.render();
    getchar();
}