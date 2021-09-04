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
    this->currentDir = this->currentDir+"/dsmount.data";
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

        if (this->type == 2){
            fseek(disco2,part_start,SEEK_SET);//Inicio de particion a la cual se agregara la info
            char buffer;
            buffer='\0';
            for(int i=0;i<size_part;i++) {
                //Llenar de 0s toda la particion
                fwrite(&buffer,sizeof(buffer),1,disco2);
                fseek(disco2, part_start + i, SEEK_SET);
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
        superBloque.s_block_size=sizeof(BloqueArchivos); //Cualquier bloque, todos pesan 64
        superBloque.s_first_ino=2; //El 2 porque el primero esta destinado para la carpeta raiz y el 2 para el archivo users.txt
        superBloque.s_first_blo=2;  //Lo mismo que con los inodos
        superBloque.s_bm_inode_start=part_start + sizeof(SuperBloque); //Inicio del bitmap de inodos
        superBloque.s_bm_block_start=superBloque.s_bm_inode_start + n; //Inicio bitmap de bloques
        superBloque.s_inode_start=superBloque.s_bm_block_start+3*n; //Inicio de la tabla de inodos
        superBloque.s_block_start=superBloque.s_inode_start+n*sizeof(Inodo); //Inicio de la tabla de bloques

        //Escribir el superbloque en la particion
        fseek(disco2,part_start, SEEK_SET);
        fwrite(&superBloque,sizeof(SuperBloque),1, disco2);

        //Creacion del bitmpa de inodos con chars, ya que solo tendran de valor 0 o 1

        //El inodo para la carpeta raiz y el otro para el archivo de users.txt
        char bitmap_inodos[n];
        bitmap_inodos[0] = '1';
        bitmap_inodos[1] = '1';

        //Todos los demas inodos en 0

        for(int i=2;i<n;i++){
            bitmap_inodos[i]='0';
        }

        //Escribir el bitmap de inodos en la particion
        fseek(disco2,superBloque.s_bm_inode_start, SEEK_SET);
        fwrite(&bitmap_inodos,sizeof(bitmap_inodos),1,disco2);


        //Creacion del bitmap de bloques
        char bitmap_bloques[3*n];

        //Bloques reservados para el users.txt y la carpeta raiz
        //Para diferencia el tipo del bloque
        /*
         * 1 para carpetas
         * 2 para archivos
         * 3 para apuntadores
         *
        */
        bitmap_bloques[0]='1'; //Carpeta raiz
        bitmap_bloques[1]='2'; //Archivo users.txt

        //Llenar de 0 todos los demas bloques que no estan en uso
        for(int i=2;i<3*n;i++){
            bitmap_bloques[i]='0';
        }

        //Escribir en la particion el bitmap de bloques
        fseek(disco2,superBloque.s_bm_block_start, SEEK_SET);
        fwrite(&bitmap_bloques,sizeof(bitmap_bloques),1,disco2);

        //Crear inodo para la carpeta raiz
        Inodo inodo_raiz;
        inodo_raiz.i_uid=1; //1 para el usuario root
        inodo_raiz.i_gid=1; //1 para el grupo de usuario root
        inodo_raiz.i_size=0; // Ni idea de momento cuanto va a pesar, actualizar luego
        inodo_raiz.i_atime = raw_time;
        inodo_raiz.i_mtime = raw_time;
        inodo_raiz.i_ctime = raw_time;
        //Todos los iblocks con -1 ya que no son utilizados de momento
        for(int i=0;i<15;i++){
            inodo_raiz.i_block[i]=-1;
        }
        inodo_raiz.i_type='0'; //0 para carpeta y 1 para archivo
        inodo_raiz.i_block[0]=0; // Se usa el primero ya que contendra el bloque hacia la carpeta raiz
        inodo_raiz.i_perm=664; //Permisos 664, todos para el root


        //Crear bloque de carpeta para la raiz para los primeros 4 content
        BloqueCarpetas carpetaRaiz;
        Content contentRoot; //Contenido de la carpeta
        strcpy(contentRoot.b_name, "raiz");//Va a apuntar a si mismo
        contentRoot.b_inodo = 0; //apuntador al primer inodo que va a ser el root
        carpetaRaiz.b_content[0] = contentRoot;
        inodo_raiz.i_block[0]=0; //Apunta al bloque de la carpeta raiz, al 0
        Content contentRaiz;

        //Crear el content del archivo users.txt
        //Nombre del archivo
        strcpy(contentRaiz.b_name, "users.txt");
        //Apuntar al segundo inodo en uso que sera el de users.txt
        contentRaiz.b_inodo = 1;
        //Content del archivo en la segunda posicion, la primera tiene hacia la carpeta raiz
        carpetaRaiz.b_content[1] = contentRaiz;
        //Llenar el nombre con 0s para los otros 2 content que no tienen nada
        memset(&contentRaiz.b_name, 0, sizeof(contentRaiz.b_name));
        //Agregado a la tercera y cuarta posicion que no tienen nada
        carpetaRaiz.b_content[2] = contentRaiz;
        carpetaRaiz.b_content[3] = contentRaiz;

        //Se esta usando 1 inodo y de bloques, entonces disminuir los disponibles
        superBloque.s_free_inodes_count--;
        superBloque.s_free_blocks_count--;

        //Guardar el primer inodo en la primera posicion que es el de la carpeta
        fseek(disco2, superBloque.s_inode_start, SEEK_SET);
        fwrite(&inodo_raiz, sizeof(Inodo), 1, disco2);

        //Guardar el primer bloque en la primera posicion que es el de la carpeta
        fseek(disco2, superBloque.s_block_start, SEEK_SET);
        fwrite(&carpetaRaiz, 64, 1, disco2);


        //Crear el bloque, content y inodo para el archivo users.txt

        char informacion[]="1,G,root\n1,U,root,root,123\n";
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
        //El primer bloque directo va hacia el archivo users.txt, que seria el bloque 2 y de archivo
        usersTxt.i_block[0]=1;
        //0 para carpeta 1 para archivo
        usersTxt.i_type='1';


        //Crear el bloque para el archivo users.txt, es el bloque 1

        BloqueArchivos bloqueUsersTxt;
        //Agregar la informacion al content del bloque
        strcpy(bloqueUsersTxt.b_content,informacion);

        //El b_inodo no apunta a ningun lado queda vacio
        //Restar el bloque e inodo utilizado
        superBloque.s_free_inodes_count--;
        superBloque.s_free_blocks_count--;


        //Guardar el inodo en la segunda posicion
        fseek(disco2, superBloque.s_inode_start+sizeof(Inodo), SEEK_SET);
        fwrite(&usersTxt, sizeof(Inodo), 1, disco2);

        //Guardar el bloque en la segunda posicion
        fseek(disco2, superBloque.s_block_start+sizeof(BloqueArchivos), SEEK_SET);
        fwrite(&bloqueUsersTxt, sizeof(BloqueArchivos), 1, disco2);


        //Escribir el superBloque con las actualizaciones
        fseek(disco2, part_start, SEEK_SET);
        fwrite(&superBloque, sizeof(SuperBloque), 1, disco2);
        fclose(disco2);

    }else{
        //Es ext3

        //Calcular n numero de inodos con la formula
        n = (size_part - sizeof(SuperBloque) - 100*sizeof(BloqueArchivos))/(4+sizeof(Inodo)+3*sizeof (BloqueArchivos));
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
        superBloque.s_block_size=sizeof(BloqueArchivos); //Cualquier bloque, todos pesan 64
        superBloque.s_first_ino=2; //El 2 porque el primero esta destinado para la carpeta raiz y el 2 para el archivo users.txt
        superBloque.s_first_blo=2;  //Lo mismo que con los inodos
        //A diferencia de ext2, este inicia despues del journaling
        //Es journal * 20 ya que el journal pesa 320 * 20 = 6400 que es igual a los 100*bloques que solicita el enunciado
        //Seran 20 entradas el journal
        superBloque.s_bm_inode_start=part_start + sizeof(SuperBloque)+ 20*sizeof(Journal);
        superBloque.s_bm_block_start=superBloque.s_bm_inode_start + n; //Inicio bitmap de bloques
        superBloque.s_inode_start=superBloque.s_bm_block_start+3*n; //Inicio de la tabla de inodos
        superBloque.s_block_start=superBloque.s_inode_start+n*sizeof(Inodo); //Inicio de la tabla de bloques

        //Escribir el superbloque en la particion
        fseek(disco2,part_start, SEEK_SET);
        fwrite(&superBloque,sizeof(SuperBloque),1, disco2);



        //Crear los journal por defecto para escribir
        time_t tiempoTemp = time(NULL);
        Journal journal;
        journal.instruccion[0]='.';
        journal.tipo_bloque='.';
        journal.nombre[0]='\0';
        journal.content[0]='\0';
        journal.fecha = tiempoTemp;
        journal.usuario[0] = '\0';
        journal.permiso=-1;

        //Escribir el journaling en el disco despues del superbloque
        int inicioJournal = part_start + sizeof(SuperBloque);
        for (int i = 0; i < 20; i++) {

                fseek(disco2, (inicioJournal + (i * sizeof(Journal))), SEEK_SET);
                fwrite(&journal, sizeof(Journal), 1, disco2);
            }




        //Creacion del bitmpa de inodos con chars, ya que solo tendran de valor 0 o 1

        //El inodo para la carpeta raiz y el otro para el archivo de users.txt
        char bitmap_inodos[n];
        bitmap_inodos[0] = '1';
        bitmap_inodos[1] = '1';

        //Todos los demas inodos en 0

        for(int i=2;i<n;i++){
            bitmap_inodos[i]='0';
        }

        //Escribir el bitmap de inodos en la particion
        fseek(disco2,superBloque.s_bm_inode_start, SEEK_SET);
        fwrite(&bitmap_inodos,sizeof(bitmap_inodos),1,disco2);


        //Creacion del bitmap de bloques
        char bitmap_bloques[3*n];

        //Bloques reservados para el users.txt y la carpeta raiz
        //Para diferencia el tipo del bloque
        /*
         * 1 para carpetas
         * 2 para archivos
         * 3 para apuntadores
         *
        */
        bitmap_bloques[0]='1'; //Carpeta raiz
        bitmap_bloques[1]='2'; //Archivo users.txt

        //Llenar de 0 todos los demas bloques que no estan en uso
        for(int i=2;i<3*n;i++){
            bitmap_bloques[i]='0';
        }

        //Escribir en la particion el bitmap de bloques
        fseek(disco2,superBloque.s_bm_block_start, SEEK_SET);
        fwrite(&bitmap_bloques,sizeof(bitmap_bloques),1,disco2);

        //Crear inodo para la carpeta raiz
        Inodo inodo_raiz;
        inodo_raiz.i_uid=1; //1 para el usuario root
        inodo_raiz.i_gid=1; //1 para el grupo de usuario root
        inodo_raiz.i_size=0; // Ni idea de momento cuanto va a pesar, actualizar luego
        inodo_raiz.i_atime = raw_time;
        inodo_raiz.i_mtime = raw_time;
        inodo_raiz.i_ctime = raw_time;
        //Todos los iblocks con -1 ya que no son utilizados de momento
        for(int i=0;i<15;i++){
            inodo_raiz.i_block[i]=-1;
        }
        inodo_raiz.i_type='0'; //0 para carpeta y 1 para archivo
        inodo_raiz.i_block[0]=0; // Se usa el primero ya que contendra el bloque hacia la carpeta raiz
        inodo_raiz.i_perm=664; //Permisos 664, todos para el root


        //Crear bloque de carpeta para la raiz para los primeros 4 content
        BloqueCarpetas carpetaRaiz;
        Content contentRoot; //Contenido de la carpeta
        strcpy(contentRoot.b_name, "raiz");//Va a apuntar a si mismo
        contentRoot.b_inodo = 0; //apuntador al primer inodo que va a ser el root
        carpetaRaiz.b_content[0] = contentRoot;
        inodo_raiz.i_block[0]=0; //Apunta al bloque de la carpeta raiz, al 0
        Content contentRaiz;

        //Crear el content del archivo users.txt
        //Nombre del archivo
        strcpy(contentRaiz.b_name, "users.txt");
        //Apuntar al segundo inodo en uso
        contentRaiz.b_inodo = 1;
        //Content del archivo en la segunda posicion, la primera tiene hacia la carpeta raiz
        carpetaRaiz.b_content[1] = contentRaiz;
        //Llenar el nombre con 0s para los otros 2 content que no tienen nada
        memset(&contentRaiz.b_name, 0, sizeof(contentRaiz.b_name));
        //De momento sin inodo
        contentRaiz.b_inodo = -1;
        //Agregado a la tercera y cuarta posicion que no tienen nada
        carpetaRaiz.b_content[2] = contentRaiz;
        carpetaRaiz.b_content[3] = contentRaiz;

        //Se esta usando 1 inodo y de bloques, entonces disminuir los disponibles
        superBloque.s_free_inodes_count--;
        superBloque.s_free_blocks_count--;

        //Guardar el primer inodo en la primera posicion que es el de la carpeta
        fseek(disco2, superBloque.s_inode_start, SEEK_SET);
        fwrite(&inodo_raiz, sizeof(Inodo), 1, disco2);

        //Guardar el primer bloque en la primera posicion que es el de la carpeta
        fseek(disco2, superBloque.s_block_start, SEEK_SET);
        fwrite(&carpetaRaiz, 64, 1, disco2);


        //Crear el bloque, content y inodo para el archivo users.txt

        char informacion[]="1,G,root\n1,U,root,root,123\n";
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
        //El primer bloque directo va hacia el archivo users.txt, que seria el bloque 2 y de archivo
        usersTxt.i_block[0]=1;
        //0 para carpeta 1 para archivo
        usersTxt.i_type='1';


        //Crear el bloque para el archivo users.txt, es el bloque 1

        BloqueArchivos bloqueUsersTxt;
        //Agregar la informacion al content del bloque
        strcpy(bloqueUsersTxt.b_content,informacion);

        //El b_inodo no apunta a ningun lado queda vacio
        //Restar el bloque e inodo utilizado
        superBloque.s_free_inodes_count--;
        superBloque.s_free_blocks_count--;


        //Guardar el inodo en la segunda posicion
        fseek(disco2, superBloque.s_inode_start+sizeof(Inodo), SEEK_SET);
        fwrite(&usersTxt, sizeof(Inodo), 1, disco2);

        //Guardar el bloque en la segunda posicion
        fseek(disco2, superBloque.s_block_start+sizeof(BloqueArchivos), SEEK_SET);
        fwrite(&bloqueUsersTxt, sizeof(BloqueArchivos), 1, disco2);


        //Crear Journal para la carpeta raiz
            Journal journalRaiz;
            strcpy(journalRaiz.instruccion,"mkfs");
            journalRaiz.tipo_bloque='0';//carpeta
            strcpy(journalRaiz.nombre,"/");
            strcpy(journalRaiz.content,"-");
            time_t fechaActual = time(NULL);
            journalRaiz.fecha = fechaActual;
            strcpy(journalRaiz.usuario,"1");
            journalRaiz.permiso=664;
            //Escribir en el disco
            int posicionJournalRaiz=part_start+sizeof(SuperBloque);
            fseek(disco2,posicionJournalRaiz+0*sizeof(Journal),SEEK_SET); //Journal 1
            fwrite(&journalRaiz,sizeof(Journal),1,disco2);


            //Crear Journal para el archivo users.txt
            Journal journalUsers;
            strcpy(journalUsers.instruccion,"mkfs");
            journalUsers.tipo_bloque='1'; //Bloque archivo
            strcpy(journalUsers.nombre,"/users.txt");
            strcpy(journalUsers.content,"1,G,root\n1,U,root,root,123\n");
            journalUsers.fecha = fechaActual;
            strcpy(journalUsers.usuario,"1");
            journalUsers.permiso=664;
            //Escribir en el disco
            fseek(disco2,posicionJournalRaiz+1*sizeof(Journal),SEEK_SET); //Journal 2
            fwrite(&journalRaiz,sizeof(Journal),1,disco2);

        //Escribir el superBloque con las actualizaciones
        fseek(disco2, part_start, SEEK_SET);
        fwrite(&superBloque, sizeof(SuperBloque), 1, disco2);
        fclose(disco2);

    }



}



