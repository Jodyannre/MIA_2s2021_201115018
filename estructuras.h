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

class estructuras
{
public:
    estructuras();
};

#endif // ESTRUCTURAS_H
