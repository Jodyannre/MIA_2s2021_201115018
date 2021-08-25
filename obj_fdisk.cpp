#include "obj_fdisk.h"

obj_fdisk::obj_fdisk()
{

    this->size =-1;
    this->f=-1;
    this->path="";
    this->u=-1;
    this->type=-1;
    this->eliminar=0;
    this->name="";
    this->add=0;
    this->tipo_eliminar = -1;
    this->ebr_sig = -1;
    this->extendida = 0;
    this->pos_extendida = -1;

}

void obj_fdisk::ejecutar(){
    cout<<"si entro"<<endl;
    FILE *disco;
    char unidades,tipoParticion,tipoFit;
    int particion_size;
    //Buscar el disco y verificar si existe
    disco =fopen(this->path.c_str(),"rb+");

    //Si el disco no existe retornara un null
    if (disco == NULL){
        cout<<"Error, el disco no existe o la ruta es incorrecta"<<endl;
        return;
    }

    //Buscar la posicion del mbr del disco
    fseek(disco, 0, SEEK_SET);
    //MBR para copiar temporalmente el mbr que contiene el disco
    //MBR mbr_temp;
    //Copiar el mbr del disco al mbr temporal
    fread(&this->mbr_temp,sizeof(MBR),1,disco);
    this->pos_extendida = this->buscarExtendida();
    if (this->pos_extendida != -1){
        fseek(disco,this->mbr_temp.mbr_partitions[this->pos_extendida].part_start, SEEK_SET);
        fread(&this->ebr_temp,sizeof(EBR),1,disco);
        this->extendida = true;
    }



    //Validar todas las variables

    if(this->size == -1 && this->eliminar != true){
        printf("Error, no se ha ingresado un size para la particion. \n");
        return;
    }

    if(this->path == ""){
        printf("Error, no se ha ingresado una ruta valida. \n");
        return;
    }
    if(this->name == ""){
        printf("Error, no se ha ingresado un nombre valido. \n");
        return;
    }


    //Verificar las unidades
    /*
     *Para el fit
     * 0 para B
     * 1 para K
     * 2 para M
    */
    switch(this->u){
        case 0:
            unidades = 'B';
            particion_size = this->size;
            break;
        case 1:
            unidades = 'K';
            particion_size = this->size * 1024;
            break;
        case 2:
            unidades = 'M';
            particion_size = this->size * 1024 * 1024;
            break;
        default:
            unidades = 'K';
            this->u = 1;
            particion_size = this->size * 1024;
            break;
    }

    //Verificar el tipo
    /*
     *Para el fit
     * 0 para P
     * 1 para E
     * 2 para L
    */
    switch(this->type){
        case 0:
            tipoParticion = 'P';
            break;
        case 1:
            tipoParticion = 'E';
            break;
        case 2:
            tipoParticion = 'L';
            break;
        default:
            tipoParticion = 'P';
            this->type = 0;
            break;
    }

    //Verificar el ajuste
    /*
     *Para el fit
     * 0 para B
     * 1 para F
     * 2 para W
    */
    switch(this->f){
        case 0:
            tipoFit = 'B';
            break;
        case 1:
            tipoFit = 'F';
            break;
        case 2:
            tipoFit = 'W';
            break;
        default:
            this->f = 2;
            tipoFit = 'W';
            break;
    }


    //verificar si se va a eliminar una particion

    if (this->eliminar == true && this->tipo_eliminar == -1){
        printf("Error, no se ingreso el tipo para eliminar la particion");
    }

    //Verificar si se va a eliminar o a agregar espacio
    if (this->eliminar == true || this->add == true){
        //Eliminar o agregar

        if (this->eliminar == true){
            int resultado = this->eliminarParticion();
            return;
        }else{
            int resultado = this->agregarEspacio(particion_size,this->type);
            if (resultado == -1){
                return;
            }
        }

    }else if (this->type == 0){
        cout<<"Tratando de crear una particion"<<endl;
        int particion_pos = buscarParticionVacia(0);
        cout<<particion_pos<<endl;
        int partStart = 0;
        if (particion_pos != -1){
            //Buscar espacio disponible para la particion
            partStart = calcularPartStart(particion_size,0);
            cout<<endl;
            cout << "partStart"<<endl;
            cout<<endl;
            cout<<partStart<<endl;
            cout<<endl;
            cout << "particion Pos"<<endl;
            cout<<endl;
            cout<<particion_pos<<endl;
            cout<<endl;
            //return;
            if (partStart != -1){
                this->mbr_temp.mbr_partitions[particion_pos].part_start=partStart;
            }else{
                printf("Error, no hay espacio disponible para crear la particion del tamano solicitado.");
                return;
            }
            //Crear particiones primarias
            //Colocar la metada de la nueva particion
            this->mbr_temp.mbr_partitions[particion_pos].part_fit = tipoFit;
            this->mbr_temp.mbr_partitions[particion_pos].part_type = tipoParticion;
            strcpy(this->mbr_temp.mbr_partitions[particion_pos].part_name,this->name.c_str());
            this->mbr_temp.mbr_partitions[particion_pos].part_size = particion_size;
            this->mbr_temp.mbr_partitions[particion_pos].part_status='1';
        }else{
            printf("No se puede crear mas particiones.");
        }
    }else if (this->type == 1){
        //Particion extendida
        cout<<"Tratando de crear una particion extendida"<<endl;
        int particion_pos = buscarParticionVacia(1);
        cout<<particion_pos<<endl;
        int partStart = 0;
        if (particion_pos != -1){
            //Buscar espacio disponible para la particion
            partStart = calcularPartStart(particion_size,1);
            cout<<endl;
            cout << "partStart"<<endl;
            cout<<partStart<<endl;
            cout << "particion Pos"<<endl;
            cout<<particion_pos<<endl;

            //return;
            if (partStart != -1){
                this->mbr_temp.mbr_partitions[particion_pos].part_start=partStart;
            }else{
                printf("Error, no se puede crear mas de 1 particion extendida.");
                return;
            }
            //Crear particiones extendidas
            //Colocar la metada de la nueva particion
            this->mbr_temp.mbr_partitions[particion_pos].part_fit = tipoFit;
            this->mbr_temp.mbr_partitions[particion_pos].part_type = tipoParticion;
            strcpy(this->mbr_temp.mbr_partitions[particion_pos].part_name,this->name.c_str());
            this->mbr_temp.mbr_partitions[particion_pos].part_size = particion_size;
            this->mbr_temp.mbr_partitions[particion_pos].part_status='1';
            //Ordenar particiones
            this->ordenarParticiones();

            //Agregar EBR
            EBR ebr;
            ebr.part_fit = ' ';
            ebr.part_name[0] = ' ';
            ebr.part_next = -1;
            ebr.part_size = -1;
            ebr.part_start = mbr_temp.mbr_partitions[particion_pos].part_start;
            ebr.part_status = '0';

            //Agregar el ebr al disco en la posicion inicial de la particion extendida
            fseek(disco,this->mbr_temp.mbr_partitions[particion_pos].part_start,SEEK_SET);
            fwrite(&ebr, sizeof(EBR), 1, disco);
            //fclose(disco);

            //Editar MBR
            fseek(disco,0,SEEK_SET);
            fwrite(&this->mbr_temp, sizeof(MBR), 1, disco);
            fclose(disco);
            return;


        }else{
            printf("Error, no se pueden crear mas particiones.");
            return;
        }

    }else if (this->type == 2){
        //Crear particiones logicas
        if (this->extendida == false){
            printf("No existe una particion extendida en este disco.");
            return;
        }
        cout<<"Tratando de crear una particion Logica"<<endl;
        int partStart = 0;
        EBR resultado = calcularPartStartLogica(particion_size);
        partStart = resultado.part_start;
        cout<<endl;
        cout << "partStart"<<endl;
        cout<<partStart<<endl;
        cout<<endl;

        //Agregar EBR
        EBR ebr;
        ebr.part_fit = tipoFit;
        strcpy(ebr.part_name,this->name.c_str());
        ebr.part_next = resultado.part_next;
        ebr.part_size = particion_size;
        ebr.part_start = resultado.part_start;
        ebr.part_status = '1';
        //Agregar el ebr al disco en la posicion inicial de la particion extendida
        fseek(disco,partStart,SEEK_SET);
        fwrite(&ebr, sizeof(EBR), 1, disco);
        fclose(disco);
        return;


    }else{
        printf("No se puede crear mas particiones.");
    }

    //Ordenar particiones
    this->ordenarParticiones();
    //Editar MBR
    fseek(disco,0,SEEK_SET);
    fwrite(&this->mbr_temp, sizeof(MBR), 1, disco);
    fclose(disco);



}


