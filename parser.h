/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    pmkdisk = 258,
    prmdisk = 259,
    pfdisk = 260,
    pmount = 261,
    pumount = 262,
    pmkfs = 263,
    plogin = 264,
    plogout = 265,
    pmkgrp = 266,
    prmgrp = 267,
    pmkusr = 268,
    prmusr = 269,
    pchmod = 270,
    ptouch = 271,
    pcat = 272,
    prm = 273,
    pedit = 274,
    pren = 275,
    pmkdir = 276,
    pcp = 277,
    pmv = 278,
    pfind = 279,
    pchown = 280,
    pchgrp = 281,
    pPause = 282,
    pexec = 283,
    prep = 284,
    psize = 285,
    pF = 286,
    pU = 287,
    pR = 288,
    pP = 289,
    pPath = 290,
    ptype = 291,
    pdelete = 292,
    pname = 293,
    padd = 294,
    pid = 295,
    pfs = 296,
    puser = 297,
    pusr = 298,
    pPwd = 299,
    pgrp = 300,
    pugo = 301,
    pcont = 302,
    pstdin = 303,
    pfilen = 304,
    pdest = 305,
    pruta = 306,
    proot = 307,
    pBf = 308,
    pWf = 309,
    pFf = 310,
    pfile = 311,
    precovery = 312,
    ploss = 313,
    punto = 314,
    bracketabre = 315,
    bracketcierra = 316,
    corcheteabre = 317,
    corchetecierra = 318,
    puntocoma = 319,
    potencia = 320,
    coma = 321,
    parentesisabre = 322,
    parentesiscierra = 323,
    llaveabre = 324,
    llavecierra = 325,
    mas = 326,
    menos = 327,
    multiplicacion = 328,
    igual = 329,
    dolar = 330,
    dospuntos = 331,
    entero = 332,
    numnegativo = 333,
    cadena = 334,
    identificador = 335,
    caracter = 336,
    ruta = 337,
    rutacualquiera = 338,
    tpath = 339,
    suma = 340,
    multi = 341,
    division = 342
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 53 "parser.y" /* yacc.c:1909  */

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

#line 180 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
