#ifndef OBJ_REP_H
#define OBJ_REP_H
#include <QString>
#include "string"
#include "obj_umount.h"
#include <QDir>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <queue>

using namespace std;

class obj_rep
{
public:
    string name;
    string path;
    string id;
    string ruta;
    string root;
    int tipo;
    MBR mbr;
    EBR ebr;
    Cmount cmount;
    string currentDir;
    string nombreArchivo;
    int posD;
    int posP;    
    obj_rep();
    void mostrardatos(obj_rep *rep);
    int ejecutar();
    void verificarRuta(string ruta);
    string getNombreDisco(string path);
    void crearReporteMBR(string nombreArchivo, string nombreRep, string ruta,string rutaDisco);
    void crearReporteEBR(string nombre, string nombreRep, string ruta, string rutaDisco);
    void crearReporteDisk(string nombreArchivo, string nombreRep, string ruta,string rutaDisco);
    string getFechaMBR();
    string convertToString(char* a);

};

#endif // OBJ_REP_H