void obj_fdisk::ordenarParticiones(){
    Particion actual,anterior;
    for (int i = 0; i < 4; i++){
        anterior = this->mbr_temp.mbr_partitions[i];
        if (anterior.part_start == -1){
            break;
        }
        for (int j = i; j < 4; j++){
            actual = this->mbr_temp.mbr_partitions[j];
            if (actual.part_start == -1){
                break;
            }
            if (actual.part_start < anterior.part_start){
                this->mbr_temp.mbr_partitions[i] = this->mbr_temp.mbr_partitions[j];
                this->mbr_temp.mbr_partitions[j] = anterior;
            }
        }
    }
}

int obj_fdisk::eliminarParticion(){
    int pos = -1;
    int sizeName = this->name.length();
    string nombrePart = "";

    cout<<sizeName<<endl;
    for (int i = 0; i<4; i++){
        for (int j = 0; j<sizeName;j++){
            nombrePart += this->mbr_temp.mbr_partitions[i].part_name[j];
        }

        if (nombrePart == this->name){
            pos = i;
            break;
        }else{
            nombrePart = "";
        }
    }

    if (nombrePart == ""){
        int resultadoLogica = this->eliminarParticionLogica();

        if (resultadoLogica == -1){
            cout<<"Error, la particion no existe."<<endl;
            return -1;
        }else{
            cout<<"Particion eliminada con exito."<<endl;
            return 0;
        }

    }

    //Borrar todo lo que tenga la particion


    //Modificar la metadata
    Particion p1;
    p1.part_status ='0';
    p1.part_type =' ';
    p1.part_fit =' ';
    p1.part_start = -1;
    p1.part_size = -1;
    p1.part_name[0] = ' ';
    //mbr.mbr_partitions[0] = p1;

    for (int i = pos; i<4; i++){
        if (i+1<4){
            this->mbr_temp.mbr_partitions[i]=this->mbr_temp.mbr_partitions[i+1];
        }
    }
    this->mbr_temp.mbr_partitions[3] = p1;
    return 0;
}


