#include "obj_mkdisk.h"

obj_mkdisk::obj_mkdisk()
{
    this->size = -1;
    this->f = -1;
    this->path = "";
    this->u = "";
}

void obj_mkdisk::mostrardatos(obj_mkdisk *disco){

          printf("\n\n---------DATOS----------\n\n");

          printf("EL tamano es %d \n",disco->size);
          printf("La ruta es %s \n",disco->path.c_str());
          printf("La unidad es %s \n",disco->u.c_str());
          printf("El fit es %d \n",disco->f);

}

int obj_mkdisk::ejecutar(){
    FILE *archivo; //Archivo binario
    printf(this->path.c_str());
    char buffer[1024];
    int unidad = 0;

    if (this->size<0){
        printf("Error, no se especifico ningun size para el disco. \n");
        return -1;
    }   
    if (this->path == ""){
        printf("Error, no se especifico ningun path para el disco. \n");
        return -1;
    } 
    if (this->u ==""){
        this->u = "m";
    }
    if (this->u == "k" || this->u == "K"){
        unidad = 1;
    }else{
        unidad = 2;
    }

    if (this->f < 0){
        this->f = 1;
    }
    archivo = fopen(this->path.c_str(),"wb");
    //Llenando el buffer del tamano del disco
    for (int i =0 ; i < this->size;i++){
        buffer[i]='/0';
    }

    if (unidad == 1){
        //Kilobytes
        printf("llenado kilos");
        for (int i = 0 ; i< this->size; i++){
            fwrite(&buffer,1024,1,archivo);
        }
        fclose(archivo);

    }else{
        //Megabytes
        printf("llenado megas");
        for (int i = 0 ; i< this->size*1024; i++){
            fwrite(&buffer,1024,1,archivo);
        }
        fclose(archivo);
    }



}
