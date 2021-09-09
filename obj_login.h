#ifndef OBJ_LOGIN_H
#define OBJ_LOGIN_H
#include "iostream"
#include "string"
#include "estructuras.h"
#include "obj_umount.h"

using namespace std;

class obj_login
{
public:
    string user;
    string pass;
    string id;
    string currentDir;
    obj_umount umount;
    Cmount cmount;
    SuperBloque superB;
    FILE* lector;
    MBR mbr;
    EBR ebr;
    int posD;
    int posP;
    obj_login();
    int ejecutar();
    string buscarUsuario(int posInodo,int pointerBloque,string lectura, string UID);
};

#endif // OBJ_LOGIN_H
