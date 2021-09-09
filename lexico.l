%option case-insensitive
%option yylineno

%{
#include <iostream>
#include <QString>
#include "parser.h"

#include <string>
#include <QList>

    int yylex();
    void yyerror(const char *s);
    int linea = 0;
    int columna = 1;
    int anterior = 0;


%}
%option noyywrap
%option nounput





entero [0-9]+
letra [a-zA-ZÑñáéíóúÁÉÍÓÚ]+


comens #[^#\n\r]*
cadena \"([^(\"|"#")])*\"
tpath "/"([^("\n"|"\t"|"\r"|"\f"|" ")])*
identificador ({letra}|{entero})({letra}|{entero}|"_")*
caracter "\'"("\\")?({letra}|{entero})"\'"






%x COM


%%

"MKDISK"    {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pmkdisk;}
"RMDISK"	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return prmdisk;}
"FDISK"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pfdisk;}
"MOUNT"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pmount;}
"UMOUNT"	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pumount;}
"MKFS"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pmkfs;}
"LOGIN"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return plogin;}
"LOGOUT"	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return plogout;}
"MKGRP"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pmkgrp;}
"RMGRP"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return prmgrp;}
"MKUSR"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pmkusr;}
"RMUSR"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return prmusr;}
"CHMOD"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pchmod;}
"TOUCH"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return ptouch;}
"CAT"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pcat;}
"RM"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return prm;}
"EDIT"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pedit;}
"REN"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pren;}
"MKDIR"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pmkdir;}
"CP"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pcp;}
"MV"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pmv;}
"FIND"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pfind;}
"CHOWN"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pchown;}
"CHGRP"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pchgrp;}
"PAUSE"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pPause;}
"EXEC"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pexec;}
"REP"		{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return prep;}



"SIZE"      {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return psize;}
"F"         {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pF;}
"U"         {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pU;}
"R"			{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pR;}
"P"			{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pP;}
"E"         {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pE;}
"L"         {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pL;}
"K"         {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pK;}
"M"         {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pM;}
"B"         {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pB;}
"PATH"      {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pPath;}
"TYPE"		{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return ptype;}
"DELETE"	{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pdelete;}
"NAME"		{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pname;}
"ADD"		{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return padd;}
"ID"		{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pid;}
"FS"		{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pfs;}
"USER"		{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return puser;}
"PWD"		{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pPwd;}
"USR"		{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pusr;}
"GRP"		{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pgrp;}
"UGO"		{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pugo;}
"CONT"		{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pcont;}
"STDIN"		{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pstdin;}
"FILEN"		{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pfilen;}
"DEST"		{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pdest;}
"RUTA"		{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pruta;}
"ROOT"		{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return proot;}
"BF"		{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pBf;}
"WF"		{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pWf;}
"FF"		{columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pFf;}
"FILE"      {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return pfile;}
"RECOVERY"  {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return precovery;}
"LOSS"      {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return ploss;}
"FAST"      {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return fast;}
"FULL"      {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return full;}
"2FS"       {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return ext2;}
"3FS"       {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return ext3;}
"MBR"       {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return mbr;}
"DISK"      {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return disk;}


{entero} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return entero;}
{cadena} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return cadena;}
{identificador} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return identificador;}
{caracter} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return caracter;}
{tpath} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return tpath;}
{comens}	{/*a C comment*/}

"." {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return punto;}
"<" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return bracketabre;}
">" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return bracketcierra;}
"[" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return corcheteabre;}
"]" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return corchetecierra;}
";" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return puntocoma;}
"^" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return potencia;}
"," {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return coma;}
"(" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return parentesisabre;}
")" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return parentesiscierra;}
"{" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return llaveabre;}
"}" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return llavecierra;}
"+" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return mas;}
"-" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return menos;}
"*" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return multiplicacion;}
"=" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return igual;}
"$" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return dolar;}
":" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return dospuntos;}

"\n" {linea++; columna=0; anterior=0;}
[[:blank:]] { columna++; }



.   {

std::cout<<"Error Lexico: "<<linea<<"\n";

}
