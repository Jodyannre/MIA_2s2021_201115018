#ifndef OBJ_FDISK_H
#define OBJ_FDISK_H


class obj_fdisk
{
public:
    obj_fdisk();
    int size;
    int ajuste;
    char* path;
    char* unit;
    int type;
    bool eliminar;
    char* nombre;
    bool agregar;
};

#endif // OBJ_FDISK_H
