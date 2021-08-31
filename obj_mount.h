#ifndef OBJ_MOUNT_H
#define OBJ_MOUNT_H
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include "iostream"
#include <string.h>
#include "estructuras.h"
using namespace std;

class obj_mount
{
public:
    string path;
    string name;
    string currentDir;
    string nombreArchivo;
    bool archivoCreado;
    MBR mbr;
    EBR ebr;
    Cmount cmount;
    obj_mount();
    Particion buscarParticion();
    int ejecutar();
    int getCurrentDir();
    int crearArchivo();
    bool estaMontada();
    int estaMontado();
    string nameToString(int disco, int particion);


};

#endif // OBJ_MOUNT_H
