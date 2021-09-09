#include "obj_mount.h"

obj_mount::obj_mount()
{
    this->name = "";
    this->path = "";
    this->nombreArchivo = "/dsmount.data";
    this->currentDir = "";
    this->archivoCreado = false;
}

int obj_mount::ejecutar(){
    Particion particion;
    FILE *archivo;
    //Cmount cmount;
    Dmount dmount;
    Pmount pmount;
    int PosCmount;
    int PosDmount;
    int sizeCmount;
    int sizeDmount;
    int no_disco;
    int no_particion;
    string id;
    string sTemp;
    char letra;
    char numero;

    //Verificar que el comando este correcto
    if (this->name == "" || this->path == ""){
        cout<<"Error, al comando le faltan parametros. \n"<<endl;
        return -1;
    }

    //Inicializar variables
    PosCmount = -1;
    PosDmount = -1;
    no_disco = -1;
    no_particion = -1;
    id = "18";
    sTemp = "";
    sizeCmount = sizeof(this->cmount.disco)/sizeof(dmount);
    sizeDmount = sizeof(dmount)/sizeof(pmount);

    //Primero conseguir el directorio actual de trabajo
    this->getCurrentDir();

    //Crear el archivo donde se guardara la informacion de los discos y particiones montadas
    this->crearArchivo();

    //Cargar la particion solicitada
    particion = this->buscarParticion();

    if (particion.part_start == -1){
        cout<<"Error, el disco no existe o la ruta es incorrecta."<<endl;
        return -1;
    }
    if (particion.part_start == -2){
        cout<<"Error, la particion no existe."<<endl;
        return -1;
    }

    //Cargar el archivo con la data del mount
    archivo =fopen(this->currentDir.c_str(),"rb+");
    fseek(archivo, 0, SEEK_SET);
    fread(&this->cmount,sizeof(Cmount),1,archivo);

    //Verificar que la particion no este montada
    if (this->estaMontada()){
        cout<<"Error, esa particion ya esta montada."<<endl;
        return -1;
    }

    //Verificar que el disco no este montado
    no_disco = this->estaMontado();

    //Buscar un slot libre para montar el disco si no esta montado el disco
    if (no_disco == -1){
        for (int i=0; i< sizeCmount;i++){
            if (this->cmount.disco[i].estado == -1){
                no_disco = i;
                break;
            }
        }
    }

    //Verificar si se puede montar otra
    if (no_disco == -1){
        cout<<"No hay mas espacio para montar otro disco."<<endl;
        fclose(archivo);
        return -1;
    }

    //Llenando data del disco
    this->cmount.disco[no_disco].estado = 1;
    this->cmount.disco[no_disco].number = no_disco+1;
    strcpy(cmount.disco[no_disco].path,this->path.c_str());

    //Buscar un slot libre para montar la unidad
    for (int i=0; i< sizeDmount;i++){
        if (this->cmount.disco[no_disco].particiones[i].estado == -1){
            no_particion = i;
            break;
        }
    }

    //Verificar si se puede montar otra
    if (no_particion == -1){
        cout<<"No hay mas espacio para montar otro disco."<<endl;
        fclose(archivo);
        return -1;
    }

    //Generar ID
    numero = (no_disco+1)+'0';
    letra = no_particion+65;
    id+= numero;
    id+= letra;
    strcpy(this->cmount.disco[no_disco].particiones[no_particion].id,id.c_str());


    //Llenando data de la particion
    this->cmount.disco[no_disco].particiones[no_particion].type = particion.part_type;
    this->cmount.disco[no_disco].particiones[no_particion].direccion = particion.part_start;
    this->cmount.disco[no_disco].particiones[no_particion].estado = 1;
    strcpy(this->cmount.disco[no_disco].particiones[no_particion].name,this->name.c_str());



    //Actualizar los archivos montados
    fseek(archivo, 0, SEEK_SET);
    fwrite(&this->cmount,sizeof(Cmount),1,archivo);

    //Imprimir las particiones montadas en pantalla
    this->imprimirParticiones();
    fclose(archivo);
    return 0;
}

int obj_mount::crearArchivo(){
    FILE *archivo; //Archivo que guardara la data

    archivo =fopen(this->currentDir.c_str(),"rb+");

    //Si el archivo ya existe entonces salir
    if (archivo != NULL){
        this->archivoCreado = true;
        fclose(archivo);
        return 0;
    }
    archivo =fopen(this->currentDir.c_str(),"wb");

    Cmount discos;
    Dmount disco;
    int sizeArray = sizeof(discos.disco)/sizeof(disco);
    //cout<<sizeArray<<endl;
    //Crear los slots para los discos que se van a montar
    for (int i=0; i<29;i++){
        Dmount dn;
        dn.path[0] = ' ';
        dn.number = -1;
        dn.estado = -1;
        //Crear los slots para las particiones del disco
        for (int j=0; j<49;j++){
            Pmount p;
            p.name[0] = ' ';
            p.id[0] = ' ';
            p.estado = -1;
            p.type = ' ';
            dn.particiones[j]=p;
        }
        discos.disco[i] = dn;
    }
    //cout<<sizeof(Cmount)<<endl;
    //cout<<sizeof(discos)<<endl;

    fseek(archivo,0,SEEK_SET);
    fwrite(&discos, sizeof(discos), 1, archivo);
    fclose(archivo);
    this->archivoCreado = true;
    return 0;
}

