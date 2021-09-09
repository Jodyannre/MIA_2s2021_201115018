#include "obj_rmdisk.h"

obj_rmdisk::obj_rmdisk()
{
    this->path = "";
}


void obj_rmdisk::mostrardatos(obj_rmdisk *disco){

    printf("El path es %s \n",disco->path.c_str());


}

int obj_rmdisk::ejecutar(){
    string confirmacion="";
    if (this->estaMontado()){
        printf("El disco no puede ser eliminado mientras haya una particion montada.");
        return -1;
    }
    cout<<"Desea continuar con la eliminacion del disco ingresado? (y/n)\n"<<endl;
    cin>>confirmacion;
    //confirmacion = "y";
    if (confirmacion =="y" || confirmacion =="Y"){

        if( remove(this->path.c_str()) != 0 ){
            printf("Error, el disco no existe.\n");
            return -1;
        }

        else{
            printf( "Disco eliminado con exito. \n" );
            return 1;
        }


    }else if (confirmacion =="n" || confirmacion =="N"){
        cout<<"El disco no fue eliminado."<<endl;
        return 0;

    }else{
        cout<<"Error, opcion invalida."<<endl;
        return 0;
    }


}


bool obj_rmdisk::estaMontado(){
    int posicion = 1;
    Cmount cmount;
    FILE *disco;
    getCurrentDir();
    //Buscar el disco y verificar si existe
    disco =fopen(this->currentDir.c_str(),"rb+");

    //Si el disco no existe retornara un null
    if (disco == NULL){
        //fclose(disco);
        return false;
    }

    //Copiar el cmount
    fseek(disco, 0, SEEK_SET);
    fread(&cmount,sizeof(Cmount),1,disco);

    //Buscar disco
    for (int i = 0; i< 29;i++){
        if (cmount.disco[i].path == this->path){
            posicion = i;
            break;
        }
    }

    //Verificar si alguna particion esta montada
    for (int i = 0; i< 49;i++){
        if (cmount.disco[posicion].particiones[i].estado == 1){
            fclose(disco);
            return true;
        }
    }


    fclose(disco);
    return false;
}


int obj_rmdisk::getCurrentDir(){
    char buffer[PATH_MAX];
    if (getcwd(buffer, sizeof(buffer)) != NULL) {
        //printf("El directorio actual es: %s\n", buffer);
        for (int i=0; i< sizeof(buffer);i++){
            if (i==88){
                //Nada
                cout<<endl;
            }
            if (buffer[i]==NULL){
                break;
            }
            this->currentDir+= buffer[i];
        }
        this->currentDir+= "/dsmount.data";
        //cout<<this->currentDir<<endl;
    } else {
        //perror("Error, el directorio no existe.");
        return -1;
    }
    return 0;
}
