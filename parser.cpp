/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

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


#line 130 "parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
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
    pE = 290,
    pL = 291,
    pK = 292,
    pM = 293,
    pB = 294,
    pPath = 295,
    ptype = 296,
    pdelete = 297,
    pname = 298,
    padd = 299,
    pid = 300,
    pfs = 301,
    puser = 302,
    pusr = 303,
    pPwd = 304,
    pgrp = 305,
    pugo = 306,
    pcont = 307,
    pstdin = 308,
    pfilen = 309,
    pdest = 310,
    pruta = 311,
    proot = 312,
    pBf = 313,
    pWf = 314,
    pFf = 315,
    pfile = 316,
    precovery = 317,
    ploss = 318,
    punto = 319,
    bracketabre = 320,
    bracketcierra = 321,
    corcheteabre = 322,
    corchetecierra = 323,
    puntocoma = 324,
    potencia = 325,
    coma = 326,
    parentesisabre = 327,
    parentesiscierra = 328,
    llaveabre = 329,
    llavecierra = 330,
    mas = 331,
    menos = 332,
    multiplicacion = 333,
    igual = 334,
    dolar = 335,
    dospuntos = 336,
    entero = 337,
    numnegativo = 338,
    cadena = 339,
    identificador = 340,
    caracter = 341,
    ruta = 342,
    rutacualquiera = 343,
    tpath = 344,
    fast = 345,
    full = 346,
    ext2 = 347,
    ext3 = 348,
    mbr = 349,
    disk = 350,
    suma = 351,
    multi = 352,
    division = 353
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 72 "parser.y" /* yacc.c:355  */

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


#line 309 "parser.cpp" /* yacc.c:355  */
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

/* Copy the second part of user declarations.  */

#line 340 "parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   204

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  99
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  208

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   353

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   254,   254,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   296,   308,   309,   311,   312,   314,   315,   317,
     318,   321,   322,   324,   325,   330,   331,   332,   344,   345,
     349,   350,   352,   353,   354,   356,   357,   358,   360,   361,
     363,   364,   367,   368,   369,   371,   372,   373,   376,   377,
     379,   380,   382,   383,   386,   387,   389,   390,   392,   393,
     395,   396,   417,   418,   420,   421,   423,   424,   426,   427,
     432,   433,   437,   438,   444,   445,   447,   448,   450,   451,
     453,   454,   456,   457,   459,   460,   468,   469,   471,   472,
     475,   476,   478,   479,   481,   482,   484,   485,   496
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "pmkdisk", "prmdisk", "pfdisk", "pmount",
  "pumount", "pmkfs", "plogin", "plogout", "pmkgrp", "prmgrp", "pmkusr",
  "prmusr", "pchmod", "ptouch", "pcat", "prm", "pedit", "pren", "pmkdir",
  "pcp", "pmv", "pfind", "pchown", "pchgrp", "pPause", "pexec", "prep",
  "psize", "pF", "pU", "pR", "pP", "pE", "pL", "pK", "pM", "pB", "pPath",
  "ptype", "pdelete", "pname", "padd", "pid", "pfs", "puser", "pusr",
  "pPwd", "pgrp", "pugo", "pcont", "pstdin", "pfilen", "pdest", "pruta",
  "proot", "pBf", "pWf", "pFf", "pfile", "precovery", "ploss", "punto",
  "bracketabre", "bracketcierra", "corcheteabre", "corchetecierra",
  "puntocoma", "potencia", "coma", "parentesisabre", "parentesiscierra",
  "llaveabre", "llavecierra", "mas", "menos", "multiplicacion", "igual",
  "dolar", "dospuntos", "entero", "numnegativo", "cadena", "identificador",
  "caracter", "ruta", "rutacualquiera", "tpath", "fast", "full", "ext2",
  "ext3", "mbr", "disk", "suma", "multi", "division", "$accept", "INICIO",
  "LEXPA", "COMANDO_MKDISK", "COMANDO_AJUSTE", "COMANDO_RMDISK",
  "COMANDO_FDISK", "COMANDO_MOUNT", "COMANDO_UMOUNT", "COMANDO_EXEC",
  "COMANDO_MKFS", "COMANDO_REP", "COMANDO_PAUSE", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353
};
# endif

