#include "obj_mkfs.h"

obj_mkfs::obj_mkfs()
{
    this->id = "";
    this->type = -1;
    this->fs = -1;
}

/*
 * Tipos
 * 0 -> Fast
 * 1 -> Full
 *
 * Fs
 * 2 -> 2fs
 * 3 -> 3fs
 *
*/

int obj_mkfs::ejecutar( ){
    //Variables
    FILE *disco;
    obj_umount *umount = new obj_umount();

    //Verificar los obligatorios
    if (this->id == ""){
        cout<<"Error, no se ingreso ningun id."<<endl;
        return -1;
    }

    //Verificar los opcionales
    if (this->type == -1){
        //Por defecto es el full
        this->type = 1;
    }

    if (this->fs == -1){
        //Por defecto sera el ext2
        this->fs = 2;
    }

    //Cargar data, directorio utilizando umount
    umount->id = this->id;
    umount->getCurrentDir();
    this->currentDir = umount->currentDir;
    disco =fopen(this->currentDir.c_str(),"rb+");

    if (disco == NULL){
        //El comando mount nunca ha sido utilizado
        cout<<"Error, no se ha montado ninguna particion"<<endl;
        fclose(disco);
        return -1;
    }
    //Cargar cmount
    fseek(disco, 0, SEEK_SET);
    fread(&this->cmount,sizeof(Cmount),1,disco);
    umount->cmount = this->cmount;


    //Vericicar que la particion este montada
    if (!umount->estaMontada()){
        cout<<"Error, la particion no ha sido montada."<<endl;
        fclose(disco);
        return -1;
    }


    //Verificar que el disco este montado
    if (!umount->estaMontado()){
        cout<<"Error, el disco no ha sido montado."<<endl;
        fclose(disco);
        return -1;
    }

    //Todo fue bien, obtener posiciones
    this->posD = umount->posD;
    this->posP = umount->posP;

    //Verificar el tipo del sistema, si es ext2 o ext3
    if (this->fs == 2){
        //Es ext2

        //Crear superbloque


        //Crear inodos




    }else{
        //Es ext3


    }



}