int obj_fdisk::eliminarParticionLogica(){
    int sizeName = this->name.length();
    string nombrePart = "";
    bool validador = true;

    cout<<sizeName<<endl;
    EBR ebr_anterior;
    EBR ebr_actual;

    FILE *disco;
    disco =fopen(this->path.c_str(),"rb+");

    fseek(disco, this->mbr_temp.mbr_partitions[this->pos_extendida].part_start, SEEK_SET);
    fread(&ebr_actual,sizeof(EBR),1,disco);

    //Verificar si existe alguna particion logica
    if(ebr_actual.part_status == -1 && ebr_actual.part_next == -1){
        printf("No hay particiones logicas.");
        return -1;
    }


    while(validador){
        //Iterar entre todas las particiones hasta encontrar la que concuerde con el nombre

        //Primero conseguir el nombre de la particion
        for (int i = 0; i<sizeName;i++){
            nombrePart += ebr_actual.part_name[i];
        }
        if (nombrePart == this->name){
            //Validar que no sea la primara
            if (ebr_actual.part_start == this->mbr_temp.mbr_partitions[this->pos_extendida].part_start){
                //Es la primera
                ebr_actual.part_fit = ' ';
                for (int i= 0 ; i <16;i++){
                    ebr_actual.part_name[i] = ' ';
                }
                ebr_actual.part_size = -1;
                ebr_actual.part_status = '0';
                //FILE *disco;
                //disco =fopen(this->path.c_str(),"rb+");
                //fseek(disco, ebr_actual.part_start, SEEK_SET);
                //fread(&ebr,sizeof(EBR),1,disco);
                fseek(disco,ebr_actual.part_start, SEEK_SET);
                fwrite(&ebr_actual, sizeof(EBR), 1, disco);
                fclose(disco);
                return 0;
            }else{
                //Tengo los 2 punteros y se va a eliminar el actual
                //Redireccionar los punteros
                ebr_anterior.part_next = ebr_actual.part_next;

                //Aqui deberia estar el metodo para eliminar la particion
                //--------------------------------------
                fseek(disco,ebr_anterior.part_start, SEEK_SET);
                fwrite(&ebr_anterior, sizeof(EBR), 1, disco);
                fclose(disco);
                return 0;
            }

        }
        //Validar que exista una next particion
        if (ebr_actual.part_next == -1){
            printf("La particion que se desea eliminar no existe.");
            fclose(disco);
            return -1;
        }
        //Actualizar los punteros
        ebr_anterior = ebr_actual;
        fseek(disco,ebr_actual.part_next, SEEK_SET);
        fread(&ebr_actual,sizeof(EBR),1,disco);
        nombrePart ="";
    }
    return -1;
}


