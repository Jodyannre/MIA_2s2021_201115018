#ifndef OBJ_MKDISK_H
#define OBJ_MKDISK_H
#include <QString>
#include "string"
#include <QDir>
#include <QDebug>
#include "estructuras.h"
#include "time.h"
using namespace std;


class obj_mkdisk
{

private:

public:
    obj_mkdisk();

    int size;
    int f;
    string path;
    string u;
    void mostrardatos(obj_mkdisk *disco);
    int ejecutar();
    void verificarRuta(string path);
    void crearParticionesVacias(Particion particion, int posicion, MBR mbr);

};

#endif // OBJ_MKDISK_H
