%{
#include "scanner.h"//se importa el header del analisis sintactico
#include <QString>
#include <string>
#include "qdebug.h"
#include <iostream>
#include "string"
#include "iostream"
#include "obj_mkdisk.h"
#include "obj_rmdisk.h"
#include "obj_fdisk.h"
#include "obj_cat.h"
#include "obj_chgrp.h"
#include "obj_chmod.h"
#include "obj_chown.h"
#include "obj_cp.h"
#include "obj_edit.h"
#include "obj_exec.h"
#include "obj_find.h"
#include "obj_login.h"
#include "obj_logout.h"
#include "obj_loss.h"
#include "obj_mkdir.h"
#include "obj_mkfs.h"
#include "obj_mkgrp.h"
#include "obj_mkusr.h"
#include "obj_mount.h"
#include "obj_mv.h"
#include "obj_pause.h"
#include "obj_recovery.h"
#include "obj_ren.h"
#include "obj_rep.h"
#include "obj_rm.h"
#include "obj_rmgrp.h"
#include "obj_rmusr.h"
#include "obj_touch.h"
#include "obj_umount.h"


using namespace std;
extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON

std::string formatear(std::string texto){
    int validador = texto.find("\"");
    if (validador != -1){
        texto = texto.replace(validador,1,"");
        validador = texto.find("\"");
        texto = texto.replace(validador,1,"");
        //std::cout<<texto<<std::endl;
        return texto;
    }
    return texto;
}

int yyerror(const char* mens)
{
std::cout << mens <<" "<<yytext<< std::endl;
return 0;
}

%}
//error-verbose si se especifica la opcion los errores sintacticos son especificados por BISON
%defines "parser.h"
%output "parser.cpp"
%error-verbose
%locations



%union{
//se especifican los tipo de valores para los no terminales y lo terminales
//char TEXT [256];
//QString TEXT;
char TEXT[256];
class obj_mkdisk *mkdisk;
class obj_rmdisk *rmdisk;
class obj_fdisk *fdisk;
class obj_cat *cat;
class obj_chgrp *chgrp;
class obj_chmod *chmod;
class obj_chown *chown;
class obj_cp *cp;
class obj_edit *edit;
class obj_exec *exec;
class obj_find *find;
class obj_login *login;
class obj_logout *logout;
class obj_loss *loss;
class obj_mkdir *mkdir;
class obj_mkfs *mkfs;
class obj_mkgrp *mkgrp;
class obj_mkusr *mkusr;
class obj_mount *mount;
class obj_mv *mv;
class obj_pause *pause;
class obj_recovery *recovery;
class obj_ren *ren;
class obj_rep *rep;
class obj_rm *rm;
class obj_rmgrp *rmgrp;
class obj_rmusr *rmusr;
class obj_touch *touch;
class obj_umount *umount;

int numero;
char caracter[1];

}
//TERMINALES DE TIPO TEXT, SON STRINGS

%token<TEXT> pmkdisk;
%token<TEXT> prmdisk;
%token<TEXT> pfdisk;
%token<TEXT> pmount;
%token<TEXT> pumount;
%token<TEXT> pmkfs;
%token<TEXT> plogin;
%token<TEXT> plogout;
%token<TEXT> pmkgrp;
%token<TEXT> prmgrp;
%token<TEXT> pmkusr;
%token<TEXT> prmusr;
%token<TEXT> pchmod;
%token<TEXT> ptouch;
%token<TEXT> pcat;
%token<TEXT> prm;
%token<TEXT> pedit;
%token<TEXT> pren;
%token<TEXT> pmkdir;
%token<TEXT> pcp;
%token<TEXT> pmv;
%token<TEXT> pfind;
%token<TEXT> pchown;
%token<TEXT> pchgrp;
%token<TEXT> pPause;
%token<TEXT> pexec;
%token<TEXT> prep;
%token<TEXT> psize;
%token<TEXT> pF;
%token<TEXT> pU;
%token<TEXT> pR;
%token<TEXT> pP;
%token<TEXT> pE;
%token<TEXT> pL;
%token<TEXT> pK;
%token<TEXT> pM;
%token<TEXT> pB;
%token<TEXT> pPath;
%token<TEXT> ptype;
%token<TEXT> pdelete;
%token<TEXT> pname;
%token<TEXT> padd;
%token<TEXT> pid;
%token<TEXT> pfs;
%token<TEXT> puser;
%token<TEXT> pusr;
%token<TEXT> pPwd;
%token<TEXT> pgrp;
%token<TEXT> pugo;
%token<TEXT> pcont;
%token<TEXT> pstdin;
%token<TEXT> pfilen;
%token<TEXT> pdest;
%token<TEXT> pruta;
%token<TEXT> proot;
%token<TEXT> pBf;
%token<TEXT> pWf;
%token<TEXT> pFf;
%token<TEXT> pfile;
%token<TEXT> precovery;
%token<TEXT> ploss;