Particion obj_mount::buscarParticion(){
    int pos;
    int sizeName;
    int j;
    int posExtendida;
    bool logicaEncontrada;
    string nombrePart;
    Particion particion;
    FILE *disco;

    //Obtener el size del nombre e inicializar las posiciones
    sizeName = this->name.length();
    logicaEncontrada = false;
    posExtendida = -1;
    pos = -1;
    nombrePart = "";
    j = 0 ;

    //Buscar el disco y verificar si existe
    disco =fopen(this->path.c_str(),"rb+");

    //Si el disco no existe retornara un null
    if (disco == NULL){
        //fclose(disco);
        particion.part_start = -1;
        return particion;
    }

    //Copiar el MBR
    fseek(disco, 0, SEEK_SET);
    fread(&this->mbr,sizeof(MBR),1,disco);

    //Buscar la particion

    //cout<<sizeName<<endl;
    for (int i = 0; i<4; i++){
        while(this->mbr.mbr_partitions[i].part_name[j]!=NULL && j<=15){
            nombrePart += toupper(this->mbr.mbr_partitions[i].part_name[j]);
            j++;
        }
        j = 0;
        /*
        for (int j = 0; j<sizeName;j++){
            nombrePart += this->mbr.mbr_partitions[i].part_name[j];
        }
        */

        //Todo a mayuscula
        string nameTemp = "";
        while(this->name[j]!=NULL && j<=15){
            nameTemp += toupper(this->name[j]);
            j++;
        }
        j = 0;
        this->name = nameTemp;

        if (this->mbr.mbr_partitions[i].part_type == 'E'){
            posExtendida = i;
        }

        if (nombrePart == this->name){
            pos = i;
            break;
        }else{
            nombrePart = "";
        }
    }

    if (nombrePart == ""){
        //Puede que no exista o que sea logica
        if (posExtendida == -1){
            //No existe una extendida por lo que no hay logicas y la particion no existe
            particion.part_start = -2;
            fclose(disco);
            return particion;
        }
        //Buscar dentro de las logicas

        //Cargar el ebr inicial
        fseek(disco, this->mbr.mbr_partitions[posExtendida].part_start, SEEK_SET);
        fread(&this->ebr,sizeof(EBR),1,disco);

        //Verificar si existe una particion logica
        if (this->ebr.part_status=='0' && this->ebr.part_next == -1){
            //No hay particiones logicas
            particion.part_start = -2;
            fclose(disco);
            return particion;
        }
        while (true){
                while(this->ebr.part_name[j]!= NULL && j<=15){
                    nombrePart += this->ebr.part_name[j];
                    j++;
                }
                j=0;
                /*
                for (int j = 0; j<sizeName;j++){
                    nombrePart += this->ebr.part_name[j];
                }
                */
                if (nombrePart == this->name){
                    logicaEncontrada = true;
                    break;
                }else{
                    nombrePart = "";
                    if (this->ebr.part_next == -1){
                        //No hay mas particiones
                        break;
                    }
                    fseek(disco, this->ebr.part_next, SEEK_SET);
                    fread(&this->ebr,sizeof(EBR),1,disco);
                    if (this->ebr.part_status=='0'){
                        break;
                    }
                }
            if (logicaEncontrada){
                break;
            }
        }

        if (logicaEncontrada){
            particion.part_start = this->ebr.part_start;
            particion.part_type = 'L';
        }else{
            particion.part_start = -2;
            particion.part_type = 'L';
        }

    }else{
        particion.part_start = pos;
        particion.part_type = 'P';
    }
    fclose(disco);
    return particion;
}

int obj_mount::getCurrentDir(){
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
        this->currentDir+= this->nombreArchivo;
        //cout<<this->currentDir<<endl;
    } else {
        perror("Error, el directorio no existe.");
        return -1;
    }
    return 0;
}

bool obj_mount::estaMontada(){
    //Recorrer cmount y luego cada disco y particion buscando la que este montada
    int i = 0;
    string nombre = "";

    while(i<29){
        //Validar si es el disco que estamos buscando
        if (this->path == this->cmount.disco[i].path){
            //Buscar la particion por nombre
            for (int j=0; j < 49;j++){
                nombre = this->nameToString(i,j);
                if (this->name == nombre){
                    if (this->cmount.disco[i].particiones[j].estado == 1){
                        //Ya esta montado
                        return true;
                    }else{
                        //No esta montado, solo es data rezagada
                        return false;
                    }
                }
            }
        }
        i++;
    }
    return false;

}

int obj_mount::estaMontado(){

    for (int i = 0; i< 29;i++){
        if (this->cmount.disco[i].path == this->path){
            return i;
        }
    }
    return -1;
}

string obj_mount::nameToString(int disco, int particion){
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


void obj_mount::imprimirParticiones(){
    //Recorrer la lista e ir imprimiendo todas las particiones
    //this->cmount.disco[i]
    string nombre,id,disco;
    for (int i=0;i< 29;i++){
        disco = this->cmount.disco[i].path;
        if (this->cmount.disco[i].estado == 1){
            for (int j=0;j<49;j++){
                if (this->cmount.disco[i].particiones[j].estado == 1){
                    id = this->cmount.disco[i].particiones[j].id;
                    id = id.substr(0,id.length()-1);
                    nombre = this->cmount.disco[i].particiones[j].name;
                    cout<<disco<<"|"<<nombre<<"|"<<id<<endl;
                }
            }
        }
    }
}