#define YYPACT_NINF -79

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-79)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -2,   -49,    33,    53,    60,    61,    62,   -79,    63,    64,
      76,   -79,    -1,    66,    55,   -79,   -23,    67,    37,    68,
      74,   -79,   -31,    69,   -79,   102,   -79,     4,    70,   -79,
       2,    71,    72,    73,    10,    75,    77,    78,    79,    81,
      82,    83,    84,    85,    -8,    86,    87,    42,    88,    89,
      90,    91,     7,    92,    93,    94,    95,    11,   -21,    28,
       0,   -73,    96,    97,    98,    99,   -29,   100,    28,    52,
     -27,    58,   -78,   -39,   -19,   101,   104,   105,   106,   107,
     108,   109,   110,   -25,    18,   111,   112,    20,    16,    24,
      19,   113,   114,   115,   -18,   -17,    21,    29,   116,   117,
     118,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,
     119,    28,    80,   -16,   -79,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,
     120,   -79,   121,    28,    59,   -15,    65,    30,    38,    -7,
     -79,   -79,   -79,   -79,    -6,    40,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,    36,    44,    39,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,    -5,    41,    49,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   122,
     -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      12,     0,     0,     0,     0,     0,     0,    98,     0,     0,
       0,     2,     0,     3,     0,     4,     0,     5,     0,     6,
       0,     7,     0,     8,    11,     0,     9,     0,    10,     1,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    14,    25,    27,    26,    16,    23,    24,    20,    19,
       0,     0,     0,     0,    29,    28,    31,    49,    36,    37,
      35,    41,    39,    45,    46,    47,    51,    53,    57,    55,
       0,    59,     0,     0,     0,     0,     0,     0,     0,     0,
      65,    63,    69,    67,     0,     0,    71,    70,    79,    81,
      77,    75,    83,    85,     0,     0,     0,    73,    72,    93,
      91,    87,    89,    97,    95,     0,     0,     0,    13,    15,
      21,    22,    18,    17,    61,    30,    48,    33,    34,    32,
      40,    38,    42,    43,    44,    50,    52,    56,    54,     0,
      58,    64,    62,    68,    66,    78,    80,    76,    74,    82,
      84,    92,    90,    86,    88,    96,    94,    60
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -79,   -79,   -79,   -79,   -68,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,   -79
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    10,    11,    13,   105,    15,    17,    19,    21,    26,
      23,    28,    24
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     117,     1,     2,     3,     4,     5,     6,    36,    37,    38,
      49,   108,   126,   127,    50,    51,   109,    39,    40,    41,
      42,    43,    75,    76,    77,     7,     8,     9,    12,    30,
      31,    32,    78,    79,    80,    81,    82,   106,   107,    33,
      62,    63,    64,   169,    54,   128,   129,    55,    91,    56,
      65,    98,    92,    93,    99,   114,   100,   121,   130,   140,
     115,   101,   122,   131,   141,   176,   157,   159,   172,   180,
     189,   158,   160,   173,   181,   190,    29,    45,   191,   201,
      46,    58,    85,   192,   202,    86,   102,   103,   104,   118,
     119,   120,   123,   124,   125,    35,   177,   178,   179,   182,
     183,   184,   142,   143,   146,   147,   148,   149,   150,   151,
      14,   152,   153,   163,   164,   161,   162,   170,   171,    48,
     185,   186,   187,   188,   193,   194,   195,   196,   197,   198,
      16,   199,   200,   205,   206,   203,   204,    18,    20,    22,
      25,    27,    53,    34,    44,    47,    52,    57,     0,     0,
      59,    60,    61,     0,    66,     0,    67,    68,    69,     0,
      70,    71,    72,    73,    74,    83,    84,    87,    88,    89,
      90,    94,    95,    96,    97,   110,   111,   112,   113,     0,
     132,     0,   116,   133,   134,   135,   136,   137,   138,   139,
     144,   145,   154,   155,   156,   165,   166,   167,     0,     0,
       0,   168,   174,   175,   207
};