%token<TEXT> punto;
%token<TEXT> bracketabre;
%token<TEXT> bracketcierra;
%token<TEXT> corcheteabre;
%token<TEXT> corchetecierra;
%token<TEXT> puntocoma;
%token<TEXT> potencia;
%token<TEXT> coma;
%token<TEXT> parentesisabre;
%token<TEXT> parentesiscierra;

%token<TEXT> llaveabre;
%token<TEXT> llavecierra;
%token<TEXT> mas;
%token<TEXT> menos;
%token<TEXT> multiplicacion;
%token<TEXT> igual;
%token<TEXT> dolar;
%token<TEXT> dospuntos;

%token<TEXT> entero;
%token<TEXT> numnegativo;
%token<TEXT> cadena;
%token<TEXT> identificador;
%token<TEXT> caracter;
%token<TEXT> ruta;
%token<TEXT> rutacualquiera;
%token<TEXT> tpath;
%token<TEXT> fast;
%token<TEXT> full;
%token<TEXT> ext2;
%token<TEXT> ext3;
%token<TEXT> mbr;
%token<TEXT> disk;

%type<mkdisk>       COMANDO_MKDISK; // lista de instrucciones
//%type<TEXT>         COMANDO_MKDISK_UNIDAD;
%type<numero>       COMANDO_AJUSTE;
%type<rmdisk>       COMANDO_RMDISK;
%type<fdisk>        COMANDO_FDISK;
//%type<TEXT>         TIPO_PARTICION;
//%type<TEXT>         UNIDAD_PARTICION;
%type<mount>        COMANDO_MOUNT;
%type<umount>       COMANDO_UMOUNT;
%type<exec>         COMANDO_EXEC;
%type<mkfs>         COMANDO_MKFS;
%type<rep>          COMANDO_REP;
%type<pause>        COMANDO_PAUSE
//%type<cat>      COMANDO_CAT
//%type<chgrp>    COMANDO_CHGRP
//%type<chmod>    COMANDO_CHMOD
//%type<chown>    COMANDO_CHOWN
//%type<cp>       COMANDO_CP
//%type<edit>     COMANDO_EDIT
//%type<find>     COMANDO_FIND
//%type<login>    COMANDO_LOGIN
//%type<logout>   COMANDO_LOGOUT
//%type<loss>     COMANDO_LOSS
//%type<mkdir>    COMANDO_MKDIR
//%type<mkgrp>    COMANDO_MKGRP
//%type<mkusr>    COMANDO_MKUSR
//%type<mv>       COMANDO_MV

//%type<recovery> COMANDO_RECOVERY
//%type<ren>      COMANDO_REN

//%type<rm>       COMANDO_RM
//%type<rmgrp>    COMANDO_RMGRP
//%type<rmusr>    COMANDO_RMUSR
//%type<touch>    COMANDO_TOUCH



%left suma menos
%left multi division
%left potencia
%start INICIO
%%

