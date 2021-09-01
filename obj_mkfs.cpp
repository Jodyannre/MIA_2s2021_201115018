#include "obj_mkfs.h"

obj_mkfs::obj_mkfs()
{
    this->id = "";
    this->type = -1;
    this->fs = -1;
}

/*
 * Tipos
 * 0 -> Fast
 * 1 -> Full
 *
 * Fs
 * 2 -> 2fs
 * 3 -> 3fs
 *
*/

int obj_mkfs::ejecutar( ){
    //Variables
    FILE *disco; //Archivo creado
    FILE *disco2; //Disco creado
    obj_umount *umount = new obj_umount();
    string name_part;
    string dir_disco;
    int dir_part;
    char type_part;
    int part_start = -1;
    int n = 0;
    int size_part = 0;
    int numero_inodos = 0;

    //Verificar los obligatorios
    if (this->id == ""){
        cout<<"Error, no se ingreso ningun id."<<endl;
        return -1;
    }

    //Verificar los opcionales
    if (this->type == -1){
        //Por defecto es el full
        this->type = 1;
    }

    if (this->fs == -1){
        //Por defecto sera el ext2
        this->fs = 2;
    }

    //Cargar data, directorio utilizando umount
    umount->id = this->id;
    umount->getCurrentDir();
    this->currentDir = umount->currentDir;
    disco =fopen(this->currentDir.c_str(),"rb+");

    if (disco == NULL){
        //El comando mount nunca ha sido utilizado
        cout<<"Error, no se ha montado ninguna particion"<<endl;
        fclose(disco);
        return -1;
    }
    //Cargar cmount
    fseek(disco, 0, SEEK_SET);
    fread(&this->cmount,sizeof(Cmount),1,disco);
    umount->cmount = this->cmount;


    //Vericicar que la particion este montada
    if (!umount->estaMontada()){
        cout<<"Error, la particion no ha sido montada."<<endl;
        fclose(disco);
        return -1;
    }


    //Verificar que el disco este montado
    if (!umount->estaMontado()){
        cout<<"Error, el disco no ha sido montado."<<endl;
        fclose(disco);
        return -1;
    }

    //Todo fue bien, obtener posiciones
    this->posD = umount->posD;
    this->posP = umount->posP;


    //Cargar MBR o EBR y la direccion del inicio de la particion
    fclose(disco);
    type_part = this->cmount.disco[posD].particiones[posP].type;
    name_part = umount->nameToString(posD,posP);
    dir_part = this->cmount.disco[posD].particiones[posP].direccion;
    dir_disco = umount->pathToString(this->posD, this->posP);
    disco2 =fopen(dir_disco.c_str(),"rb+");

    if (type_part == 'P'){
        //Si es primaria cargar el MBR
        fseek(disco2, 0, SEEK_SET);
        fread(&this->mbr,sizeof(MBR),1,disco);
        part_start= this->mbr.mbr_partitions[dir_part].part_start;
        size_part = this->mbr.mbr_partitions[dir_part].part_size;
    }else if (type_part == 'L'){
        //Si es logica cargar directamente el EBR
        fseek(disco2, dir_part, SEEK_SET);
        fread(&this->ebr,sizeof(MBR),1,disco);
        part_start= this->ebr.part_start;
        size_part = this->ebr.part_size;
    }



    //Verificar el tipo del sistema, si es ext2 o ext3
    if (this->fs == 2){
        //Es ext2

        //Calcular n numero de inodos con la formula
        n = (size_part - sizeof(SuperBloque))/(4+sizeof(Inodo)+3*sizeof (BloqueArchivos));
        numero_inodos = floor(n);

        //Formatear

        if (this->fs == 1){
            fseek(disco2,part_start,SEEK_SET);//Inicio de particion a la cual se agregara la info
            if(this->fs==2){
                char buffer;
                buffer='\0';
                for(int i=0;i<size_part;i++) {
                    //Llenar de 0s toda la particion
                    fwrite(&buffer,sizeof(buffer),1,disco2);
                    fseek(disco2, part_start + i, SEEK_SET);
                }

            }
        }

        //Crear superbloque
        SuperBloque superBloque;

        time_t raw_time;
        raw_time = time(NULL);

        superBloque.s_inodes_count=n;
        superBloque.s_blocks_count=3*n;
        superBloque.s_free_blocks_count=3*n; //Todos
        superBloque.s_free_inodes_count=n; //Todos
        superBloque.s_filesystem_type=2;
        superBloque.s_mtime = raw_time;
        superBloque.s_umtime = raw_time;
        superBloque.s_mnt_count=1;
        superBloque.s_magic=0xEF53; //Valor predefinido
        superBloque.s_inode_size=sizeof(Inodo);
        superBloque.s_block_size=sizeof(BloqueArchivos);
        superBloque.s_first_ino=2; //El 2 porque el primero esta destinado para el archivo de users.txt
        superBloque.s_first_blo=2;  //El primero para el archivo users.txt
        superBloque.s_bm_inode_start=part_start + sizeof(SuperBloque); //Inicio bitmap de inodos
        superBloque.s_bm_block_start=superBloque.s_bm_inode_start + sizeof(Inodo); //Inicio bitmap de bloques
        superBloque.s_inode_start=superBloque.s_bm_block_start+3*n; //Inicio de la tabla de inodos
        superBloque.s_block_start=superBloque.s_inode_start+n*sizeof(Inodo); //Inicio de la tabla de bloques

        //Escribir el superbloque en la particion
        fseek(disco2,part_start, SEEK_SET);
        fwrite(&superBloque,sizeof(SuperBloque),1, disco2);

        //Creacion del bitmpa de inodos
        char bitmap_inodos[n];
        int start_bitmap_inodos=part_start + sizeof(SuperBloque);
        for(int i=2;i<n;i++){
            bitmap_inodos[i]='0';
        }
        //El inodo para users.txt y la carpeta raiz
        bitmap_inodos[0] = '1';
        bitmap_inodos[1] = '1';

        //Escribir el bitmap de inodos en la particion
        fseek(disco2,start_bitmap_inodos, SEEK_SET);
        fwrite(&bitmap_inodos,sizeof(bitmap_inodos),1,disco2);


        //Creacion del bitmap de bloques
        char bitmap_bloques[3*n];
        int start_bitmap_bloques=start_bitmap_inodos+sizeof(bitmap_inodos);
        for(int i=2;i<3*n;i++){
            bitmap_bloques[i]='0';
        }

        //Bloques reservados para el users.txt y la carpeta raiz
        bitmap_bloques[0]='1';
        bitmap_bloques[1]='2';

        //Escribir en la particion el bitmap de bloques
        fseek(disco2,start_bitmap_bloques, SEEK_SET);
        fwrite(&bitmap_bloques,sizeof(bitmap_bloques),1,disco2);


        //Crear inodo para la carpeta raiz
        Inodo raiz;
        raiz.i_uid=1; //1 para el usuario root
        raiz.i_gid=1; //1 para el grupo de usuario root
        raiz.i_size=0; // Ni idea de momento <------------------------------
        raiz.i_atime = raw_time;
        raiz.i_mtime = raw_time;
        raiz.i_ctime = raw_time;
        //Todos los iblocks con -1 ya que no son utilizados de momento
        for(int i=0;i<15;i++){
            raiz.i_block[i]=-1;
        }
        raiz.i_block[0]=0; // Se usa el primero directo hacia la carpeta raiz
        raiz.i_type='0'; //0 para carpeta y 1 para archivo
        raiz.i_perm=664; //Permisos 664, todos para el root


        //Crear bloque de carpeta para la raiz
        BloqueCarpetas carpetaRaiz;
        Content contentRaiz; //Contenido de la carpeta
        strcpy(contentRaiz.b_name, ".");
        contentRaiz.b_inodo = 0; //apuntador al primer inodo
        carpetaRaiz.b_content[0] = contentRaiz;
        strcpy(contentRaiz.b_name, ".."); //Padre de todas las carpetas
        contentRaiz.b_inodo = 0; //apuntador al primer inodo
        carpetaRaiz.b_content[1] = contentRaiz;


        //Crear el content del archivo users.txt

        //Nombre del archivo
        strcpy(contentRaiz.b_name, "users.txt");
        //Apuntar al segundo inodo en uso
        contentRaiz.b_inodo = 1;
        //Content del archivo en la tercera posicion
        carpetaRaiz.b_content[2] = contentRaiz;
        //Llenar el nombre con 0s
        memset(&contentRaiz.b_name, 0, sizeof(contentRaiz.b_name));
        //De momento sin inodo
        contentRaiz.b_inodo = -1;
        //Agregado a la cuarta posicion
        carpetaRaiz.b_content[3] = contentRaiz;

        //Se esta usando 1 inodo y de bloques
        superBloque.s_free_inodes_count--;
        superBloque.s_free_blocks_count--;

        //Guardar el primer inodo en la primera posicion que es el de la carpeta
        fseek(disco2, superBloque.s_inode_start, SEEK_SET);
        fwrite(&raiz, sizeof(Inodo), 1, disco2);

        //Guardar el primer bloque en la primera posicion que es el de la carpeta
        fseek(disco2, superBloque.s_block_start, SEEK_SET);
        fwrite(&carpetaRaiz, 64, 1, disco2);


        //Crear el bloque, content y inodo para el archivo users.txt

        char informacion[]="Informacion";
        //Inodo del archivo
        Inodo usersTxt;
        //Usuario root
        usersTxt.i_gid=1;
        //Size del contenido del archivo
        usersTxt.i_size=sizeof(informacion);
        //1 para grupo root
        usersTxt.i_uid=1;
        //Hora de creacion y modificacion
        usersTxt.i_atime = raw_time;
        usersTxt.i_mtime = raw_time;
        usersTxt.i_ctime = raw_time;
        //Apuntadores, iniciados todos en -1
        for(int i=0;i<15;i++){
            usersTxt.i_block[i]=-1;
        }
        //Todos los permisos para el root
        usersTxt.i_perm=664;
        //El primer bloque directo va hacia el archivo users.txt
        usersTxt.i_block[0]=1;
        //0 para carpeta 1 para archivo
        usersTxt.i_type='1';



        //Crear el bloque para el archivo users.txt

        BloqueArchivos bloqueUsersTxt;
        //Agregar la informacion al content del bloque
        strcpy(bloqueUsersTxt.b_content,informacion);

        //Restar el bloque e inodo utilizado
        superBloque.s_free_inodes_count--;
        superBloque.s_free_blocks_count--;

        //Guardar el inodo en la segunda posicion
        fseek(disco2, superBloque.s_inode_start+sizeof(Inodo), SEEK_SET);
        fwrite(&usersTxt, sizeof(Inodo), 1, disco2);

        //Guardar el bloque en la segunda posicion
        fseek(disco2, superBloque.s_block_start+sizeof(BloqueArchivos), SEEK_SET);
        fwrite(&bloqueUsersTxt, 64, 1, disco2);


        //Escribir el superBloque con las actualizaciones
        fseek(disco2, superBloque.s_block_start, SEEK_SET);
        fwrite(&superBloque, sizeof(SuperBloque), 1, disco2);
        fclose(disco2);

    }else{
        //Es ext3


    }



}



