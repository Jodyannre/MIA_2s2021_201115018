#ifndef OBJ_RMDISK_H
#define OBJ_RMDISK_H
#include <QString>
#include "string"
using namespace std;

class obj_rmdisk
{
public:
    obj_rmdisk();
    void mostrardatos(obj_rmdisk *disco);
    string path;
    int ejecutar();
};

#endif // OBJ_RMDISK_H
