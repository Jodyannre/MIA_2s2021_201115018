#include "obj_rep.h"

obj_rep::obj_rep()
{
    this->name = "";
    this->path = "";
    this->id = "";
}


void obj_rep::mostrardatos(obj_rep *rep){

          printf("\n\n---------DATOS----------\n\n");
}


int obj_rep::ejecutar(){
    //Variables
    FILE *file_mounts; //Archivo creado
    FILE *disco; //Disco creado
    obj_umount *umount = new obj_umount();
    string name_part;
    string dir_disco;
    char type_part;
    int dir_part, part_start,size_part;

    //Verificar obligatorios

    //Verificar nombre vacio
    if(this->name == ""){
        cout<<"Error, nombre de reporte no valido. \n"<<endl;
        return -1;
    }

    if(this->path == ""){
        cout<<"Error, no se ingreso un path valido. \n"<<endl;
        return -1;
    }

    if(this->id == ""){
        cout<<"Error, no se ingreso un id valido. \n"<<endl;
        return -1;
    }

    //Cargar data, directorio utilizando umount
    umount->id = this->id;
    umount->getCurrentDir();
    this->currentDir = umount->currentDir;
    file_mounts =fopen((this->currentDir+"/dsmount.data").c_str(),"rb+");

    if (file_mounts == NULL){
        //El comando mount nunca ha sido utilizado
        cout<<"Error, no se ha montado ninguna particion. \n"<<endl;
        fclose(file_mounts);
        return -1;
    }

    //Cargar cmount
    fseek(file_mounts, 0, SEEK_SET);
    fread(&this->cmount,sizeof(Cmount),1,file_mounts);
    umount->cmount = this->cmount;

    //Vericicar que la particion este montada
    if (!umount->estaMontada()){
        cout<<"Error, la particion no ha sido montada. \n"<<endl;
        fclose(file_mounts);
        return -1;
    }


    //Verificar que el disco este montado
    if (!umount->estaMontado()){
        cout<<"Error, el disco no ha sido montado. \n"<<endl;
        fclose(file_mounts);
        return -1;
    }

    //Todo fue bien, obtener posiciones
    this->posD = umount->posD;
    this->posP = umount->posP;


    //Cargar MBR o EBR y la direccion del inicio de la particion
    fclose(file_mounts);
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
        fread(&this->ebr,sizeof(EBR),1,disco);
        part_start= this->ebr.part_start;
        size_part = this->ebr.part_size;
    }
    fclose(disco);
    //Revisar si la carpeta existe o crearla
    //Quitar nombre del archivo
    int pos = this->path.find_last_of('//');
    string pathTemp = this->path.substr(0,pos);
    verificarRuta(pathTemp);

    //Todo listo para crear el reporte

    if ((strcasecmp(this->name.c_str(), "MBR")==0)){
        //Crear reporte MBR
        string nombreArchivo = this->getNombreDisco(this->path);
        string rutaDisco = "";
        string nombreMBR = "";
        for (int i = 0; i < 100;i++){
            if (this->cmount.disco[this->posD].path[i]==NULL){
                break;
            }
            rutaDisco+=this->cmount.disco[this->posD].path[i];
        }
        nombreMBR = this->getNombreDisco(rutaDisco);
        this->crearReporteMBR(nombreArchivo, nombreMBR, pathTemp, dir_disco);

    }
    if ((strcasecmp(this->name.c_str(), "DISK")==0)){
        //Crear reporte disk
        string nombreArchivo = this->getNombreDisco(this->path);
        string rutaDisco = "";
        string nombreMBR = "";
        for (int i = 0; i < 100;i++){
            if (this->cmount.disco[this->posD].path[i]==NULL){
                break;
            }
            rutaDisco+=this->cmount.disco[this->posD].path[i];
        }
        this->crearReporteDisk(nombreArchivo, nombreMBR, pathTemp, dir_disco);
    }
    return 0;
}


void obj_rep::verificarRuta(string ruta){
    QString path = ruta.c_str();
    QDir dir(path);

    if(!dir.exists())
        {
            //qDebug() << "Creating " << path << "directory";
            dir.mkpath(path);
        }
        else
        {
            //qDebug() << path << " already exists";
     }

}


