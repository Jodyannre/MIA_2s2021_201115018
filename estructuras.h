#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include "time.h"


typedef struct{
    char part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];
}EBR;


typedef struct{
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];


}Particion;


typedef struct{
    int mbr_tamano;
    time_t mbr_fecha_creacion;
    int mbr_disk_signature;
    char disk_fit[1];
    Particion mbr_partitions[4];
}MBR;


typedef struct{
    char name[16];
    char id[4];
    char type;
    int estado;
    int direccion;
}Pmount;


typedef struct{
    Pmount particiones[49];
    char path[100];
    int number;
    int estado;
}Dmount;

typedef struct{
    Dmount disco[29];
}Cmount;


class estructuras
{
public:
    estructuras();
};

#endif // ESTRUCTURAS_H
