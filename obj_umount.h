#ifndef OBJ_UMOUNT_H
#define OBJ_UMOUNT_H
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include "iostream"
#include <string.h>
#include "estructuras.h"
using namespace std;

class obj_umount
{
public:
    string id;
    string currentDir;
    string nombreArchivo;
    bool archivoCreado;
    int posD;
    int posP;
    Particion buscarParticion();
    int ejecutar();
    int getCurrentDir();
    bool estaMontada();
    bool estaMontado();
    string nameToString(int disco, int particion);
    string idToString(int disco, int particion);
    MBR mbr;
    EBR ebr;
    Cmount cmount;
    obj_umount();
};

#endif // OBJ_UMOUNT_H