int obj_fdisk::agregarEspacio(int size, int tipoParticion){
    int pos = -1;
    int sizeName = this->name.length();
    string nombrePart = "";
    FILE *disco;
    disco =fopen(this->path.c_str(),"rb+");

    cout<<sizeName<<endl;
    for (int i = 0; i<4; i++){
        for (int j = 0; j<sizeName;j++){
            nombrePart += this->mbr_temp.mbr_partitions[i].part_name[j];
        }

        if (nombrePart == this->name){
            pos = i;
            break;
        }else{
            nombrePart = "";
        }
    }

    if (nombrePart == ""){
        int resultadoLogica = this->addParticionLogica(size);

        if (resultadoLogica == -1){
            cout<<"Error, la particion no existe."<<endl;
            return -1;
        }else{
            cout<<"Instruccion ejecutada con exito."<<endl;
            return 0;
        }

    }
    if (pos == -1){
        cout<<"Error, la particion no existe."<<endl;
        return -1;
    }

    if (size > 0){
        Particion particion = this->mbr_temp.mbr_partitions[pos];
        Particion particion_sig = this->mbr_temp.mbr_partitions[pos+1];
        if (pos < 3){
            //No es la ultima
            if (size < 0){
                if (particion.part_size > (size*-1) && ((particion.part_size+size)> sizeof(MBR)) ){
                    //Si hay espacio
                    this->mbr_temp.mbr_partitions[pos].part_size-= size;
                }else{
                    //No hay espacio
                    cout<<"Error, no hay suficiente espacio disponible."<<endl;
                    return -1;
                }
            }
            if (particion_sig.part_status == '1'){
                //Si hay mas particiones
                if (size > (particion.part_start+particion.part_size - particion_sig.part_start)){
                    //Si hay espacio
                }else{
                    //No hay espacio
                    cout<<"Error, no hay suficiente espacio disponible."<<endl;
                    return -1;
                }

            }else{
                //No tiene mas particiones por delante
                if (this->ebr_temp.part_size-(particion.part_start+particion.part_size) > size){
                   //Si hay espacio
                    this->mbr_temp.mbr_partitions[pos].part_size-= size;

                }else{
                    //No hay espacio
                    cout<<"Error, no hay suficiente espacio disponible."<<endl;
                    return -1;
                }
            }

        }else{
            //Es la ultima
            if (size < 0){
                if (particion.part_size > (size*-1) && ((particion.part_size+size)> sizeof(MBR)) ){
                    //Si hay espacio
                    this->mbr_temp.mbr_partitions[pos].part_size-= size;
                }else{
                    //No hay espacio
                    cout<<"Error, no hay suficiente espacio disponible."<<endl;
                    return -1;
                }
            }

            if (this->ebr_temp.part_size-(particion.part_start+particion.part_size) > size){
               //Si hay espacio
                this->mbr_temp.mbr_partitions[pos].part_size+= size;
            }else{
                //No hay espacio
                cout<<"Error, no hay suficiente espacio disponible."<<endl;
                return -1;
            }
        }
    }else{
        cout<<"Error, no se ingreso ninguna cantidad valida."<<endl;
        return -1;
    }
    return 0;
sdasdasdasdasdasd
}