string obj_rep::getNombreDisco(string path){
    int pos = path.find_last_of('//');
    string pathTemp = path.substr(pos+1,path.length());
    string resultado = "";
    //verificarRuta(pathTemp);
    for (int i = 0; i<pathTemp.length();i++){
        if (pathTemp[i]==NULL){
            break;
        }
        resultado+= pathTemp[i];
    }
    return resultado;
}

void obj_rep::crearReporteMBR(string nombreArchivoSalida, string nombreDisco, string ruta, string rutaDisco){
    int pos = nombreArchivoSalida.find_last_of('.');
    string nombreArchivo = nombreArchivoSalida.substr(0,pos)+"MBR";
    string nombre_dot = ruta+"/"+nombreArchivo+".dot";
    string cmd = "dot -Tsvg " + nombre_dot + " -O " +ruta+"/"+ nombreArchivo+".svg";
    string inicio = "digraph structs { \n node [shape=plaintext] \n struct [label=< \n <TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\"> \n";
    string TR_A = "<TR>";
    string TR_C = "</TR> \n";
    string TD_A = "<TD COLSPAN=\"3\">";
    string TD_C = "</TD> \n";
    string finTabla = "</TABLE>>]; \n";
    string cierre = "}";
    string titulo = " -> struct [style=invis]";
    //Archivo de salida
    ofstream archivo(nombre_dot);

    //Inicio
    archivo<<inicio;

    //Titulos
    archivo<<TR_A;
    archivo<<TD_A;
    archivo<<"Nombre";
    archivo<<TD_C;
    archivo<<TD_A;
    archivo<<"Valor";
    archivo<<TD_C;
    archivo<<TR_C;

    //Datos del mbr

    //mbr size
    archivo<<TR_A;
    archivo<<TD_A;
    archivo<<"mbr_tamano";
    archivo<<TD_C;
    archivo<<TD_A;
    archivo<<to_string(this->mbr.mbr_tamano);
    archivo<<TD_C;
    archivo<<TR_C;

    //Fecha de creacion
    archivo<<TR_A;
    archivo<<TD_A;
    archivo<<"mbr_fecha_creacion";
    archivo<<TD_C;
    archivo<<TD_A;
    archivo<<this->getFechaMBR();
    archivo<<TD_C;
    archivo<<TR_C;

    //signature
    archivo<<TR_A;
    archivo<<TD_A;
    archivo<<"mbr_disk_signature";
    archivo<<TD_C;
    archivo<<TD_A;
    archivo<<to_string(this->mbr.mbr_disk_signature);
    archivo<<TD_C;
    archivo<<TR_C;

    //Fit
    archivo<<TR_A;
    archivo<<TD_A;
    archivo<<"Disk_fit";
    archivo<<TD_C;
    archivo<<TD_A;
    archivo<<to_string(this->mbr.disk_fit[0]);
    archivo<<TD_C;
    archivo<<TR_C;

    //Aqui comienza el llenado por cada una de las particiones
    for (int i = 0; i<4 ; i++){
        if (this->mbr.mbr_partitions[i].part_status!='1'){
            continue;
        }
        //Part status
        archivo<<TR_A;
        archivo<<TD_A;
        archivo<<"part_status_"+to_string(i+1);
        archivo<<TD_C;
        archivo<<TD_A;
        archivo<<this->mbr.mbr_partitions[i].part_status;
        archivo<<TD_C;
        archivo<<TR_C;

        //part type
        archivo<<TR_A;
        archivo<<TD_A;
        archivo<<"part_type_"+to_string(i+1);
        archivo<<TD_C;
        archivo<<TD_A;
        archivo<<this->mbr.mbr_partitions[i].part_type;
        archivo<<TD_C;
        archivo<<TR_C;

        //part fit
        archivo<<TR_A;
        archivo<<TD_A;
        archivo<<"part_fit_"+to_string(i+1);
        archivo<<TD_C;
        archivo<<TD_A;
        archivo<<this->mbr.mbr_partitions[i].part_fit;
        archivo<<TD_C;
        archivo<<TR_C;

        //part start
        archivo<<TR_A;
        archivo<<TD_A;
        archivo<<"part_start_"+to_string(i+1);
        archivo<<TD_C;
        archivo<<TD_A;
        archivo<<to_string(this->mbr.mbr_partitions[i].part_start);
        archivo<<TD_C;
        archivo<<TR_C;

        //part size
        archivo<<TR_A;
        archivo<<TD_A;
        archivo<<"part_size_"+to_string(i+1);
        archivo<<TD_C;
        archivo<<TD_A;
        archivo<<to_string(this->mbr.mbr_partitions[i].part_size);
        archivo<<TD_C;
        archivo<<TR_C;

        //part name
        archivo<<TR_A;
        archivo<<TD_A;
        archivo<<"part_name_"+to_string(i+1);
        archivo<<TD_C;
        archivo<<TD_A;
        archivo<<this->convertToString(this->mbr.mbr_partitions[i].part_name);
        archivo<<TD_C;
        archivo<<TR_C;
    }
    archivo<<finTabla;
    archivo<< "\" MBR "+nombreDisco+"\"" + titulo;
    archivo<<cierre;
    archivo.close();

    //Ejecutar dot y get un svg
    for (int i=0; i<500;i++){

    }
    system(cmd.c_str());
    //Esperar un momento para poder borrar el dot
    for (int i=0; i<500;i++){

    }
    if( remove(nombre_dot.c_str()) != 0 ){
        printf("Error, el archivo no existe.");
    }

    //Renombrar el archivo de salida
    string renombrar = "mv "+nombre_dot+".svg " + ruta+"/"+nombreArchivo+".svg";
    //cout<<renombrar;
    system(renombrar.c_str());
    crearReporteEBR(nombreArchivoSalida, nombreDisco, ruta,rutaDisco);

}


