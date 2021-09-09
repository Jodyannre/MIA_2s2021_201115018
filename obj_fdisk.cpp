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
    //cout<<"si entro"<<endl;
    FILE *disco;
    char unidades,tipoParticion,tipoFit;
    int particion_size;
    //Buscar el disco y verificar si existe
    disco =fopen(this->path.c_str(),"rb+");

    //Si el disco no existe retornara un null
    if (disco == NULL){
        cout<<"Error, el disco no existe o la ruta es incorrecta"<<endl;
        //fclose(disco);
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
        fclose(disco);
        return;
    }

    if(this->path == ""){
        printf("Error, no se ha ingresado una ruta valida. \n");
        fclose(disco);
        return;
    }
    if(this->name == ""){
        printf("Error, no se ha ingresado un nombre valido. \n");
        fclose(disco);
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
        printf("Error, no se ingreso el tipo para eliminar la particion \n");
    }

    //Verificar si se va a eliminar o a agregar espacio
    if (this->eliminar == true || this->add == true){
        //Eliminar o agregar

        if (this->eliminar == true){
            int resultado = this->eliminarParticion(particion_size);
            fclose(disco);
            return;
        }else{
            int resultado = this->agregarEspacio(particion_size,this->type);
            if (resultado == -1){
                fclose(disco);
                return;
            }
            fclose(disco);
            return;
        }

    }else if (this->type == 0){
        //cout<<"Tratando de crear una particion"<<endl;
        int particion_pos = buscarParticionVacia(0);
        //cout<<particion_pos<<endl;
        int partStart = 0;
        if (particion_pos != -1 && particion_pos != -2){
            //Buscar espacio disponible para la particion
            partStart = calcularPartStart(particion_size,0,this->mbr_temp.disk_fit[0]);
            //cout<<endl;
            //cout << "partStart"<<endl;
            //cout<<endl;
            //cout<<partStart<<endl;
            //cout<<endl;
            //cout << "particion Pos"<<endl;
            //cout<<endl;
            //cout<<particion_pos<<endl;
            //cout<<endl;
            //return;
            if (partStart != -1){
                this->mbr_temp.mbr_partitions[particion_pos].part_start=partStart;
            }else{
                printf("Error, no hay espacio disponible para crear la particion del tamano solicitado. \n");
                fclose(disco);
                return;
            }
            //Crear particiones primarias
            //Colocar la metada de la nueva particion
            this->mbr_temp.mbr_partitions[particion_pos].part_fit = tipoFit;
            this->mbr_temp.mbr_partitions[particion_pos].part_type = tipoParticion;
            strcpy(this->mbr_temp.mbr_partitions[particion_pos].part_name,this->name.c_str());
            this->mbr_temp.mbr_partitions[particion_pos].part_size = particion_size;
            this->mbr_temp.mbr_partitions[particion_pos].part_status='1';

            //Verificar si hay suficiente espacio para crearla
            if (this->mbr_temp.mbr_partitions[particion_pos].part_start + this->mbr_temp.mbr_partitions[particion_pos].part_size
                    > this->mbr_temp.mbr_tamano){
                cout<<"Error, la particion no se puede crear ya que excede la capacidad del disco. \n";
                fclose(disco);
                return;
            }

        }else if (particion_pos == -2){
            printf("Error, no se puede crear mas de 1 particion extendida. \n");
            fclose(disco);
            return;
        }
        else{
            printf("Error, no se puede crear mas particiones. \n");
            fclose(disco);
            return;
        }
    }else if (this->type == 1){
        //Particion extendida
        //cout<<"Tratando de crear una particion extendida"<<endl;
        int particion_pos = buscarParticionVacia(1);
        //cout<<particion_pos<<endl;
        int partStart = 0;
        if (particion_pos != -1 && particion_pos != -2){
            //Buscar espacio disponible para la particion
            partStart = calcularPartStart(particion_size,1,this->mbr_temp.disk_fit[0]);
            //cout<<endl;
            //cout << "partStart"<<endl;
            //cout<<partStart<<endl;
            //cout << "particion Pos"<<endl;
            //cout<<particion_pos<<endl;

            //Verificar que todavia exista espacio disponible
            if (partStart+particion_size > this->mbr_temp.mbr_tamano){
                cout<<"No hay espacio suficiente para crear esa particion. \n"<<endl;
                fclose(disco);
                return;
            }

            //return;
            if (partStart != -1 && partStart != -2){
                this->mbr_temp.mbr_partitions[particion_pos].part_start=partStart;
            }else if(partStart == -2){
                cout<<"No hay espacio suficiente para crear otra particion. \n"<<endl;
                fclose(disco);
                return;
            }else{
                printf("Error, no se puede crear mas de 1 particion extendida. \n");
                fclose(disco);
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

            //Verificar si hay suficiente espacio para crearla
            if (this->mbr_temp.mbr_partitions[particion_pos].part_start + this->mbr_temp.mbr_partitions[particion_pos].part_size
                    > this->mbr_temp.mbr_tamano){
                cout<<"Error, la particion no se puede crear ya que excede la capacidad del disco. \n";
                fclose(disco);
                return;
            }

            //Editar MBR
            fseek(disco,0,SEEK_SET);
            fwrite(&this->mbr_temp, sizeof(MBR), 1, disco);

            //Agregar el ebr al disco en la posicion inicial de la particion extendida
            fseek(disco,this->mbr_temp.mbr_partitions[particion_pos].part_start,SEEK_SET);
            fwrite(&ebr, sizeof(EBR), 1, disco);

            cout<<"Particion creada correctamente. \n"<<endl;
            fclose(disco);
            return;


        }else if (particion_pos == -2){
            printf("Error, no se puede crear mas de 1 particion extendida. \n");
            fclose(disco);
            return;
        }else{
            printf("Error, no se pueden crear mas particiones. \n");
            fclose(disco);
            return;
        }

    }else if (this->type == 2){
        //Crear particiones logicas
        if (this->extendida == false){
            printf("No existe una particion extendida en este disco. \n");
            fclose(disco);
            return;
        }
        //cout<<"Tratando de crear una particion Logica"<<endl;
        int partStart = 0;
        EBR resultado = calcularPartStartLogica(particion_size,this->mbr_temp.mbr_partitions[pos_extendida].part_fit);
        partStart = resultado.part_start;
        //cout<<endl;
        //cout << "partStart"<<endl;
        //cout<<partStart<<endl;
        //cout<<endl;

        if (partStart == -1){
            cout << "Error, la particion extendida no tiene suficiente espacio para crear la nueva particion logica. \n"<<endl;
            fclose(disco);
            return;
        }

        //Agregar EBR
        EBR ebr;
        ebr.part_fit = tipoFit;
        strcpy(ebr.part_name,this->name.c_str());
        ebr.part_next = resultado.part_next;
        ebr.part_size = particion_size;
        ebr.part_start = resultado.part_start;
        ebr.part_status = '1';


        //Agregar el ebr al disco en la posicion inicial de la particion extendida
        cout<<"Particion logica creada correctamente."<<endl;
        fseek(disco,partStart,SEEK_SET);
        fwrite(&ebr, sizeof(EBR), 1, disco);
        fclose(disco);
        return;


    }else{
        printf("No se puede crear mas particiones. \n");
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

int obj_fdisk::eliminarParticion(int size){
    int pos = -1;
    int sizeName = this->name.length();
    int j = 0;
    string nombrePart = "";
    FILE *disco;
    //cout<<sizeName<<endl;

    //Todo a mayusculas
    string nameTemp="";
    while(this->name[j] != NULL && j <= 15){
        nameTemp += toupper(this->name[j]);
        j++;
    }
    j=0;
    this->name = nameTemp;

    for (int i = 0; i<4; i++){
        while(this->mbr_temp.mbr_partitions[i].part_name[j] != NULL && j <= 15){
            nombrePart += toupper(this->mbr_temp.mbr_partitions[i].part_name[j]);
            j++;
        }
        j=0;

        //Todo a mayusculas



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
            cout<<"Error, la particion no existe. \n"<<endl;
            return -1;
        }else if (resultadoLogica == -2){
            return 0;
        }
        else{
            cout<<"Particion eliminada con exito. \n"<<endl;
            return 0;
        }

    }

    //---------------------------------------------------------------------------------
    cout<<"Desea continuar con la eliminacion de la particion ingresada? (y/n)\n"<<endl;
    string confirmacion="";
    cin>>confirmacion;
    //confirmacion = "y";
    if (confirmacion =="y" || confirmacion =="Y"){
       printf( "Particion eliminada. \n" );

    }else if (confirmacion =="n" || confirmacion =="N"){
        printf( "La particion no fue eliminada. \n" );
        return 0;
    }
    //---------------------------------------------------------------------------------

    //Borrar todo lo que tenga la particion
    if (this->mbr_temp.mbr_partitions[pos].part_type=='E'){
        int ultimaLogica = this->getUltimaLogica();
        if (this->mbr_temp.mbr_partitions[pos].part_size - (size*-1) < ultimaLogica){
            cout<<"Error, no se puede reducir esa cantidad, ya que la particion tiene otras particiones logicas. \n"<<endl;
            return -1;
        }
    }

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
        if (i+1<5){
            this->mbr_temp.mbr_partitions[i]=this->mbr_temp.mbr_partitions[i+1];
        }
    }
    this->mbr_temp.mbr_partitions[3] = p1;
    disco =fopen(this->path.c_str(),"rb+");
    fseek(disco,0,SEEK_SET);
    fwrite(&this->mbr_temp, sizeof(MBR), 1, disco);
    fclose(disco);
    return 0;
}


