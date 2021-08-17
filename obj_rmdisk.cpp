#include "obj_rmdisk.h"

obj_rmdisk::obj_rmdisk()
{
    this->path = "";
}


void obj_rmdisk::mostrardatos(obj_rmdisk *disco){

    printf("El path es %s \n",disco->path.c_str());


}

int obj_rmdisk::ejecutar(){
    if( remove(this->path.c_str()) != 0 ){
        printf("Error, el archivo no existe.");
        return -1;
    }

    else{
        printf( "Archivo eliminado con exito." );
        return 1;
    }

}
