#ifndef OBJ_REP_H
#define OBJ_REP_H
#include <QString>
#include "string"
using namespace std;

class obj_rep
{
public:
    char* name;
    char* path;
    char* id;
    char* ruta;
    char* root;
    int tipo;
    obj_rep();
    void mostrardatos(obj_rep *rep);
    void ejecutar();
};

#endif // OBJ_REP_H