void obj_rep::crearReporteEBR(string nombreArchivoSalida, string nombreDisco, string ruta, string rutaDisco){
    //Cargar el ebr inicial
    //Conseguir la direccion del ebr

    int part_start = -1;
    for (int i = 0;i<4;i++){
        if (this->mbr.mbr_partitions[i].part_type =='E'){
            part_start = this->mbr.mbr_partitions[i].part_start;
            break;
        }
    }

    //No hay extendida
    if (part_start == -1){
        return;
    }
    FILE *disco;
    EBR ebr;
    disco =fopen(rutaDisco.c_str(),"rb+");
    fseek(disco, part_start, SEEK_SET);
    fread(&ebr,sizeof(EBR),1,disco);

    //Verificar que tenga un siguiente y que el actual tambien exista
    if (ebr.part_status=='0' && ebr.part_next==-1){
        //No hay ninguna logica
        fclose(disco);
        return;
    }

    int pos = nombreArchivoSalida.find_last_of('.');
    string nombreArchivo = nombreArchivoSalida.substr(0,pos)+"EBR";
    string nombre_dot = ruta+"/"+nombreArchivo+".dot";
    string cmd = "dot -Tsvg " + nombre_dot + " -O " +ruta+"/"+ nombreArchivo+".svg";
    string inicio = "digraph structs { \n node [shape=plaintext] \n struct [label=< \n <TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\"> \n";
    string TR_A = "<TR>";
    string TR_C = "</TR> \n";
    string TD_A = "<TD COLSPAN=\"3\">";
    string TD_C = "</TD> \n";
    string finTabla = "</TABLE>>]; \n";
    string cierre = "}";
    string titulo = " -> struct [style=invis]";
    //Archivo de salida
    ofstream archivo(nombre_dot);



    //Inicio
    archivo<<inicio;
    for (int i=0 ; i<29;i++){
        //Verificar que la actual exista
        if (ebr.part_status == '0'){
            fseek(disco, ebr.part_next, SEEK_SET);
            fread(&ebr,sizeof(EBR),1,disco);
            continue;
        }

        //Part status
        archivo<<TR_A;
        archivo<<TD_A;
        archivo<<"part_status_"+to_string(i+1);;
        archivo<<TD_C;
        archivo<<TD_A;
        archivo<<ebr.part_status;
        archivo<<TD_C;
        archivo<<TR_C;

        //part fit
        archivo<<TR_A;
        archivo<<TD_A;
        archivo<<"part_fit_"+to_string(i+1);;
        archivo<<TD_C;
        archivo<<TD_A;
        archivo<<ebr.part_fit;
        archivo<<TD_C;
        archivo<<TR_C;

        //part start
        archivo<<TR_A;
        archivo<<TD_A;
        archivo<<"part_start_"+to_string(i+1);;
        archivo<<TD_C;
        archivo<<TD_A;
        archivo<<to_string(ebr.part_start);
        archivo<<TD_C;
        archivo<<TR_C;

        //part size
        archivo<<TR_A;
        archivo<<TD_A;
        archivo<<"part_size_"+to_string(i+1);;
        archivo<<TD_C;
        archivo<<TD_A;
        archivo<<to_string(ebr.part_size);
        archivo<<TD_C;
        archivo<<TR_C;

        //part next
        archivo<<TR_A;
        archivo<<TD_A;
        archivo<<"part_next_"+to_string(i+1);;
        archivo<<TD_C;
        archivo<<TD_A;
        archivo<<to_string(ebr.part_next);
        archivo<<TD_C;
        archivo<<TR_C;

        //part name
        archivo<<TR_A;
        archivo<<TD_A;
        archivo<<"part_name_"+to_string(i+1);;
        archivo<<TD_C;
        archivo<<TD_A;
        archivo<<this->convertToString(ebr.part_name);
        archivo<<TD_C;
        archivo<<TR_C;

        if (ebr.part_next != -1){
            fseek(disco, ebr.part_next, SEEK_SET);
            fread(&ebr,sizeof(EBR),1,disco);
        }else{
            break;
        }
    }



    archivo<<finTabla;
    archivo<< "\" EBR "+nombreDisco+"\"" + titulo;
    archivo<<cierre;
    archivo.close();

    //Ejecutar dot y get un svg
    for (int i=0; i<500;i++){

    }
    system(cmd.c_str());
    //Esperar un momento para poder borrar el dot
    for (int i=0; i<500;i++){

    }
    if( remove(nombre_dot.c_str()) != 0 ){
        printf("Error, el archivo no existe.");
    }

    //Renombrar el archivo de salida
    string renombrar = "mv "+nombre_dot+".svg " + ruta+"/"+nombreArchivo+".svg";
    //cout<<renombrar;
    system(renombrar.c_str());
    fclose(disco);

}

