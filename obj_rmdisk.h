#ifndef OBJ_RMDISK_H
#define OBJ_RMDISK_H
#include <QString>
#include "string"
#include <unistd.h>
#include <stdio.h>
#include "iostream"
#include <limits.h>
#include "estructuras.h"
using namespace std;

class obj_rmdisk
{
public:
    obj_rmdisk();
    void mostrardatos(obj_rmdisk *disco);
    string path;
    string currentDir;
    int ejecutar();
    bool estaMontada();
    bool estaMontado();
    int getCurrentDir();
};

#endif // OBJ_RMDISK_H