INICIO : LEXPA { }
;
//\0
LEXPA
:       pmkdisk     COMANDO_MKDISK  {$2->ejecutar();}
|       prmdisk     COMANDO_RMDISK  {$2->ejecutar();}
|       pfdisk      COMANDO_FDISK   {$2->ejecutar();}
|       pmount      COMANDO_MOUNT   {$2->ejecutar();}
|       pumount     COMANDO_UMOUNT  {$2->ejecutar();}
|       pmkfs       COMANDO_MKFS    {$2->ejecutar();}
|       pexec       COMANDO_EXEC    {$2->ejecutar();}
|       prep        COMANDO_REP     {$2->ejecutar();}
|       pPause      COMANDO_PAUSE
{
    obj_pause *disco = new obj_pause();
    disco->ejecutar();
}
|
//|       pcat        COMANDO_CAT
//|       pchgrp      COMANDO_CHGRP
//|       pchmod      COMANDO_CHMOD
//|       pchown      COMANDO_CHOWN
//|       pcp         COMANDO_CP
//|       pedit       COMANDO_EDIT
//|       pfind       COMANDO_FIND
//|       plogin      COMANDO_LOGIN
//|       plogout     COMANDO_LOGOUT
//|       ploss       COMANDO_LOSS
//|       pmkdir      COMANDO_MKDIR
//|       pmkfs       COMANDO_MKFS
//|       pmkgrp      COMANDO_MKGRP
//|       pmkusr      COMANDO_MKUSR
//|       pmv         COMANDO_MV

//|       precovery   COMANDO_RECOVERY
//|       pren        COMANDO_REN
//|       prm         COMANDO_RM
//|       prmdisk     COMANDO_RMDISK
//|       prmgrp      COMANDO_RMGRP
//|       prmusr      COMANDO_RMUSR
//|       ptouch      COMANDO_TOUCH

{


//$2->ejecutar();
//$2->mostrardatos($2);//ejecuto el metodo "mostrardatos" del objeto retornado en COMANDOMKDISK
//printf("estoy en lexpa primera produccion");
}


;

COMANDO_MKDISK
:	COMANDO_MKDISK menos psize igual entero {int tam=atoi($5); $1->size=tam;  $$=$1;}
|	menos psize igual entero {int tam=atoi($4); obj_mkdisk *disco=new obj_mkdisk(); disco->size=tam; $$=disco;}

|	COMANDO_MKDISK menos pF igual COMANDO_AJUSTE {$1->f =$5; $$=$1;}
|	menos pF igual COMANDO_AJUSTE {int ajuste=$4; obj_mkdisk *disco=new obj_mkdisk(); disco->f=ajuste;  $$=disco;}

|	COMANDO_MKDISK menos pPath igual tpath {$1->path = formatear($5);$$=$1;}
|	COMANDO_MKDISK menos pPath igual cadena {$1->path = formatear($5); $$=$1;}

|	menos pPath igual tpath {obj_mkdisk *disco=new obj_mkdisk(); disco->path=formatear($4);  $$=disco;}
|	menos pPath igual cadena {obj_mkdisk *disco=new obj_mkdisk(); disco->path=formatear($4);  $$=disco;}


|	COMANDO_MKDISK menos pU igual pK {$1->u = $5; $$=$1;}
|	COMANDO_MKDISK menos pU igual pM {$1->u = $5; $$=$1;}

|	menos pU igual pK {obj_mkdisk *disco=new obj_mkdisk(); disco->u=$4;  $$=disco;}
|	menos pU igual pM {obj_mkdisk *disco=new obj_mkdisk(); disco->u=$4;  $$=disco;}
;


COMANDO_AJUSTE
:	pBf {int tipo=0; $$=tipo;}
|	pFf {int tipo=1; $$=tipo;}
|	pWf {int tipo=2; $$=tipo;}
;

/*
COMANDO_MKDISK_UNIDAD
:   pK  {$$="K";}
|   pM  {$$="M";}
;
*/


COMANDO_RMDISK
:   menos pPath igual tpath {obj_rmdisk *disco=new obj_rmdisk();disco->path=formatear($4); $$=disco;}
|   menos pPath igual cadena {obj_rmdisk *disco=new obj_rmdisk();disco->path=formatear($4); $$=disco;}
;

COMANDO_FDISK
:   COMANDO_FDISK menos psize igual entero {int tam =atoi($5); $1->size = tam;$$=$1;}
|   menos psize igual entero {obj_fdisk *disco=new obj_fdisk(); int tam =atoi($4); disco->size = tam; $$ = disco;}

|   COMANDO_FDISK menos pU igual pB {$1->u = 0; $$ = $1;}
|   COMANDO_FDISK menos pU igual pK {$1->u = 1; $$ = $1;}
|   COMANDO_FDISK menos pU igual pM {$1->u = 2; $$ = $1;}