void obj_rep::crearReporteDisk(string nombreArchivoSalida, string nombreRep, string ruta,string rutaDisco){
    //Datos del archivo de salida
    int pos = nombreArchivoSalida.find_last_of('.');
    string nombreArchivo = nombreArchivoSalida.substr(0,pos)+"DISK";
    string nombre_dot = ruta+"/"+nombreArchivo+".dot";
    string cmd = "dot -Tsvg " + nombre_dot + " -O " +ruta+"/"+ nombreArchivo+".svg";
    bool hayExtendida = false;
    int posExtendida = -1;
    int extensionExtendida = 0;
    queue<GraficaDisk> lista_ebr;
    queue<GraficaDisk> lista_mbr;
    //Verificar si hay extendida
    for (int i = 0; i<4; i++){
        if (this->mbr.mbr_partitions[i].part_type=='E'){
            posExtendida = i;
            hayExtendida = true;
            GraficaDisk nodo;
            nodo.nombre = "Extendida";
            nodo.size = this->mbr.mbr_partitions[i].part_size;
            nodo.type = 'E';
            nodo.inicio = this->mbr.mbr_partitions[i].part_start;
            if (!lista_mbr.empty() && lista_mbr.size()>0){
                GraficaDisk anterior;
                anterior = lista_mbr.back();
                if (nodo.inicio-anterior.inicio-anterior.size > 0){
                    //Hay espacio libre
                    GraficaDisk nodoL;
                    nodoL.nombre = "Libre";
                    nodoL.size = nodo.inicio-anterior.inicio-anterior.size;
                    nodoL.inicio = anterior.inicio+anterior.size ;
                    nodoL.type = 'L';
                    lista_mbr.push(nodoL);
                }
            }
            lista_mbr.push(nodo);
            continue;
        }
        if (this->mbr.mbr_partitions[i].part_status=='1'){
            GraficaDisk nodo;
            nodo.nombre = "Primaria";
            nodo.size = this->mbr.mbr_partitions[i].part_size;
            nodo.inicio = this->mbr.mbr_partitions[i].part_start;
            nodo.type = 'P';

            if (!lista_mbr.empty() && lista_mbr.size()>0){
                GraficaDisk anterior;
                anterior = lista_mbr.back();
                if (nodo.inicio-anterior.inicio-anterior.size > 0){
                    //Hay espacio libre
                    GraficaDisk nodoL;
                    nodoL.nombre = "Libre";
                    nodoL.size = nodo.inicio-anterior.inicio-anterior.size;
                    nodoL.inicio = anterior.inicio+anterior.size ;
                    nodoL.type = 'L';
                    lista_mbr.push(nodoL);
                }
            }
            lista_mbr.push(nodo);
        }
    }

    //Espacio libre al final
    GraficaDisk anterior;
    anterior = lista_mbr.back();
    GraficaDisk nodo;
    nodo.nombre = "Libre";
    nodo.size = this->mbr.mbr_tamano-anterior.inicio-anterior.size;
    nodo.inicio = anterior.inicio+anterior.size ;
    nodo.type = 'L';
    lista_mbr.push(nodo);


    if (hayExtendida){
        //Verificar la extension de la extendida
        FILE *disco;
        EBR ebr;
        disco =fopen((rutaDisco.c_str()),"rb+");
        //Copiar primer ebr
        fseek(disco, this->mbr.mbr_partitions[posExtendida].part_start, SEEK_SET);
        fread(&ebr,sizeof(EBR),1,disco);

        //ebr inicial
        if (ebr.part_status == '1'){
            extensionExtendida++;
            extensionExtendida++;
            GraficaDisk nodo;
            nodo.nombre = "Logica";
            nodo.size = ebr.part_size;
            nodo.type = 'O';
            nodo.inicio = ebr.part_start;
            lista_ebr.push(nodo);
        }
        bool primera = false;

        while(true){
            if (primera){
                extensionExtendida++;
                extensionExtendida++;
                GraficaDisk nodo;
                nodo.nombre = "Logica";
                nodo.size = ebr.part_size;
                nodo.type = 'O';
                nodo.inicio = ebr.part_start;
                lista_ebr.push(nodo);
            }

            if (ebr.part_next != -1){
                if (ebr.part_next - ebr.part_start - ebr.part_size > 0){
                    //Hay espacio libre
                    extensionExtendida++;
                    GraficaDisk nodoL;
                    nodoL.nombre = "Libre";
                    nodoL.size = ebr.part_next - ebr.part_start - ebr.part_size;
                    nodoL.type = 'L';
                    nodoL.inicio = ebr.part_start;
                    lista_ebr.push(nodoL);
                }
                primera = true;
                fseek(disco, ebr.part_next, SEEK_SET);
                fread(&ebr,sizeof(EBR),1,disco);
            }else{
                //Espacio libre
                extensionExtendida++;
                GraficaDisk nodoL;
                nodoL.nombre = "Libre";
                nodoL.size = this->mbr.mbr_partitions[posExtendida].part_start +this->mbr.mbr_partitions[posExtendida].part_size - ebr.part_start - ebr.part_size;
                nodoL.type = 'L';
                nodoL.inicio = ebr.part_start;
                lista_ebr.push(nodoL);
                fclose(disco);
                break;
            }

        }
    }


    //Iniciar variables para el html
    string mbr = "<TD ROWSPAN=\"5\">MBR</TD> \n";
    string ebrt = "<TD ROWSPAN=\"4\">EBR</TD> \n";
    string tr_a = "<TR>";
    string tr_c = "</TR> \n";
    string mbr_libre = "<TD ROWSPAN=\"5\">Libre<br/>";
    string ebr_libre = "<TD ROWSPAN=\"4\">Libre<br/>";
    string td_c = "</TD> \n";
    string logica = "<TD ROWSPAN=\"4\">Logica<br/>";
    string primaria = "<TD ROWSPAN=\"5\">Primaria<br/>";
    string libre_mbr = "<TD ROWSPAN=\"5\">Libre<br/>";
    string libre_ebr = "<TD ROWSPAN=\"4\">Libre<br/>";
    string extendida = "<TD COLSPAN=\""+to_string(extensionExtendida)+"\">Extendida\n";
    ofstream archivo(nombre_dot);
    string inicio = "digraph G { \n rankdir=LR \n node [shape=plaintext] \n a [ \n label=< \n <TABLE color='blue'> \n";
    string cierre = "</TABLE>> \n] \n}";

    archivo<<inicio;
    //Agregar todo lo del mbr
    archivo<<tr_a;
    archivo<<mbr;

    //Recorrer lista mbr
    GraficaDisk aux;
    float porcentaje = 0;
    float dividendo = 0;
    string percentaje = "";
    while(!lista_mbr.empty()){
        aux = lista_mbr.front();
        lista_mbr.pop();
        if (aux.type == 'P'){
            //Primaria
            stringstream stream;
            archivo<<primaria;
            dividendo = this->mbr.mbr_tamano;
            porcentaje = (aux.size*100)/dividendo;
            stream<<fixed<<std::setprecision(2)<<porcentaje;
            percentaje = stream.str();
            archivo<<percentaje+"% del disco";
            archivo<<td_c;
        }else if (aux.type == 'E'){
            //Extendida
            archivo<<extendida;
            porcentaje = (aux.size*100)/ this->mbr.mbr_tamano;
            archivo<<td_c;
        }else{
            //Espacio libre
            stringstream stream;
            archivo<<libre_mbr;
            dividendo = this->mbr.mbr_tamano;
            porcentaje = (aux.size*100)/dividendo;
            stream<<fixed<<std::setprecision(2)<<porcentaje;
            percentaje = stream.str();
            archivo<<percentaje+"% del disco";
            archivo<<td_c;
        }
    }
    archivo<<tr_c;
    if(hayExtendida){
       archivo<<tr_a;
    }
    //Recorrer lista ebr
    while(!lista_ebr.empty()){
        aux = lista_ebr.front();
        lista_ebr.pop();
        if (aux.type == 'O'){
            //Es logica
            stringstream stream;
            dividendo = this->mbr.mbr_tamano;
            archivo<<ebrt;
            archivo<<logica;
            porcentaje = (aux.size*100)/dividendo;
            stream<<fixed<<std::setprecision(2)<<porcentaje;
            percentaje = stream.str();
            archivo<<percentaje+"% del disco";
            archivo<<td_c;
        }else{
            //Es espacio libre
            stringstream stream;
            dividendo = this->mbr.mbr_tamano;
            archivo<<libre_ebr;
            porcentaje = (aux.size*100)/dividendo;
            stream<<fixed<<std::setprecision(2)<<porcentaje;
            percentaje = stream.str();
            archivo<<percentaje+"% del disco";
            archivo<<td_c;
        }
    }

    //Cerrar tabla
    if (hayExtendida){
       archivo<<tr_c;
    }
    archivo<<cierre;
    archivo.close();
    //Ejecutar dot y get un svg
    for (int i=0; i<7000;i++){

    }
    system(cmd.c_str());
    //Esperar un momento para poder borrar el dot
    for (int i=0; i<7000;i++){

    }
    if( remove(nombre_dot.c_str()) != 0 ){
        printf("Error, el archivo no existe.");
    }
    for (int i=0; i<7000;i++){

    }
    //Renombrar el archivo de salida
    string renombrar = "mv "+nombre_dot+".svg " + ruta+"/"+nombreArchivo+".svg";
    //cout<<renombrar;
    system(renombrar.c_str());

}

string obj_rep::getFechaMBR(){
    string resultado = "";
    struct tm *tiempo;
    tiempo = gmtime(&this->mbr.mbr_fecha_creacion);
    resultado+= to_string(tiempo->tm_mday)+"/"+to_string(tiempo->tm_mon)+"/"+to_string(tiempo->tm_year+1900)+" "+to_string(tiempo->tm_hour)+":"+to_string(tiempo->tm_min);
    return resultado;
}

string obj_rep::convertToString(char* caracteres)
{
    int size = sizeof(caracteres)/sizeof(char);
    string resultado = "";
    for (int i = 0; i < 15; i++) {
        if (caracteres[i]==NULL){
            break;
        }
        resultado = resultado + caracteres[i];
    }
    return resultado;
}
