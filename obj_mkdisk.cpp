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
    FILE *archivo; //Archivo binario que simulara el disco
    MBR mbr;
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
        mbr.mbr_tamano = this->size * 1024;
    }else if (this->u == "m" || this->u == "M"){
        unidad = 2;
        mbr.mbr_tamano = this->size * 1024 * 1024;
    }

    if (this->f < 0){
        this->f = 1;
        strcpy( mbr.disk_fit,"F");
    }else if (this->f == 0){
        strcpy( mbr.disk_fit,"B");
    }else if (this->f == 1){
        strcpy( mbr.disk_fit,"F");
    }else if (this->f == 2){
        strcpy( mbr.disk_fit,"W");
    }

    //Datos para el mbr
    time_t fecha = time(NULL);
    mbr.mbr_fecha_creacion = fecha;
    mbr.mbr_disk_signature = (rand() % 1000);

    //Verificar que existan las carpetas
    //Quitar nombre del archivo
    int pos = this->path.find_last_of('//');
    string pathTemp = this->path.substr(0,pos);
    verificarRuta(pathTemp);

    //Creando archivo
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

    //Creando las 4 particiones vacias para el disco
    Particion p1;
    Particion p2;
    Particion p3;
    Particion p4;
    //crearParticionesVacias(p1,0,mbr);
    //crearParticionesVacias(p2,1,mbr);
    //crearParticionesVacias(p3,2,mbr);
    //crearParticionesVacias(p4,3,mbr);

    p1.part_status ='0';
    p1.part_type =' ';
    p1.part_fit =' ';
    p1.part_start = -1;
    p1.part_size = -1;
    p1.part_name[0] = ' ';
    mbr.mbr_partitions[0] = p1;

    p2.part_status ='0';
    p2.part_type =' ';
    p2.part_fit =' ';
    p2.part_start = -1;
    p2.part_size = -1;
    p2.part_name[0] = ' ';
    mbr.mbr_partitions[1] = p2;

    p3.part_status ='0';
    p3.part_type =' ';
    p3.part_fit =' ';
    p3.part_start = -1;
    p3.part_size = -1;
    p3.part_name[0] = ' ';
    mbr.mbr_partitions[2] = p3;

    p4.part_status ='0';
    p4.part_type =' ';
    p4.part_fit =' ';
    p4.part_start = -1;
    p4.part_size = -1;
    p4.part_name[0] = ' ';
    mbr.mbr_partitions[3] = p4;




    //Agregar mbr al archivo binario

    archivo = fopen(this->path.c_str(), "rb+"); //modo de escritura mixto permite actualizar un fichero sin borrar el contenido anterior
        if(archivo != NULL){
            fseek(archivo,0,SEEK_SET);
            fwrite(&mbr, sizeof(MBR), 1, archivo);
            fclose(archivo);
            printf("DISCO CREADO CORRECTAMENTE \nSE AGREGO EL MBR DE MANERA CORRECTA\n");
        }else{
            printf("Error!\n No se puede acceder al disco, MBR no creado\n");
        }


    return 0;
}

void obj_mkdisk::crearParticionesVacias(Particion particion, int posicion, MBR mbr){
    particion.part_status ='0';
    particion.part_type =' ';
    particion.part_fit ='f';
    particion.part_start = -1;
    particion.part_size = -1;
    particion.part_name[0] = 'a';
    mbr.mbr_partitions[posicion] = particion;

}


void obj_mkdisk::verificarRuta(string ruta){
    QString path = ruta.c_str();
    QDir dir(path);

    if(!dir.exists())
        {
            qDebug() << "Creating " << path << "directory";
            dir.mkpath(path);
        }
        else
        {
            //qDebug() << path << " already exists";
     }

}