|   menos pU igual pB {obj_fdisk *disco=new obj_fdisk();disco->u = 0;$$=disco;}
|   menos pU igual pK {obj_fdisk *disco=new obj_fdisk();disco->u = 1;$$=disco;}
|   menos pU igual pM {obj_fdisk *disco=new obj_fdisk();disco->u = 2;$$=disco;}

|   COMANDO_FDISK menos pPath igual tpath {$1->path = formatear($5); $$ = $1;}
|   menos pPath igual tpath {obj_fdisk *disco=new obj_fdisk(); disco->path =formatear($4);$$ = disco;}

|   COMANDO_FDISK menos pPath igual cadena {$1->path = formatear($5); $$ = $1;}
|   menos pPath igual cadena {obj_fdisk *disco=new obj_fdisk(); disco->path =formatear($4);$$ = disco;}


|   COMANDO_FDISK menos ptype igual pP {$1->type = 0; $$ = $1;}
|   COMANDO_FDISK menos ptype igual pE {$1->type = 1; $$ = $1;}
|   COMANDO_FDISK menos ptype igual pL {$1->type = 2; $$ = $1;}

|   menos ptype igual pP {obj_fdisk *disco=new obj_fdisk(); disco->type=0; $$ =disco;}
|   menos ptype igual pE {obj_fdisk *disco=new obj_fdisk(); disco->type=1; $$ =disco;}
|   menos ptype igual pL {obj_fdisk *disco=new obj_fdisk(); disco->type=2; $$ =disco;}


|   COMANDO_FDISK menos pF igual COMANDO_AJUSTE {$1->f = $5; $$ = $1;}
|   menos pF igual COMANDO_AJUSTE {obj_fdisk *disco=new obj_fdisk(); disco->f =$4;$$=disco;}

|   COMANDO_FDISK menos pdelete igual fast {$1->eliminar = 1;$1->tipo_eliminar =0;$$=$1;}
|   menos pdelete igual fast {obj_fdisk *disco=new obj_fdisk(); disco->eliminar = 1;disco->tipo_eliminar =0; $$=disco;}

|   COMANDO_FDISK menos pdelete igual full {$1->eliminar = 1;$1->tipo_eliminar =1;$$=$1;}
|   menos pdelete igual full {obj_fdisk *disco=new obj_fdisk(); disco->eliminar = 1;disco->tipo_eliminar =1; $$=disco;}


|   COMANDO_FDISK menos pname igual identificador {$1->name = formatear($5); $$=$1;}
|   menos pname igual identificador {obj_fdisk *disco=new obj_fdisk(); disco->name = formatear($4); $$=disco;}

|   COMANDO_FDISK menos pname igual cadena {$1->name = formatear($5); $$=$1;}
|   menos pname igual cadena {obj_fdisk *disco=new obj_fdisk(); disco->name = formatear($4); $$=disco;}

|   COMANDO_FDISK menos padd igual entero {$1->size = atoi($5);$1->add = 1; $$=$1;}
|   menos padd igual entero {obj_fdisk *disco=new obj_fdisk(); disco->size = atoi($4);disco->add = 1; $$=disco;}

|   COMANDO_FDISK menos padd igual menos entero {int num =atoi($6); num = num*-1; $1->size = num;$1->add = 1; $$=$1;}
|   menos padd igual menos entero {obj_fdisk *disco=new obj_fdisk();int num =atoi($5); num = num*-1; disco->size = num; disco->add = 1; $$=disco;}
;


/*
TIPO_PARTICION
:   pP {$$ = 'P';}
|   pE {$$ = 'E';}
|   pL {$$ = 'L';}
;
*/

/*
UNIDAD_PARTICION
:   pB  {$$='B';}
|   pK  {$$='K';}
|   pM  {$$='M';}
;
*/

COMANDO_MOUNT
:   COMANDO_MOUNT menos pPath igual tpath {$1->path = formatear($5); $$ = $1;}
|   menos pPath igual tpath {obj_mount *disco=new obj_mount(); disco->path = formatear($4); $$ = disco;}

|   COMANDO_MOUNT menos pPath igual cadena {$1->path = formatear($5); $$ = $1;}
|   menos pPath igual cadena {obj_mount *disco=new obj_mount(); disco->path = formatear($4); $$ = disco;}

