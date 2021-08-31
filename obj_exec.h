#ifndef OBJ_EXEC_H
#define OBJ_EXEC_H

#include <iostream>
#include <fstream>
#include <string>
#include "string"
#include "iostream"
#include "QString"
#include <parser.h>  // Nuestro parser
#include <scanner.h>  // Nuestro scanner
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
extern int yyparse(); //
//static QList<discosmontados> discosenmemoria

extern int linea; // Linea del token
extern int columna; // Columna de los tokens
extern int yylineno;

using namespace std;

class obj_exec
{
public:
    string path;
    string nombreArchivo;
    string currentDir;
    obj_exec();
    int ejecutar();
    int getCurrentDir();
};

#endif // OBJ_EXEC_H