int obj_fdisk::eliminarParticionLogica(){
    int sizeName = this->name.length();
    int j = 0;
    string nombrePart = "";
    bool validador = true;

    //cout<<sizeName<<endl;
    EBR ebr_anterior;
    EBR ebr_actual;

    FILE *disco;
    disco =fopen(this->path.c_str(),"rb+");

    fseek(disco, this->mbr_temp.mbr_partitions[this->pos_extendida].part_start, SEEK_SET);
    fread(&ebr_actual,sizeof(EBR),1,disco);

    //Verificar si existe alguna particion logica
    if(ebr_actual.part_status == -1 && ebr_actual.part_next == -1){
        printf("No hay particiones logicas. \n");
        return -1;
    }

    //Todo a mayusculas
    string nameTemp="";
    while(this->name[j] != NULL && j <= 15){
        nameTemp += toupper(this->name[j]);
        j++;
    }
    j=0;
    this->name = nameTemp;

    while(validador){
        //Iterar entre todas las particiones hasta encontrar la que concuerde con el nombre

        //Primero conseguir el nombre de la particion
        while(ebr_actual.part_name[j]!= NULL && j <= 15){
            nombrePart += toupper(ebr_actual.part_name[j]);
            j++;
        }
        j = 0;

        if (nombrePart == this->name){
            //---------------------------------------------------------------------------------
            cout<<"Desea continuar con la eliminacion de la particion ingresada? (y/n)\n"<<endl;
            string confirmacion="";
            cin>>confirmacion;
            //confirmacion = "y";
            if (confirmacion =="y" || confirmacion =="Y"){
               printf( "Particion eliminada. \n" );

            }else if (confirmacion =="n" || confirmacion =="N"){
                printf( "La particion no fue eliminada. \n" );
                fclose(disco);
                return -2;
            }
            //---------------------------------------------------------------------------------
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
    fclose(disco);
    return -1;
}


int obj_fdisk::agregarEspacio(int size, int tipoParticion){
    int pos = -1;
    int j = 0;
    int sizeName = this->name.length();
    string nombrePart = "";
    FILE *disco;
    disco =fopen(this->path.c_str(),"rb+");
    //Obtener nombre
    //cout<<sizeName<<endl;

    //Todo a mayusculas
    string nameTemp="";
    while(this->name[j] != NULL && j <= 15){
        nameTemp += toupper(this->name[j]);
        j++;
    }
    j=0;
    this->name = nameTemp;

    for (int i = 0; i<4; i++){
        /*
        for (int j = 0; j<sizeName;j++){
            nombrePart += this->mbr_temp.mbr_partitions[i].part_name[j];
        }
        */
        while (this->mbr_temp.mbr_partitions[i].part_name[j] != NULL && j <= 15){
            nombrePart += toupper(this->mbr_temp.mbr_partitions[i].part_name[j]);
            j++;
        }
        j = 0;
        if (nombrePart == this->name){
            pos = i;
            break;
        }else{
            nombrePart = "";
        }
    }

    //Verificar si existe la particion o puede que sea logica
    if (nombrePart == ""){
        int resultadoLogica = this->agregarEspacioLogica(size);

        if (resultadoLogica == -1){
            cout<<"Error, la particion no existe. \n"<<endl;
            fclose(disco);
            return -1;
        }else{
            cout<<"Instruccion ejecutada con exito. \n"<<endl;
            fclose(disco);
            return 0;
        }

    }
    if (pos == -1){
        cout<<"Error, la particion no existe. \n"<<endl;
        fclose(disco);
        return -1;
    }

    //Verificar si el size ingresado es correcto
    if (size > 0 || size < 0){
        Particion particion = this->mbr_temp.mbr_partitions[pos];
        if (pos < 3){
            Particion particion_sig = this->mbr_temp.mbr_partitions[pos+1];
            //No es la ultima
            if (size < 0){
                if (particion.part_size > (size*-1) && ((particion.part_size+size)> sizeof(MBR)) ){
                    //Si hay espacio
                    this->mbr_temp.mbr_partitions[pos].part_size+= size;
                    fseek(disco,0,SEEK_SET);
                    fwrite(&this->mbr_temp, sizeof(MBR), 1, disco);
                    fclose(disco);
                    return 0;
                }else{
                    //No hay espacio
                    cout<<"Error, no hay suficiente espacio disponible. \n"<<endl;
                    fclose(disco);
                    return -1;
                }
            }
            if (particion_sig.part_status == '1'){
                //Si hay mas particiones
                if (size < (particion_sig.part_start - particion.part_start -particion.part_size)){
                    //Si hay espacio
                    this->mbr_temp.mbr_partitions[pos].part_size+= size;
                    fseek(disco,0,SEEK_SET);
                    fwrite(&this->mbr_temp, sizeof(MBR), 1, disco);
                    fclose(disco);
                    return 0;
                }else{
                    //No hay espacio
                    cout<<"Error, no hay suficiente espacio disponible. \n"<<endl;
                    fclose(disco);
                    return -1;
                }

            }else{
                //No tiene mas particiones por delante
                if (this->mbr_temp.mbr_tamano-(particion.part_start+particion.part_size) > size){
                   //Si hay espacio
                    this->mbr_temp.mbr_partitions[pos].part_size+= size;
                    fseek(disco,0,SEEK_SET);
                    fwrite(&this->mbr_temp, sizeof(MBR), 1, disco);
                    fclose(disco);
                    return 0;
                }else{
                    //No hay espacio
                    cout<<"Error, no hay suficiente espacio disponible. \n"<<endl;
                    fclose(disco);
                    return -1;
                }
            }

        }else{
            //Es la ultima
            if (size < 0){
                if (particion.part_size > (size*-1) ){
                    //Si hay espacio
                    int logica = getUltimaLogica();
                    if (logica == 0){
                        this->mbr_temp.mbr_partitions[pos].part_size-= size;
                        fseek(disco,0,SEEK_SET);
                        fwrite(&this->mbr_temp, sizeof(MBR), 1, disco);
                        fclose(disco);
                        return 0;
                    }

                }else{
                    //No hay espacio
                    cout<<"Error, no hay suficiente espacio disponible. \n"<<endl;
                    fclose(disco);
                    return -1;
                }
            }

            if (this->mbr_temp.mbr_tamano-(particion.part_start+particion.part_size) >= size){
               //Si hay espacio
                this->mbr_temp.mbr_partitions[pos].part_size+= size;
                fseek(disco,0,SEEK_SET);
                fwrite(&this->mbr_temp, sizeof(MBR), 1, disco);
                fclose(disco);
                return 0;
            }else{
                //No hay espacio
                cout<<"Error, no hay suficiente espacio disponible. \n"<<endl;
                fclose(disco);
                return -1;
            }
        }
    }else{
        cout<<"Error, no se ingreso ninguna cantidad valida. \n"<<endl;
        fclose(disco);
        return -1;
    }
    return 0;
}

int obj_fdisk::getUltimaLogica(){
    EBR logica;
    FILE *disco;
    int ultimaPos;
    disco =fopen(this->path.c_str(),"rb+");
    fseek(disco,this->mbr_temp.mbr_partitions[this->pos_extendida].part_start, SEEK_SET);
    fread(&logica,sizeof(EBR),1,disco);
    ultimaPos = logica.part_start;
    if (logica.part_status == '1'){
        while (true){
            if (logica.part_next != -1){
                ultimaPos = logica.part_next;
                fseek(disco,ultimaPos, SEEK_SET);
                fread(&logica,sizeof(EBR),1,disco);
            }else{
                fclose(disco);
                return ultimaPos + logica.part_size;
            }
        }
    }else{
        fclose(disco);
        return 0;
    }

}

int obj_fdisk::agregarEspacioLogica(int size){
    //Verificar si existe extendida
    if (this->pos_extendida == -1){
        //cout<<"Error, no existe ninguna particion extendida. \n"<<endl;
        return -1;
    }

    int sizeName = this->name.length();
    int j = 0;
    string nombrePart = "";
    FILE *disco;
    EBR ebr;
    EBR ebr_sig;
    //Cargar el EBR inicial de la particion extendida
    disco =fopen(this->path.c_str(),"rb+");
    fseek(disco,this->mbr_temp.mbr_partitions[this->pos_extendida].part_start, SEEK_SET);
    fread(&ebr,sizeof(EBR),1,disco);
    //Obtener nombre

    //Todo a mayusculas
    string nameTemp="";
    while(this->name[j] != NULL && j <= 15){
        nameTemp += toupper(this->name[j]);
        j++;
    }
    j=0;
    this->name = nameTemp;

    while(true){
    /*
        for (int j = 0; j<sizeName;j++){
            nombrePart += ebr.part_name[j];
        }
    */
        while (ebr.part_name[j] != NULL && j <= 15){
            nombrePart += toupper(ebr.part_name[j]);
            j++;
        }
        j= 0;
        if (nombrePart == this->name){
            break;
        }else{
            nombrePart = "";
            if (ebr.part_next == -1){
                break;
            }
            fseek(disco,ebr.part_next, SEEK_SET);
            fread(&ebr,sizeof(EBR),1,disco);
        }
    }
    //Verificar si existe la particion o puede que sea logica
    if (nombrePart == ""){
        cout<<"Error, la particion no existe. \n"<<endl;
        fclose(disco);
        return -1;
    }

    if (size < 0){
        //Size negativo
        if (ebr.part_size > size*-1){
            ebr.part_size+= size;
            fseek(disco,ebr.part_start,SEEK_SET);
            fwrite(&ebr, sizeof(EBR), 1, disco);
            fclose(disco);
            return 0;
        }else{
            //No hay espacio
            cout<<"Error, no hay suficiente espacio disponible. \n"<<endl;
            fclose(disco);
            return -1;
        }
    }else{
        //Size positivo
        if (ebr.part_next != -1){
            //Hay mas particiones
            //ebr.part_size-= size;
            fseek(disco,ebr.part_next,SEEK_SET);
            fread(&ebr_sig,sizeof(EBR),1,disco);
            if (ebr_sig.part_start - ebr.part_start-ebr.part_size >= size){
                ebr.part_size+= size;
                fseek(disco,ebr.part_start,SEEK_SET);
                fwrite(&ebr, sizeof(EBR), 1, disco);
                fclose(disco);
                return 0;
            }else{
                //No hay espacio
                cout<<"Error, no hay suficiente espacio disponible. \n"<<endl;
                fclose(disco);
                return -1;
            }
        }else{
            //No hay mas particiones
            if (this->mbr_temp.mbr_partitions[this->pos_extendida].part_size > size+ ebr.part_start + ebr.part_size){
                ebr.part_size+= size;
                fseek(disco,ebr.part_start,SEEK_SET);
                fwrite(&ebr, sizeof(EBR), 1, disco);
                fclose(disco);
                return 0;
            }else{
                //No hay espacio
                cout<<"Error, no hay suficiente espacio disponible. \n"<<endl;
                fclose(disco);
                return -1;
            }
        }
    }

    return -1;
}


int obj_fdisk::calcularPartStart(int size, int tipo_particion, char ajuste){
    // Primero verificar que haya alguna particion


    if (tipo_particion == 0 || tipo_particion == 1){
        Particion part_actual;
        Particion part_ant = mbr_temp.mbr_partitions[0];
        int espacioDisponible = 0;
        int espacioEntreParticion = 0;
        queue <Espacio> listaEspacio;

        //validar espacio inicial
        if (part_ant.part_start != 136 && part_ant.part_status == '1'){
            espacioEntreParticion = part_ant.part_start - sizeof(MBR);
            if (espacioEntreParticion > 0){
                Espacio espacio;
                espacio.anterior = this->ebr_temp;
                espacio.inicio = sizeof(MBR);
                espacio.size = espacioEntreParticion;
                espacio.libre = espacioEntreParticion - size;
                espacio.tipoParticion = 'P';
                listaEspacio.push(espacio);
            }
            if (ajuste == 'F'){
                if (espacioEntreParticion >= size){
                    return sizeof(MBR);
                }
            }
        }else if (part_ant.part_status != '1'){
            //No hay ninguna particion creada
            if (this->mbr_temp.mbr_tamano > size){
                return sizeof(MBR);
            }else{
                cout<<"Error, no hay particiones creadas en ese disco. \n"<<endl;
                return -1;
            }
        }

        if (ajuste != 'F'){
            for (int i=1;i<4;i++){
                part_actual = mbr_temp.mbr_partitions[i];
                if (part_actual.part_status == '1' && part_ant.part_status== '1'){
                    espacioEntreParticion = part_actual.part_start - part_ant.part_start - part_ant.part_size;
                    if (espacioEntreParticion > 0){
                        Espacio espacio;
                        espacio.anterior = this->ebr_temp;
                        espacio.inicio = part_ant.part_start + part_ant.part_size;
                        espacio.size = espacioEntreParticion;
                        espacio.libre = espacioEntreParticion - size;
                        espacio.tipoParticion = 'P';
                        listaEspacio.push(espacio);
                    }
                    part_ant = part_actual;
                }else{
                    continue;
                }

            }
            //Crear el espacio que queda al final
            Espacio espacio;
            espacio.anterior = this->ebr_temp;
            espacio.inicio = part_ant.part_start + part_ant.part_size;
            espacio.size = this->mbr_temp.mbr_tamano - part_ant.part_start - part_ant.part_size;
            espacio.libre = espacio.size - size;
            espacio.tipoParticion = 'P';
            listaEspacio.push(espacio);

            if (listaEspacio.empty()){
                //No se encontro ningun espacio pero al menos hay 1 particion
                if (this->mbr_temp.mbr_tamano > size+part_ant.part_start + part_ant.part_size){
                    return part_ant.part_start + part_ant.part_size;
                }else{              
                    return -2;
                }
            }
            Espacio temp;
            temp = listaEspacio.front();
            listaEspacio.pop();
            Espacio actual;
            while(!listaEspacio.empty()){
                actual = listaEspacio.front();
                listaEspacio.pop();
                if (ajuste == 'W'){
                    if (temp.size < actual.size){
                        temp = actual;
                    }

                }else if (ajuste == 'B'){
                    if ((temp.size > actual.size && actual.size >= size)
                            || (temp.size<size && actual.size >= size)){
                        temp = actual;
                    }
                }

            }
            if (temp.size > size){
                return temp.inicio;
            }else{
                //cout<<"No hay espacio suficiente para crear otra particion. \n"<<endl;
                return -1;
            }

        }



        for (int i= 1; i<4;i++){
            if (this->mbr_temp.mbr_partitions[i].part_status!='0'){
                part_actual = this->mbr_temp.mbr_partitions[i];
                espacioEntreParticion = part_actual.part_start - (part_ant.part_start + part_ant.part_size);
                //cout<<espacioEntreParticion<<endl;
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
            cout<<"No hay espacio suficiente para crear otra particion. \n"<<endl;
            return -1;
        }
    }

}


EBR obj_fdisk::calcularPartStartLogica(int size, char ajuste){

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
            //Si ni la primera existe
            if (ebr.part_status != '1'){
                if (sizeof(EBR)+ size < this->mbr_temp.mbr_partitions[pos_extendida].part_size){
                    EBR resultado;
                    resultado.part_start = this->mbr_temp.mbr_partitions[pos_extendida].part_start;
                    resultado.part_next = -1;
                    fclose(disco);
                    return resultado;
                }
            }

            if (size >= ebr.part_start - part_ant){
                EBR resultado;
                resultado.part_start = part_ant;
                resultado.part_next = part_sig;
                fclose(disco);
                return resultado;
            }
            fclose(disco);
        }else{
            if (ajuste == 'F'){
                EBR resultado;
                resultado.part_start = part_ant;
                resultado.part_next = -1;
                if (resultado.part_start + size > this->mbr_temp.mbr_partitions[this->pos_extendida].part_size){
                    //La particion no tiene tanto espacio para crearla
                    resultado.part_start = -1;
                    resultado.part_next = -1;
                    return resultado;
                }
                return resultado;
            }
        }
    }

    //Validar que la siguiente exista, sino tratar de crearla en la siguiente
    if (part_sig == -1){
        EBR resultado;
        FILE *disco;
        disco =fopen(this->path.c_str(),"rb+");
        EBR ebr;
        fseek(disco, part_ant, SEEK_SET);
        fread(&ebr,sizeof(EBR),1,disco);
        if (ebr.part_size == -1){
            resultado.part_start = ebr.part_start;
        }else{
            resultado.part_start = ebr.part_start+ebr.part_size;
        }
        resultado.part_next = -1;
        if (resultado.part_start + size > this->mbr_temp.mbr_partitions[this->pos_extendida].part_size + this->mbr_temp.mbr_partitions[this->pos_extendida].part_start){
            //La particion no tiene tanto espacio para crearla
            resultado.part_start = -1;
            resultado.part_next = -1;
            fclose(disco);
            return resultado;
        }
        if (ebr.part_status == '1'){
            ebr.part_next = resultado.part_start;
            fseek(disco,ebr.part_start, SEEK_SET);
            fwrite(&ebr, sizeof(EBR), 1, disco);
        }else{
            ebr.part_start = resultado.part_start;
            ebr.part_next = -1;
            fseek(disco,ebr.part_start, SEEK_SET);
            fwrite(&ebr, sizeof(EBR), 1, disco);
        }
        fclose(disco);
        return resultado;
    }

    //Validar si es peor ajuste o mejor ajuste con el struct
    //Recorrer todas las particiones y crear todos los espacios y luego decidir


    if (ajuste != 'F'){
        //Recorrer particiones
        FILE *disco;
        disco =fopen(this->path.c_str(),"rb+");
        EBR ebr;
        EBR ebr_ant;
        queue <Espacio>listaEspacio;
        int espacio_bytes;
        while (validador){
            fseek(disco, part_ant, SEEK_SET);
            fread(&ebr_ant,sizeof(EBR),1,disco);
            if (ebr_ant.part_next == -1){
                //No hay mas salir y crear el espacio del final
                espacio_bytes = this->mbr_temp.mbr_partitions[pos_extendida].part_size+this->mbr_temp.mbr_partitions[pos_extendida].part_start - ebr_ant.part_start;
                if (espacio_bytes < 1){
                    break;
                }
                Espacio espacio;
                espacio.anterior = ebr_ant;
                espacio.inicio = ebr_ant.part_start+ebr_ant.part_size;
                espacio.size = espacio_bytes;
                espacio.libre = espacio_bytes - size;
                espacio.tipoParticion = 'L';
                listaEspacio.push(espacio);
                break;
            }
            fseek(disco, ebr_ant.part_next, SEEK_SET);
            fread(&ebr,sizeof(EBR),1,disco);

            //Revisar si hay espacio entre cada par de particiones
            espacio_bytes = ebr.part_start - ebr_ant.part_start-ebr_ant.part_size;
            if (espacio_bytes > 0){
                Espacio espacio;
                espacio.anterior = ebr_ant;
                espacio.inicio = ebr_ant.part_start+ebr_ant.part_size;
                espacio.size = espacio_bytes;
                espacio.libre = espacio_bytes - size;
                espacio.tipoParticion = 'L';
                listaEspacio.push(espacio);
            }
            part_ant = ebr_ant.part_next;

        }
        //Revisar toda la lista resultante y ver la posicion de la nueva particio

        Espacio temp;
        Espacio sig;
        temp = listaEspacio.front();
        listaEspacio.pop();
        if (ajuste == 'W'){
            //Buscando el espacio libre mas grande
            while(!listaEspacio.empty()){
                sig = listaEspacio.front();
                listaEspacio.pop();
                //Comparamos
                if(temp.libre < sig.libre){
                    //Cambiar el temp
                    temp = sig;
                }
                if (listaEspacio.empty()){
                    //No hay mas y salimos
                    break;
                }

            }

        }else if (ajuste == 'B'){
            //Buscando el espacio libre mas pequeno
            while(!listaEspacio.empty()){
                sig = listaEspacio.front();
                listaEspacio.pop();
                //Comparamos
                if(temp.libre > sig.libre && sig.libre > size){
                    //Cambiar el temp
                    temp = sig;
                }
                if (listaEspacio.empty()){
                    //No hay mas y salimos
                    break;
                }

            }
        }
        if (temp.libre < size){
            EBR resultado;
            resultado.part_start = -1;
            resultado.part_next = -1;
            fclose(disco);
            return resultado;
        }
        //Ya tendria mi struct espacio
        fseek(disco, temp.anterior.part_start, SEEK_SET);
        fread(&ebr_ant,sizeof(EBR),1,disco);
        EBR resultado;
        resultado.part_start = temp.inicio;
        resultado.part_next = temp.anterior.part_next;
        ebr_ant.part_next = resultado.part_start;
        //ebr.part_next = ebr.part_start;
        fseek(disco,ebr_ant.part_start, SEEK_SET);
        fwrite(&ebr_ant, sizeof(EBR), 1, disco);
        fclose(disco);
        return resultado;
    }



    //Validar los siguientes hasta encontrar un espacio en el primer ajuste
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
            if (resultado.part_start + size > this->mbr_temp.mbr_partitions[this->pos_extendida].part_size){
                //La particion no tiene tanto espacio para crearla
                resultado.part_start = -1;
                resultado.part_next = -1;
                fclose(disco);
                return resultado;
            }
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
    int j = 0;
    int sizeName = this->name.length();
    string nombrePart = "";

    if (extendida != -1 ){
/*
        for (int j = 0; j<sizeName;j++){
            nombrePart += this->mbr_temp.mbr_partitions[particion].part_name[j];
        }
*/
        //Todo a mayusculas
        string nameTemp="";
        while(this->name[j] != NULL && j <= 15){
            nameTemp += toupper(this->name[j]);
            j++;
        }
        j=0;
        this->name = nameTemp;

        while(this->mbr_temp.mbr_partitions[particion].part_name[j] != NULL && j <= 15){
            nombrePart += toupper(this->mbr_temp.mbr_partitions[particion].part_name[j]);
            j++;
        }
        j= 0;
    }else{
        EBR ebrInicial;
        EBR ebrTemp;
        bool encontrado = false;
        FILE *disco;
        //Copiar el EBR inicial
        disco =fopen(this->path.c_str(),"rb+");
        fseek(disco, this->mbr_temp.mbr_partitions[extendida].part_start, SEEK_SET);
        fread(&ebrInicial,sizeof(EBR),1,disco);
/*
        for (int j = 0; j<sizeName;j++){
            nombrePart += this->mbr_temp.mbr_partitions[particion].part_name[j];
        }


*/
        //Todo a mayusculas
        string nameTemp="";
        while(this->name[j] != NULL && j <= 15){
            nameTemp += toupper(this->name[j]);
            j++;
        }
        j=0;
        this->name = nameTemp;

        while (this->mbr_temp.mbr_partitions[particion].part_name[j] != NULL && j<=15){
            nombrePart += toupper(this->mbr_temp.mbr_partitions[particion].part_name[j]);
            j++;
        }
        j = 0;

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