int obj_fdisk::agregarEspacioLogica(int size){
    return -1;
}


int obj_fdisk::calcularPartStart(int size, int tipo_particion){
    // Primero verificar que haya alguna particion
    if (tipo_particion == 0 || tipo_particion == 1){
        Particion part_actual;
        Particion part_ant = mbr_temp.mbr_partitions[0];
        int espacioDisponible = 0;
        int espacioEntreParticion = 0;

        //validar espacio inicial
        if (part_ant.part_start != 136){
            espacioEntreParticion = part_ant.part_start - sizeof(MBR);
            if (espacioEntreParticion >= size){
                return sizeof(MBR);
            }
        }

        for (int i= 1; i<4;i++){
            if (this->mbr_temp.mbr_partitions[i].part_status!='0'){
                part_actual = this->mbr_temp.mbr_partitions[i];
                espacioEntreParticion = part_actual.part_start - (part_ant.part_start + part_ant.part_size);
                cout<<espacioEntreParticion<<endl;
                if (espacioEntreParticion >= size){
                    return part_ant.part_start + part_ant.part_size;
                }else{
                    part_ant = part_actual;
                }
            }
         }
        if (part_ant.part_start == -1){
            return sizeof(MBR);
        }
        espacioDisponible = this->mbr_temp.mbr_tamano - (part_ant.part_start + part_ant.part_size);
        if (espacioDisponible > size){
            return part_ant.part_start + part_ant.part_size;
        }else{
            return -1;
        }
    }

}


EBR obj_fdisk::calcularPartStartLogica(int size){

    int part_sig = this->ebr_temp.part_next;
    int part_ant = this->ebr_temp.part_start;
    bool validador = true;

    //validar espacio inicial
    if (this->ebr_temp.part_status == '0'){
        //Verificar el size
        if (part_sig!= -1){
            FILE *disco;
            disco =fopen(this->path.c_str(),"rb+");
            EBR ebr;
            fseek(disco, part_sig, SEEK_SET);
            fread(&ebr,sizeof(EBR),1,disco);
            if (size >= ebr.part_start - part_ant){
                EBR resultado;
                resultado.part_start = part_ant;
                resultado.part_next = part_sig;
                fclose(disco);
                return resultado;
            }
            fclose(disco);
        }else{
            EBR resultado;
            resultado.part_start = part_ant;
            resultado.part_next = -1;
            return resultado;
        }
    }

    //Validar que la siguiente exista
    if (part_sig == -1){
        EBR resultado;
        FILE *disco;
        disco =fopen(this->path.c_str(),"rb+");
        EBR ebr;
        fseek(disco, part_ant, SEEK_SET);
        fread(&ebr,sizeof(EBR),1,disco);
        resultado.part_start = ebr.part_start+ebr.part_size;
        resultado.part_next = -1;
        ebr.part_next = resultado.part_start;
        fseek(disco,ebr.part_start, SEEK_SET);
        fwrite(&ebr, sizeof(EBR), 1, disco);
        fclose(disco);
        return resultado;
    }

    //Validar los siguientes hasta encontrar un espacio
    FILE *disco;
    disco =fopen(this->path.c_str(),"rb+");
    EBR ebr;
    EBR ebr_ant;
    while (validador){
        fseek(disco, part_ant, SEEK_SET);
        fread(&ebr_ant,sizeof(EBR),1,disco);
        fseek(disco, part_sig, SEEK_SET);
        fread(&ebr,sizeof(EBR),1,disco);
        if (ebr.part_start - (part_ant+ebr_ant.part_size)>=size){
            EBR resultado;
            resultado.part_start = part_ant+ebr_ant.part_size;
            resultado.part_next = ebr.part_start;
            ebr_ant.part_next = resultado.part_start;
            //ebr.part_next = ebr.part_start;
            fseek(disco,ebr_ant.part_start, SEEK_SET);
            fwrite(&ebr_ant, sizeof(EBR), 1, disco);
            fseek(disco,ebr.part_start, SEEK_SET);
            fwrite(&ebr, sizeof(EBR), 1, disco);
            fclose(disco);
            return resultado;
        }

        //part_sig = ebr.part_next;
        if (ebr.part_next == -1){
            EBR resultado;
            ebr.part_next=ebr.part_start+ebr.part_size;
            resultado.part_start = ebr.part_start+ebr.part_size;
            resultado.part_next = -1;
            fseek(disco,ebr.part_start, SEEK_SET);
            fwrite(&ebr, sizeof(EBR), 1, disco);
            fclose(disco);
            return resultado;
        }
        part_ant = part_sig;
        part_sig = ebr.part_next;
    }

}




