#ifndef OBJ_FDISK_H
#define OBJ_FDISK_H
#include "string"
#include "iostream"
#include "estructuras.h"
#include <bits/stdc++.h>
#include <cstdio>



using namespace std;


class obj_fdisk
{
public:
    obj_fdisk();

    int size;
    int f;
    string path;
    int u;
    int type;
    bool eliminar;
    int tipo_eliminar;
    string name;
    bool add;
    MBR mbr_temp;
    EBR ebr_temp;
    bool extendida;
    int pos_extendida;
    int ebr_sig;
    void mostrarDatos();
    void ejecutar();
    int buscarParticionVacia(int tipo_particion);
    int calcularPartStart(int size, int tipo_particion);
    EBR calcularPartStartLogica(int size);
    void ordenarParticiones();
    int eliminarParticion(int size);
    int eliminarParticionLogica();
    int agregarEspacio(int size,int tipoParticion);
    int agregarEspacioLogica(int size);
    int buscarExtendida();
    int addParticionLogica(int size);
    void cargarEBR();
    int getUltimaLogica();
    string obtenerNombre(int particion, int extendida);

};

#endif // OBJ_FDISK_H
