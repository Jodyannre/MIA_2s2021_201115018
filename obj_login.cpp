#include "obj_login.h"

obj_login::obj_login()
{
    this->id="";
    this->pass="";
    this->user="";
}


int obj_login::ejecutar(){
    //Verificar los obligatorios
    if (this->user == ""){
        cout<<"Error, no se ingreso ningun usuario."<<endl;
        return -1;
    }

    //Verificar los opcionales
    if (this->id == ""){
        //Error no se ingreso id
        cout<<"Error, no se ingreso un id valido."<<endl;
        return -1;
    }

    if (this->pass == ""){
        //Error no se ingreso contrasena
        cout<<"Error, no se ingreso un password valido."<<endl;
        return -1;
    }

    FILE* dataMount;
    FILE* disco;
    obj_umount *umount = new obj_umount();
    string name_part;
    string dir_disco;
    int dir_part;
    char type_part;
    int part_start = -1;
    int n = 0;
    int size_part = 0;

    umount->getCurrentDir();
    //Cargar data, directorio utilizando umount
    umount->id = this->id;
    umount->getCurrentDir();
    this->currentDir = umount->currentDir;
    this->currentDir = this->currentDir+"/dsmount.data";
    dataMount =fopen(this->currentDir.c_str(),"rb+");

    if (dataMount == NULL){
        //El comando mount nunca ha sido utilizado
        cout<<"Error, no se ha montado ninguna particion"<<endl;
        fclose(dataMount);
        return -1;
    }
    //Cargar cmount
    fseek(dataMount, 0, SEEK_SET);
    fread(&this->cmount,sizeof(Cmount),1,dataMount);
    umount->cmount = this->cmount;


    //Vericicar que la particion este montada
    if (!umount->estaMontada()){
        cout<<"Error, la particion no ha sido montada."<<endl;
        fclose(dataMount);
        return -1;
    }


    //Verificar que el disco este montado
    if (!umount->estaMontado()){
        cout<<"Error, el disco no ha sido montado."<<endl;
        fclose(dataMount);
        return -1;
    }

    //Todo fue bien, obtener posiciones
    this->posD = umount->posD;
    this->posP = umount->posP;


    //Cargar MBR o EBR y la direccion del inicio de la particion
    fclose(dataMount);
    type_part = this->cmount.disco[posD].particiones[posP].type;
    name_part = umount->nameToString(posD,posP);
    dir_part = this->cmount.disco[posD].particiones[posP].direccion;
    dir_disco = umount->pathToString(this->posD, this->posP);
    disco =fopen(dir_disco.c_str(),"rb+");

    if (type_part == 'P'){
        //Si es primaria cargar el MBR
        fseek(disco, 0, SEEK_SET);
        fread(&this->mbr,sizeof(MBR),1,disco);
        part_start= this->mbr.mbr_partitions[dir_part].part_start;
        size_part = this->mbr.mbr_partitions[dir_part].part_size;
    }else if (type_part == 'L'){
        //Si es logica cargar directamente el EBR
        fseek(disco, dir_part, SEEK_SET);
        fread(&this->ebr,sizeof(MBR),1,disco);
        part_start= this->ebr.part_start;
        size_part = this->ebr.part_size;
    }
    fclose(disco);
    this->lector = fopen(dir_disco.c_str(),"rb+");
    fseek(this->lector,part_start,SEEK_SET);
    fread(&superB,sizeof(SuperBloque),1,this->lector);
    string datosUsuario = this->buscarUsuario(superB.s_inode_start,0,"",this->id);
    fclose(this->lector);

    return 0;
}


string obj_login::buscarUsuario(int posInodo, int pointerBloque, string lectura, string UID){
    Inodo inodo;
    BloqueArchivos bloque;
    string resultado = lectura;
    string temp= "";
    string tipo = "";
    string nombreUsuario = "";
    int final = -1;
    fseek(this->lector,posInodo,SEEK_SET);
    fread(&inodo,sizeof(Inodo),1,this->lector);
    int posBloque = inodo.i_block[pointerBloque];
    fseek(this->lector,posBloque*sizeof(BloqueArchivos)+superB.s_block_start,SEEK_SET);
    fread(&bloque,sizeof(BloqueArchivos),1,this->lector);

    for (int i =0;i<sizeof(bloque.b_content);i++){
        if (bloque.b_content[i]==NULL){
            break;
        }
        if (bloque.b_content[i]=='\n'){
            //Ya llego al final de un dato
            temp = resultado;
            final = resultado.find(",");
            resultado = resultado.substr(final,resultado.length()-1);
            final = resultado.find(",");
            tipo = resultado.substr(0,final);
            if (tipo != "U"){
                resultado = "";
                continue;
            }
            final = resultado.find(",");
            resultado = resultado.substr(final,resultado.length()-1);
            final = resultado.find(",");
            nombreUsuario = resultado.substr(0,final);
            if (nombreUsuario == UID){
                //Encontrado y retornar temp
                return temp;
            }else{
                resultado = "";
                continue;
            }
        }
        resultado+=bloque.b_content[i];
    }


    if (resultado != ""){
        //Esta leyendo a medias
        resultado = this->buscarUsuario(posInodo, pointerBloque+1, resultado, UID);
    }


    return resultado;
}