int obj_fdisk::buscarParticionVacia(int tipo_particion){
    /*
     *  Errores
     *  -1 cuando no se pueden crear mas particiones
     *  -2 cuando ya existe una extendida y no se pueden crear mas
     *  -3 cuando no existe una extendida y se quiere crear una logica
    */

    if (tipo_particion==0){
        for (int i= 0; i<4;i++){
            if (this->mbr_temp.mbr_partitions[i].part_status=='0'){
                return i;
            }
        }
        return -1;

    }else if (tipo_particion == 1){
        for (int i= 0; i<4;i++){
            if (this->mbr_temp.mbr_partitions[i].part_type == 'E'){
                return -2;
            }
        }
        for (int i= 0; i<4;i++){
            if (this->mbr_temp.mbr_partitions[i].part_status=='0'){
                return i;
            }
        }
    }else{
        for (int i= 0; i<4;i++){
            if (this->mbr_temp.mbr_partitions[i].part_type == 'E'){
                return i;
            }
        }
        return -3;
    }

    return -1;
}


int obj_fdisk::buscarExtendida(){
    for (int i = 0; i<4;i++){
        if (this->mbr_temp.mbr_partitions[i].part_type=='E'){
            this->extendida = true;
            return i;
        }
    }
    //No existe
    return -1;
}

string obj_fdisk::obtenerNombre(int particion, int extendida){
    int pos = -1;
    int sizeName = this->name.length();
    string nombrePart = "";

    if (extendida != -1 ){

        for (int j = 0; j<sizeName;j++){
            nombrePart += this->mbr_temp.mbr_partitions[particion].part_name[j];
        }
    }else{
        EBR ebrInicial;
        EBR ebrTemp;
        bool encontrado = false;
        FILE *disco;
        //Copiar el EBR inicial
        disco =fopen(this->path.c_str(),"rb+");
        fseek(disco, this->mbr_temp.mbr_partitions[extendida].part_start, SEEK_SET);
        fread(&ebrInicial,sizeof(EBR),1,disco);

        for (int j = 0; j<sizeName;j++){
            nombrePart += this->mbr_temp.mbr_partitions[particion].part_name[j];
        }

       fclose(disco);
    }

}



void obj_fdisk::mostrarDatos(){

    cout<<this->size<<endl;
    cout<<endl;
    cout<<this->f<<endl;
    cout<<endl;
    cout<<this->path<<endl;
    cout<<endl;
    cout<<this->u<<endl;
    cout<<endl;
    cout<<this->type<<endl;
    cout<<endl;
    cout<<this->eliminar<<endl;
    cout<<endl;
    cout<<this->name<<endl;
    cout<<endl;
    cout<<this->add<<endl;
    cout<<endl;

}