|   COMANDO_MOUNT menos pname igual identificador {$1->name = formatear($5); $$ = $1;}
|   menos pname igual identificador {obj_mount *disco=new obj_mount(); disco->name = formatear($4); $$ = disco;}

|   COMANDO_MOUNT menos pname igual cadena {$1->name = formatear($5); $$ = $1;}
|   menos pname igual cadena {obj_mount *disco=new obj_mount(); disco->name = formatear($4); $$ = disco;}
;


COMANDO_UMOUNT
:   menos pid igual identificador {obj_umount *disco=new obj_umount(); disco->id=formatear($4); $$ = disco;}
|   menos pid igual cadena {obj_umount *disco=new obj_umount(); disco->id=formatear($4); $$ = disco;}
;

COMANDO_EXEC
:   menos pPath igual tpath {obj_exec *disco=new obj_exec(); disco->path=formatear($4); $$=disco;}
|   menos pPath igual cadena {obj_exec *disco=new obj_exec(); disco->path=formatear($4); $$=disco;}
;



COMANDO_MKFS
:   COMANDO_MKFS menos pid igual identificador {$1->id = formatear($5); $$ = $1;}
|   menos pid igual identificador {obj_mkfs *disco = new obj_mkfs(); disco->id = formatear($4); $$ = disco;}

|   COMANDO_MKFS menos pid igual cadena {$1->id = formatear($5); $$ = $1;}
|   menos pid igual cadena {obj_mkfs *disco = new obj_mkfs(); disco->id = formatear($4); $$ = disco;}

|   COMANDO_MKFS menos ptype igual fast {$1->type = 0; $$ = $1;}
|   menos ptype igual fast {obj_mkfs *disco = new obj_mkfs(); disco->type = 0; $$ = disco;}

|   COMANDO_MKFS menos ptype igual full {$1->type = 1; $$ = $1;}
|   menos ptype igual full {obj_mkfs *disco = new obj_mkfs(); disco->type = 1; $$ = disco;}

|   COMANDO_MKFS menos pfs igual ext2 {$1->fs = 2; $$ = $1;}
|   menos pfs igual ext2 {obj_mkfs *disco = new obj_mkfs(); disco->fs = 2; $$ = disco;}

|   COMANDO_MKFS menos pfs igual ext3 {$1->fs = 3; $$ = $1;}
|   menos pfs igual ext3 {obj_mkfs *disco = new obj_mkfs(); disco->fs = 3; $$ = disco;}
;
;




COMANDO_REP
:   COMANDO_REP menos pname igual mbr {$1->name = "mbr"; $$ = $1;}
|   menos pname igual mbr {obj_rep *disco = new obj_rep();disco->name = "mbr"; $$ = disco;}

|   COMANDO_REP menos pname igual disk {$1->name = "disk"; $$ = $1;}
|   menos pname igual disk {obj_rep *disco = new obj_rep();disco->name = "disk"; $$ = disco;}


|   COMANDO_REP menos pPath igual tpath {$1->path = formatear($5); $$ = $1;}
|   menos pPath igual tpath {obj_rep *disco = new obj_rep();disco->path = formatear($4); $$ = disco;}

|   COMANDO_REP menos pPath igual cadena {$1->path = formatear($5); $$ = $1;}
|   menos pPath igual cadena {obj_rep *disco = new obj_rep();disco->path = formatear($4); $$ = disco;}

|   COMANDO_REP menos pid igual identificador {$1->id = formatear($5); $$ = $1;}
|   menos pid igual identificador {obj_rep *disco = new obj_rep();disco->id = formatear($4); $$ = disco;}

|   COMANDO_REP menos pid igual cadena {$1->id = formatear($5); $$ = $1;}
|   menos pid igual cadena {obj_rep *disco = new obj_rep();disco->id = formatear($4); $$ = disco;}

/*
|   COMANDO_REP menos pruta igual identificador {}
|   menos pruta igual identificador {}

|   COMANDO_REP menos proot igual identificador {}
|   menos proot igual identificador {}
*/

COMANDO_PAUSE
:   {obj_pause *disco = new obj_pause(); $$ = disco;}
;










