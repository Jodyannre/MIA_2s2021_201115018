#ifndef OBJ_MKFS_H
#define OBJ_MKFS_H
#include "string"
#include "iostream"
#include "estructuras.h"
#include "time.h"
#include "obj_umount.h"

using namespace std;

class obj_mkfs
{
public:
    string id;
    int type;
    int fs;
    obj_mkfs();
    int ejecutar();
    MBR mbr;
    EBR ebr;
    Cmount cmount;
    string currentDir;
    string nombreArchivo;
    bool archivoCreado;
    int posD;
    int posP;
};

#endif // OBJ_MKFS_H
