#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include "time.h"
#include "string"

using namespace std;

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
    int inicio;
    int size;
    int libre;
    char tipoParticion;
    EBR anterior;
}Espacio;


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


typedef struct {
   int s_filesystem_type;
   int s_inodes_count;
   int s_blocks_count;
   int s_free_blocks_count;
   int s_free_inodes_count;
   time_t s_mtime;
   time_t s_umtime;
   int s_mnt_count;
   int s_magic;
   int s_inode_size;
   int s_block_size;
   int s_first_ino;
   int s_first_blo;
   int s_bm_inode_start;
   int s_bm_block_start;
   int s_inode_start;
   int s_block_start;

}SuperBloque;

typedef struct {
    int i_uid;
    int i_gid;
    int i_size;
    time_t i_atime;
    time_t i_ctime;
    time_t i_mtime;
    int i_block[15];
    char i_type;
    int i_perm;


}Inodo;

typedef struct {
    char b_name [12];
    int b_inodo;

}Content;

typedef struct {
    Content b_content [4];

}BloqueCarpetas;

typedef struct {
    char b_content[64];

}BloqueArchivos;

typedef struct {
    int inicio;
    int size;
    string nombre;
    char type;
}GraficaDisk;


typedef struct{
   char instruccion[10] ; //Tipo de instruccion
   char tipo_bloque; //0 Para carpeta e 1 para archivo como en el superbloque
   char nombre [140]; //Nombre con ruta
   char content [140]; //Contenido del archivo
   time_t fecha; // Fecha de creacion
   char usuario [10]; //El usuario que creo la carpeta o el archivo
   int permiso; //permisos
   }Journal;

class estructuras
{
public:
    estructuras();
};

#endif // ESTRUCTURAS_H
