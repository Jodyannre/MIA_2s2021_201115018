#include <QCoreApplication>
#include "iostream"
#include "string"
#include <QString>
#include <parser.h>  // Nuestro parser
#include <scanner.h>  // Nuestro scanner
#include <QTextStream>
#include <obj_mkdisk.h>
#include "time.h"
#include "obj_rep.h"


using namespace std;
extern int yyparse(); //
//static QList<discosmontados> discosenmemoria
int p;
extern int linea; // Linea del token
extern int columna; // Columna de los tokens
extern int yylineno;
int main(int argc, char *argv[])
{

    /*
    //Pruebas mkfs
    MBR mbr;
    FILE *disco;
    SuperBloque super;
    Inodo iraiz;
    Inodo archivo;
    BloqueArchivos bArchivo;
    BloqueCarpetas bCarpeta;
    char bitmapInodos[16];
    char bitmapBloques[3*16];
    Journal journal;
    string path = "/home/joddie/Desktop/archivos/proyecto1/disco1.dk";
    //string path = "/home/joddie/Desktop/archivos/proyecto1/build-proyecto1-Desktop_Qt_6_1_2_GCC_64bit-Debug/dsmount.data";
    disco =fopen(path.c_str(),"rb+");
    fseek(disco, 0, SEEK_SET);
    fread(&mbr,sizeof(MBR),1,disco);
    fseek(disco,mbr.mbr_partitions[1].part_start,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,disco);
    fseek(disco,super.s_inode_start,SEEK_SET);
    fread(&iraiz,sizeof(Inodo),1,disco);
    fseek(disco,super.s_inode_start+super.s_inode_size,SEEK_SET);
    fread(&archivo,sizeof(Inodo),1,disco);
    fseek(disco,super.s_block_start,SEEK_SET);
    fread(&bCarpeta,sizeof(BloqueCarpetas),1,disco);
    fseek(disco,super.s_block_start+super.s_block_size,SEEK_SET);
    fread(&bArchivo,sizeof(BloqueArchivos),1,disco);
    fseek(disco,mbr.mbr_partitions[1].part_start+sizeof(SuperBloque),SEEK_SET);
    fread(&bitmapInodos,sizeof(bitmapInodos),1,disco);
    fseek(disco,mbr.mbr_partitions[1].part_start+sizeof(SuperBloque)+sizeof(bitmapInodos),SEEK_SET);
    fread(&bitmapBloques,sizeof(bitmapBloques),1,disco);
    */



/*
    //Reportes
    obj_rep *reporte = new obj_rep();
    string direccion ="/home/joddie/Desktop/archivos/proyecto1/reportes/reporte2.pdf";
    string tipo="dISk";
    string id="181B";
    reporte->id = id;
    reporte->name = tipo;
    reporte->path = direccion;
    reporte->ejecutar();
    return 0;
*/

/*
//Obtener el tiempo
    time_t raw_time;
    struct tm *tiempo;
    raw_time = time(NULL);
    tiempo = gmtime(&raw_time);
    return 0;
*/


/*
    //string path = "/home/joddie/Desktop/archivos/proyecto1/disco1.dk";
    string path = "/home/joddie/Desktop/archivos/proyecto1/build-proyecto1-Desktop_Qt_6_1_2_GCC_64bit-Debug/dsmount.data";
    FILE *disco;
    char unidades,tipo;
    int particion_size;
    //Buscar el disco y verificar si existe
    disco =fopen(path.c_str(),"rb+");
    Cmount cmount;


    fseek(disco, 0, SEEK_SET);
    fread(&cmount,sizeof(Cmount),1,disco);

    //Buscar la posicion del mbr del disco
    //MBR para copiar temporalmente el mbr que contiene el disco
    MBR mbr_temp;
    EBR ebr_temp;
    EBR ebr_sig;
    EBR ebr_sig_sig;
    //Copiar el mbr del disco al mbr temporal
    fread(&mbr_temp,sizeof(MBR),1,disco);
    fseek(disco,mbr_temp.mbr_partitions[0].part_start, SEEK_SET);
    fread(&ebr_temp,sizeof(EBR),1,disco);
    fseek(disco,ebr_temp.part_next, SEEK_SET);
    fread(&ebr_sig,sizeof(EBR),1,disco);
    fseek(disco,ebr_sig.part_next, SEEK_SET);
    fread(&ebr_sig_sig,sizeof(EBR),1,disco);

    cout<<"Resultados"<<endl;
    cout<<"------------------------------------------"<<endl;
    cout<<mbr_temp.disk_fit<<endl;
    cout<<mbr_temp.mbr_disk_signature<<endl;
    cout<<mbr_temp.mbr_tamano<<endl;
    cout<<"------------------------------------------"<<endl;
    cout<<mbr_temp.mbr_partitions[0].part_status<<endl;
    cout<<mbr_temp.mbr_partitions[0].part_name<<endl;
    cout<<mbr_temp.mbr_partitions[0].part_fit<<endl;
    cout<<mbr_temp.mbr_partitions[0].part_start<<endl;
    cout<<mbr_temp.mbr_partitions[0].part_size<<endl;
    cout<<"------------------------------------------"<<endl;
    cout<<mbr_temp.mbr_partitions[1].part_status<<endl;
    cout<<mbr_temp.mbr_partitions[1].part_name<<endl;
    cout<<mbr_temp.mbr_partitions[1].part_fit<<endl;
    cout<<mbr_temp.mbr_partitions[1].part_start<<endl;
    cout<<mbr_temp.mbr_partitions[1].part_size<<endl;
    cout<<"------------------------------------------"<<endl;
    cout<<mbr_temp.mbr_partitions[2].part_status<<endl;
    cout<<mbr_temp.mbr_partitions[2].part_name<<endl;
    cout<<mbr_temp.mbr_partitions[2].part_fit<<endl;
    cout<<mbr_temp.mbr_partitions[2].part_start<<endl;
    cout<<mbr_temp.mbr_partitions[2].part_size<<endl;
    cout<<"------------------------------------------"<<endl;
    cout<<mbr_temp.mbr_partitions[3].part_status<<endl;
    cout<<mbr_temp.mbr_partitions[3].part_name<<endl;
    cout<<mbr_temp.mbr_partitions[3].part_fit<<endl;
    cout<<mbr_temp.mbr_partitions[3].part_start<<endl;
    cout<<mbr_temp.mbr_partitions[3].part_size<<endl;
    cout<<"------------------------------------------"<<endl;
    cout<<ebr_temp.part_name<<endl;
    cout<<ebr_temp.part_next<<endl;
    cout<<ebr_temp.part_fit<<endl;
    cout<<ebr_temp.part_status<<endl;
    cout<<ebr_temp.part_start<<endl;
    cout<<"------------------------------------------"<<endl;
    cout<<ebr_sig.part_name<<endl;
    cout<<ebr_sig.part_next<<endl;
    cout<<ebr_sig.part_fit<<endl;
    cout<<ebr_sig.part_status<<endl;
    cout<<ebr_sig.part_start<<endl;
    cout<<"------------------------------------------"<<endl;
    cout<<ebr_sig_sig.part_name<<endl;
    cout<<ebr_sig_sig.part_next<<endl;
    cout<<ebr_sig_sig.part_fit<<endl;
    cout<<ebr_sig_sig.part_status<<endl;
    cout<<ebr_sig_sig.part_start<<endl;
    cout<<ebr_sig_sig.part_size<<endl;
    return 1;

*/

//-----------------------------------------------------------------------------------------------


    string lista ="";
    for (int i=1; i < argc; i++){
        lista += argv[i];
        lista += " ";

    }
    string p="------------------------------Comando ingresado------------------------------\n";
    //QTextStream qtin(stdin);
    QString line;
    //lista = "mkdisk -size = 2 -u = m -path = /home/joddie/Desktop/archivos/proyecto1/hola1/hola2/hola3/disco1.dk";
    //lista ="fdisk -delete = fast -name=particion3 -path = /home/joddie/Desktop/archivos/proyecto1/disco1.dk";
    //lista ="fdisk -size = 5 -name = particion1 -type=E -path = /home/joddie/Desktop/archivos/proyecto1/disco1.dk";
    //lista ="fdisk -size = 5 -name = particion2 -path = /home/joddie/Desktop/archivos/proyecto1/disco1.dk";
    //lista ="fdisk -size = 1 -name = particion3 -type=L -path = /home/joddie/Desktop/archivos/proyecto1/disco1.dk";
    //lista = "fdisk -add = 5 -u=k -name = particion3 -path = /home/joddie/Desktop/archivos/proyecto1/disco1.dk";
    //lista = "mount -path = /home/joddie/Desktop/archivos/proyecto1/disco1.dk -name = particion1";
    //lista = "mount -path = /home/joddie/Desktop/archivos/proyecto1/disco1.dk -name = particion2";
    //lista = "mount -path = /home/joddie/Desktop/archivos/proyecto1/disco1.dk -name = particion3";
    //lista = "umount -id = 181C";
    //lista = "exec -path = /home/joddie/Desktop/archivos/proyecto1/comandos.sh";
    //lista = "mount -path=/home/joddie/Desktop/archivos/calificacion/discoscalificacion/discooficial.dk -name = p1";
    //lista = "rep -id=181A -path = /home/joddie/Desktop/archivos/calificacion/reportes/reporte1.pdf -name = disk";
    //lista = "rep -id=181A -path = /home/joddie/Desktop/archivos/calificacion/reportes/reporte1.pdf -name = mbr";

    //lista = "pause";
    line = QString::fromStdString(lista);
    if(line!="salir"){
        if(line.isEmpty()==false){
            YY_BUFFER_STATE buffer = yy_scan_string(line.toUtf8().constData());
            linea = 0;
            columna = 0;
            yylineno = 0;

            if(yyparse()==0) // Si nos da un número negativo, signifca error.
            {
                //printf("\n\Comando ejecutado correctamente\n\n");

            }else {

                //printf("\n\nhay errores\n\n");
            }

        }
    }


    return 0;
}





