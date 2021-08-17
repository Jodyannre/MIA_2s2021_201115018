#ifndef OBJ_MKDISK_H
#define OBJ_MKDISK_H
#include <QString>
#include "string"
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

};

#endif // OBJ_MKDISK_H
