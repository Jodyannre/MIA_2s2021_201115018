#include "obj_umount.h"

obj_umount::obj_umount()
{
    this->currentDir = "";
    this->nombreArchivo = "/dsmount.data";
    this->archivoCreado = false;
    this->posD = -1;
    this->posP = -1;
}



int obj_umount::ejecutar(){
    FILE *disco;

    //Obtener ruta del archivo
    this->getCurrentDir();

    //Cargar el archivo
    disco =fopen(this->currentDir.c_str(),"rb+");

    if (disco == NULL){
        //El comando mount nunca ha sido utilizado
        cout<<"Error, no se ha montado ninguna particion"<<endl;
        fclose(disco);
        return -1;
    }

    fseek(disco, 0, SEEK_SET);
    fread(&this->cmount,sizeof(Cmount),1,disco);

    //Vericicar que la particion este montada
    if (!this->estaMontada()){
        cout<<"Error, la particion no ha sido montada."<<endl;
        fclose(disco);
        return -1;
    }


    //Verificar que el disco este montado
    if (!this->estaMontado()){
        cout<<"Error, el disco no ha sido montado."<<endl;
        fclose(disco);
        return -1;
    }



    //Todo bien, crear una particion vacia y sobreescribir la otra
    this->cmount.disco[this->posD].particiones[this->posP].name[0] = ' ';
    this->cmount.disco[this->posD].particiones[this->posP].id[0] = ' ';
    this->cmount.disco[this->posD].particiones[this->posP].estado = -1;
    this->cmount.disco[this->posD].particiones[this->posP].type = ' ';


    //Actualizar el archivo
    fseek(disco, 0, SEEK_SET);
    fwrite(&this->cmount, sizeof(Cmount), 1, disco);
    fclose(disco);
    return 0;

}




int obj_umount::getCurrentDir(){
    char buffer[PATH_MAX];
    if (getcwd(buffer, sizeof(buffer)) != NULL) {
        printf("El directorio actual es: %s\n", buffer);
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
        this->currentDir+= this->nombreArchivo;
        cout<<this->currentDir<<endl;
    } else {
        perror("Error, el directorio no existe.");
        return -1;
    }
    return 0;
}

bool obj_umount::estaMontada(){
    //Recorrer cmount y luego cada disco y particion buscando la que este montada
    string nombre = "";
    char letra = this->id[2];
    this->posD= letra;
    this->posD-=48+1;
    if (this->posD < 0){
        //El disco no esta montado
        return false;
    }

    //Verificar en el archivo si el disco esta cargado
    if (!this->estaMontado()){
        //El disco no esta montado
        cout<<"El disco no esta montado"<<endl;
        return false;
    }

    //Buscar la particion por id
    for (int j=0; j < 49;j++){
        nombre = this->idToString(this->posD,j);
        if (this->id == nombre){
            if (this->cmount.disco[this->posD].particiones[j].estado == 1){
                //Ya esta montado
                this->posP = j;
                return true;
            }else{
                //No esta montado, solo es data rezagada
                return false;
            }
        }
    }

    return false;

}

bool obj_umount::estaMontado(){
    if (this->cmount.disco[this->posD].estado==1){
        return true;
    }else{
        return false;
    }
}


string obj_umount::nameToString(int disco, int particion){
    int i = 0;
    string nombre = "";
    //Validar si la particion esta montada
    if (this->cmount.disco[disco].particiones[particion].estado == -1){
        return nombre;
    }
    while(this->cmount.disco[disco].particiones[particion].name[i]!=NULL && i<=15){
        nombre+= this->cmount.disco[disco].particiones[particion].name[i];
        i++;
    }
    return nombre;
}


string obj_umount::idToString(int disco, int particion){
    int i = 0;
    string nombre = "";
    //Validar si la particion esta montada
    if (this->cmount.disco[disco].particiones[particion].estado == -1){
        return nombre;
    }
    while(this->cmount.disco[disco].particiones[particion].id[i]!=NULL && i<4){
        nombre+= this->cmount.disco[disco].particiones[particion].id[i];
        i++;
    }
    return nombre;
}

string obj_umount::pathToString(int disco, int particion){
    int i = 0;
    string nombre = "";
    //Validar si la particion esta montada
    if (this->cmount.disco[disco].estado == -1){
        return nombre;
    }
    while(this->cmount.disco[disco].path[i]!=NULL && i<=100){
        nombre+= this->cmount.disco[disco].path[i];
        i++;
    }
    return nombre;
}
