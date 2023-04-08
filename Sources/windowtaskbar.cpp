#include "../Headers/windowtaskbar.h"

WindowTaskBar::WindowTaskBar(QObject *parent): QObject{parent}{

}
//-----------------------------------------------------------------------------------------
void WindowTaskBar::windowsClose()  {
    exit(EXIT_FAILURE);
}
//-----------------------------------------------------------------------------------------
