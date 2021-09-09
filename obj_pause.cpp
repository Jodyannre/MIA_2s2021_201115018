#include "obj_pause.h"

obj_pause::obj_pause()
{

}

int obj_pause::ejecutar(){
    cout<<"Programa en pausa. Presione enter para continuar."<<endl;
    int c;
    c=getchar();
    putchar (c);
    return 0;
}