static const yytype_int16 yycheck[] =
{
      68,     3,     4,     5,     6,     7,     8,    30,    31,    32,
      41,    84,    90,    91,    45,    46,    89,    40,    41,    42,
      43,    44,    30,    31,    32,    27,    28,    29,    77,    30,
      31,    32,    40,    41,    42,    43,    44,    37,    38,    40,
      30,    31,    32,   111,    40,    84,    85,    43,    41,    45,
      40,    40,    45,    46,    43,    84,    45,    84,    77,    84,
      89,    82,    89,    82,    89,   133,    84,    84,    84,    84,
      77,    89,    89,    89,    89,    82,     0,    40,    84,    84,
      43,    79,    40,    89,    89,    43,    58,    59,    60,    37,
      38,    39,    34,    35,    36,    40,    37,    38,    39,    34,
      35,    36,    84,    85,    84,    85,    90,    91,    84,    85,
      77,    92,    93,    84,    85,    94,    95,    37,    38,    45,
      90,    91,    84,    85,    84,    85,    90,    91,    84,    85,
      77,    92,    93,    84,    85,    94,    95,    77,    77,    77,
      77,    77,    40,    77,    77,    77,    77,    77,    -1,    -1,
      79,    79,    79,    -1,    79,    -1,    79,    79,    79,    -1,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    -1,
      79,    -1,    82,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    -1,    -1,
      -1,    82,    82,    82,    82
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    27,    28,    29,
     100,   101,    77,   102,    77,   104,    77,   105,    77,   106,
      77,   107,    77,   109,   111,    77,   108,    77,   110,     0,
      30,    31,    32,    40,    77,    40,    30,    31,    32,    40,
      41,    42,    43,    44,    77,    40,    43,    77,    45,    41,
      45,    46,    77,    40,    40,    43,    45,    77,    79,    79,
      79,    79,    30,    31,    32,    40,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    30,    31,    32,    40,    41,
      42,    43,    44,    79,    79,    40,    43,    79,    79,    79,
      79,    41,    45,    46,    79,    79,    79,    79,    40,    43,
      45,    82,    58,    59,    60,   103,    37,    38,    84,    89,
      79,    79,    79,    79,    84,    89,    82,   103,    37,    38,
      39,    84,    89,    34,    35,    36,    90,    91,    84,    85,
      77,    82,    79,    79,    79,    79,    79,    79,    79,    79,
      84,    89,    84,    85,    79,    79,    84,    85,    90,    91,
      84,    85,    92,    93,    79,    79,    79,    84,    89,    84,
      89,    94,    95,    84,    85,    79,    79,    79,    82,   103,
      37,    38,    84,    89,    82,    82,   103,    37,    38,    39,
      84,    89,    34,    35,    36,    90,    91,    84,    85,    77,
      82,    84,    89,    84,    85,    90,    91,    84,    85,    92,
      93,    84,    89,    94,    95,    84,    85,    82
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    99,   100,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   103,   103,   103,   104,   104,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   106,   106,   106,   106,   106,   106,   106,   106,
     107,   107,   108,   108,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   111
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     0,     5,     4,     5,     4,     5,     5,     4,
       4,     5,     5,     4,     4,     1,     1,     1,     4,     4,
       5,     4,     5,     5,     5,     4,     4,     4,     5,     4,
       5,     4,     5,     5,     5,     4,     4,     4,     5,     4,
       5,     4,     5,     4,     5,     4,     5,     4,     5,     4,
       6,     5,     5,     4,     5,     4,     5,     4,     5,     4,
       4,     4,     4,     4,     5,     4,     5,     4,     5,     4,
       5,     4,     5,     4,     5,     4,     5,     4,     5,     4,
       5,     4,     5,     4,     5,     4,     5,     4,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 254 "parser.y" /* yacc.c:1646  */
    { }
#line 1663 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 258 "parser.y" /* yacc.c:1646  */
    {(yyvsp[0].mkdisk)->ejecutar();}
#line 1669 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 259 "parser.y" /* yacc.c:1646  */
    {(yyvsp[0].rmdisk)->ejecutar();}
#line 1675 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 260 "parser.y" /* yacc.c:1646  */
    {(yyvsp[0].fdisk)->ejecutar();}
#line 1681 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 261 "parser.y" /* yacc.c:1646  */
    {(yyvsp[0].mount)->ejecutar();}
#line 1687 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 262 "parser.y" /* yacc.c:1646  */
    {(yyvsp[0].umount)->ejecutar();}
#line 1693 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 263 "parser.y" /* yacc.c:1646  */
    {(yyvsp[0].mkfs)->ejecutar();}
#line 1699 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 264 "parser.y" /* yacc.c:1646  */
    {(yyvsp[0].exec)->ejecutar();}
#line 1705 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 265 "parser.y" /* yacc.c:1646  */
    {(yyvsp[0].rep)->ejecutar();}
#line 1711 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 267 "parser.y" /* yacc.c:1646  */
    {
    obj_pause *disco = new obj_pause();
    disco->ejecutar();
}
#line 1720 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 296 "parser.y" /* yacc.c:1646  */
    {


//$2->ejecutar();
//$2->mostrardatos($2);//ejecuto el metodo "mostrardatos" del objeto retornado en COMANDOMKDISK
//printf("estoy en lexpa primera produccion");
}
#line 1732 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 308 "parser.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[0].TEXT)); (yyvsp[-4].mkdisk)->size=tam;  (yyval.mkdisk)=(yyvsp[-4].mkdisk);}
#line 1738 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 309 "parser.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[0].TEXT)); obj_mkdisk *disco=new obj_mkdisk(); disco->size=tam; (yyval.mkdisk)=disco;}
#line 1744 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 311 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].mkdisk)->f =(yyvsp[0].numero); (yyval.mkdisk)=(yyvsp[-4].mkdisk);}
#line 1750 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 312 "parser.y" /* yacc.c:1646  */
    {int ajuste=(yyvsp[0].numero); obj_mkdisk *disco=new obj_mkdisk(); disco->f=ajuste;  (yyval.mkdisk)=disco;}
#line 1756 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 314 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].mkdisk)->path = formatear((yyvsp[0].TEXT));(yyval.mkdisk)=(yyvsp[-4].mkdisk);}
#line 1762 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 315 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].mkdisk)->path = formatear((yyvsp[0].TEXT)); (yyval.mkdisk)=(yyvsp[-4].mkdisk);}
#line 1768 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 317 "parser.y" /* yacc.c:1646  */
    {obj_mkdisk *disco=new obj_mkdisk(); disco->path=formatear((yyvsp[0].TEXT));  (yyval.mkdisk)=disco;}
#line 1774 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 318 "parser.y" /* yacc.c:1646  */
    {obj_mkdisk *disco=new obj_mkdisk(); disco->path=formatear((yyvsp[0].TEXT));  (yyval.mkdisk)=disco;}
#line 1780 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 321 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].mkdisk)->u = (yyvsp[0].TEXT); (yyval.mkdisk)=(yyvsp[-4].mkdisk);}
#line 1786 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 322 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].mkdisk)->u = (yyvsp[0].TEXT); (yyval.mkdisk)=(yyvsp[-4].mkdisk);}
#line 1792 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 324 "parser.y" /* yacc.c:1646  */
    {obj_mkdisk *disco=new obj_mkdisk(); disco->u=(yyvsp[0].TEXT);  (yyval.mkdisk)=disco;}
#line 1798 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 325 "parser.y" /* yacc.c:1646  */
    {obj_mkdisk *disco=new obj_mkdisk(); disco->u=(yyvsp[0].TEXT);  (yyval.mkdisk)=disco;}
#line 1804 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 330 "parser.y" /* yacc.c:1646  */
    {int tipo=0; (yyval.numero)=tipo;}
#line 1810 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 331 "parser.y" /* yacc.c:1646  */
    {int tipo=1; (yyval.numero)=tipo;}
#line 1816 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 332 "parser.y" /* yacc.c:1646  */
    {int tipo=2; (yyval.numero)=tipo;}
#line 1822 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 344 "parser.y" /* yacc.c:1646  */
    {obj_rmdisk *disco=new obj_rmdisk();disco->path=formatear((yyvsp[0].TEXT)); (yyval.rmdisk)=disco;}
#line 1828 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 345 "parser.y" /* yacc.c:1646  */
    {obj_rmdisk *disco=new obj_rmdisk();disco->path=formatear((yyvsp[0].TEXT)); (yyval.rmdisk)=disco;}
#line 1834 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 349 "parser.y" /* yacc.c:1646  */
    {int tam =atoi((yyvsp[0].TEXT)); (yyvsp[-4].fdisk)->size = tam;(yyval.fdisk)=(yyvsp[-4].fdisk);}
#line 1840 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 350 "parser.y" /* yacc.c:1646  */
    {obj_fdisk *disco=new obj_fdisk(); int tam =atoi((yyvsp[0].TEXT)); disco->size = tam; (yyval.fdisk) = disco;}
#line 1846 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 352 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].fdisk)->u = 0; (yyval.fdisk) = (yyvsp[-4].fdisk);}
#line 1852 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 353 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].fdisk)->u = 1; (yyval.fdisk) = (yyvsp[-4].fdisk);}
#line 1858 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 354 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].fdisk)->u = 2; (yyval.fdisk) = (yyvsp[-4].fdisk);}
#line 1864 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 356 "parser.y" /* yacc.c:1646  */
    {obj_fdisk *disco=new obj_fdisk();disco->u = 0;(yyval.fdisk)=disco;}
#line 1870 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 357 "parser.y" /* yacc.c:1646  */
    {obj_fdisk *disco=new obj_fdisk();disco->u = 1;(yyval.fdisk)=disco;}
#line 1876 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 358 "parser.y" /* yacc.c:1646  */
    {obj_fdisk *disco=new obj_fdisk();disco->u = 2;(yyval.fdisk)=disco;}
#line 1882 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 360 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].fdisk)->path = formatear((yyvsp[0].TEXT)); (yyval.fdisk) = (yyvsp[-4].fdisk);}
#line 1888 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 361 "parser.y" /* yacc.c:1646  */
    {obj_fdisk *disco=new obj_fdisk(); disco->path =formatear((yyvsp[0].TEXT));(yyval.fdisk) = disco;}
#line 1894 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 363 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].fdisk)->path = formatear((yyvsp[0].TEXT)); (yyval.fdisk) = (yyvsp[-4].fdisk);}
#line 1900 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 364 "parser.y" /* yacc.c:1646  */
    {obj_fdisk *disco=new obj_fdisk(); disco->path =formatear((yyvsp[0].TEXT));(yyval.fdisk) = disco;}
#line 1906 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 367 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].fdisk)->type = 0; (yyval.fdisk) = (yyvsp[-4].fdisk);}
#line 1912 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 368 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].fdisk)->type = 1; (yyval.fdisk) = (yyvsp[-4].fdisk);}
#line 1918 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 369 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].fdisk)->type = 2; (yyval.fdisk) = (yyvsp[-4].fdisk);}
#line 1924 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 371 "parser.y" /* yacc.c:1646  */
    {obj_fdisk *disco=new obj_fdisk(); disco->type=0; (yyval.fdisk) =disco;}
#line 1930 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 372 "parser.y" /* yacc.c:1646  */
    {obj_fdisk *disco=new obj_fdisk(); disco->type=1; (yyval.fdisk) =disco;}
#line 1936 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 373 "parser.y" /* yacc.c:1646  */
    {obj_fdisk *disco=new obj_fdisk(); disco->type=2; (yyval.fdisk) =disco;}
#line 1942 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 376 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].fdisk)->f = (yyvsp[0].numero); (yyval.fdisk) = (yyvsp[-4].fdisk);}
#line 1948 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 377 "parser.y" /* yacc.c:1646  */
    {obj_fdisk *disco=new obj_fdisk(); disco->f =(yyvsp[0].numero);(yyval.fdisk)=disco;}
#line 1954 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 379 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].fdisk)->eliminar = 1;(yyvsp[-4].fdisk)->tipo_eliminar =0;(yyval.fdisk)=(yyvsp[-4].fdisk);}
#line 1960 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 380 "parser.y" /* yacc.c:1646  */
    {obj_fdisk *disco=new obj_fdisk(); disco->eliminar = 1;disco->tipo_eliminar =0; (yyval.fdisk)=disco;}
#line 1966 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 382 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].fdisk)->eliminar = 1;(yyvsp[-4].fdisk)->tipo_eliminar =1;(yyval.fdisk)=(yyvsp[-4].fdisk);}
#line 1972 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 383 "parser.y" /* yacc.c:1646  */
    {obj_fdisk *disco=new obj_fdisk(); disco->eliminar = 1;disco->tipo_eliminar =1; (yyval.fdisk)=disco;}
#line 1978 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 386 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].fdisk)->name = formatear((yyvsp[0].TEXT)); (yyval.fdisk)=(yyvsp[-4].fdisk);}
#line 1984 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 387 "parser.y" /* yacc.c:1646  */
    {obj_fdisk *disco=new obj_fdisk(); disco->name = formatear((yyvsp[0].TEXT)); (yyval.fdisk)=disco;}
#line 1990 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 389 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].fdisk)->name = formatear((yyvsp[0].TEXT)); (yyval.fdisk)=(yyvsp[-4].fdisk);}
#line 1996 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 390 "parser.y" /* yacc.c:1646  */
    {obj_fdisk *disco=new obj_fdisk(); disco->name = formatear((yyvsp[0].TEXT)); (yyval.fdisk)=disco;}
#line 2002 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 392 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].fdisk)->size = atoi((yyvsp[0].TEXT));(yyvsp[-4].fdisk)->add = 1; (yyval.fdisk)=(yyvsp[-4].fdisk);}
#line 2008 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 393 "parser.y" /* yacc.c:1646  */
    {obj_fdisk *disco=new obj_fdisk(); disco->size = atoi((yyvsp[0].TEXT));disco->add = 1; (yyval.fdisk)=disco;}
#line 2014 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 395 "parser.y" /* yacc.c:1646  */
    {int num =atoi((yyvsp[0].TEXT)); num = num*-1; (yyvsp[-5].fdisk)->size = num;(yyvsp[-5].fdisk)->add = 1; (yyval.fdisk)=(yyvsp[-5].fdisk);}
#line 2020 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 396 "parser.y" /* yacc.c:1646  */
    {obj_fdisk *disco=new obj_fdisk();int num =atoi((yyvsp[0].TEXT)); num = num*-1; disco->size = num; disco->add = 1; (yyval.fdisk)=disco;}
#line 2026 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 417 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].mount)->path = formatear((yyvsp[0].TEXT)); (yyval.mount) = (yyvsp[-4].mount);}
#line 2032 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 418 "parser.y" /* yacc.c:1646  */
    {obj_mount *disco=new obj_mount(); disco->path = formatear((yyvsp[0].TEXT)); (yyval.mount) = disco;}
#line 2038 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 420 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].mount)->path = formatear((yyvsp[0].TEXT)); (yyval.mount) = (yyvsp[-4].mount);}
#line 2044 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 421 "parser.y" /* yacc.c:1646  */
    {obj_mount *disco=new obj_mount(); disco->path = formatear((yyvsp[0].TEXT)); (yyval.mount) = disco;}
#line 2050 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 423 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].mount)->name = formatear((yyvsp[0].TEXT)); (yyval.mount) = (yyvsp[-4].mount);}
#line 2056 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 424 "parser.y" /* yacc.c:1646  */
    {obj_mount *disco=new obj_mount(); disco->name = formatear((yyvsp[0].TEXT)); (yyval.mount) = disco;}
#line 2062 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 426 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].mount)->name = formatear((yyvsp[0].TEXT)); (yyval.mount) = (yyvsp[-4].mount);}
#line 2068 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 427 "parser.y" /* yacc.c:1646  */
    {obj_mount *disco=new obj_mount(); disco->name = formatear((yyvsp[0].TEXT)); (yyval.mount) = disco;}
#line 2074 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 432 "parser.y" /* yacc.c:1646  */
    {obj_umount *disco=new obj_umount(); disco->id=formatear((yyvsp[0].TEXT)); (yyval.umount) = disco;}
#line 2080 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 433 "parser.y" /* yacc.c:1646  */
    {obj_umount *disco=new obj_umount(); disco->id=formatear((yyvsp[0].TEXT)); (yyval.umount) = disco;}
#line 2086 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 437 "parser.y" /* yacc.c:1646  */
    {obj_exec *disco=new obj_exec(); disco->path=formatear((yyvsp[0].TEXT)); (yyval.exec)=disco;}
#line 2092 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 438 "parser.y" /* yacc.c:1646  */
    {obj_exec *disco=new obj_exec(); disco->path=formatear((yyvsp[0].TEXT)); (yyval.exec)=disco;}
#line 2098 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 444 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].mkfs)->id = formatear((yyvsp[0].TEXT)); (yyval.mkfs) = (yyvsp[-4].mkfs);}
#line 2104 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 445 "parser.y" /* yacc.c:1646  */
    {obj_mkfs *disco = new obj_mkfs(); disco->id = formatear((yyvsp[0].TEXT)); (yyval.mkfs) = disco;}
#line 2110 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 447 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].mkfs)->id = formatear((yyvsp[0].TEXT)); (yyval.mkfs) = (yyvsp[-4].mkfs);}
#line 2116 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 448 "parser.y" /* yacc.c:1646  */
    {obj_mkfs *disco = new obj_mkfs(); disco->id = formatear((yyvsp[0].TEXT)); (yyval.mkfs) = disco;}
#line 2122 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 450 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].mkfs)->type = 0; (yyval.mkfs) = (yyvsp[-4].mkfs);}
#line 2128 "parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 451 "parser.y" /* yacc.c:1646  */
    {obj_mkfs *disco = new obj_mkfs(); disco->type = 0; (yyval.mkfs) = disco;}
#line 2134 "parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 453 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].mkfs)->type = 1; (yyval.mkfs) = (yyvsp[-4].mkfs);}
#line 2140 "parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 454 "parser.y" /* yacc.c:1646  */
    {obj_mkfs *disco = new obj_mkfs(); disco->type = 1; (yyval.mkfs) = disco;}
#line 2146 "parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 456 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].mkfs)->fs = 2; (yyval.mkfs) = (yyvsp[-4].mkfs);}
#line 2152 "parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 457 "parser.y" /* yacc.c:1646  */
    {obj_mkfs *disco = new obj_mkfs(); disco->fs = 2; (yyval.mkfs) = disco;}
#line 2158 "parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 459 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].mkfs)->fs = 3; (yyval.mkfs) = (yyvsp[-4].mkfs);}
#line 2164 "parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 460 "parser.y" /* yacc.c:1646  */
    {obj_mkfs *disco = new obj_mkfs(); disco->fs = 3; (yyval.mkfs) = disco;}
#line 2170 "parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 468 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].rep)->name = "mbr"; (yyval.rep) = (yyvsp[-4].rep);}
#line 2176 "parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 469 "parser.y" /* yacc.c:1646  */
    {obj_rep *disco = new obj_rep();disco->name = "mbr"; (yyval.rep) = disco;}
#line 2182 "parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 471 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].rep)->name = "disk"; (yyval.rep) = (yyvsp[-4].rep);}
#line 2188 "parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 472 "parser.y" /* yacc.c:1646  */
    {obj_rep *disco = new obj_rep();disco->name = "disk"; (yyval.rep) = disco;}
#line 2194 "parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 475 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].rep)->path = formatear((yyvsp[0].TEXT)); (yyval.rep) = (yyvsp[-4].rep);}
#line 2200 "parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 476 "parser.y" /* yacc.c:1646  */
    {obj_rep *disco = new obj_rep();disco->path = formatear((yyvsp[0].TEXT)); (yyval.rep) = disco;}
#line 2206 "parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 478 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].rep)->path = formatear((yyvsp[0].TEXT)); (yyval.rep) = (yyvsp[-4].rep);}
#line 2212 "parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 479 "parser.y" /* yacc.c:1646  */
    {obj_rep *disco = new obj_rep();disco->path = formatear((yyvsp[0].TEXT)); (yyval.rep) = disco;}
#line 2218 "parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 481 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].rep)->id = formatear((yyvsp[0].TEXT)); (yyval.rep) = (yyvsp[-4].rep);}
#line 2224 "parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 482 "parser.y" /* yacc.c:1646  */
    {obj_rep *disco = new obj_rep();disco->id = formatear((yyvsp[0].TEXT)); (yyval.rep) = disco;}
#line 2230 "parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 484 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].rep)->id = formatear((yyvsp[0].TEXT)); (yyval.rep) = (yyvsp[-4].rep);}
#line 2236 "parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 485 "parser.y" /* yacc.c:1646  */
    {obj_rep *disco = new obj_rep();disco->id = formatear((yyvsp[0].TEXT)); (yyval.rep) = disco;}
#line 2242 "parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 496 "parser.y" /* yacc.c:1646  */
    {obj_pause *disco = new obj_pause(); (yyval.pause) = disco;}
#line 2248 "parser.cpp" /* yacc.c:1646  */
    break;


#line 2252 "parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
