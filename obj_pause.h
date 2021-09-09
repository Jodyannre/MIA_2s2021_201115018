#ifndef OBJ_PAUSE_H
#define OBJ_PAUSE_H

#include "string"
#include "iostream"
#include <unistd.h>
#include <termios.h>
#include <curses.h>
#include <stdio.h>

using namespace std;

class obj_pause
{
public:
    obj_pause();
    int ejecutar();
};

#endif // OBJ_PAUSE_H
