#include <QCoreApplication>
#include "iostream"
#include "string"
#include <QString>
#include <parser.h>  // Nuestro parser
#include <scanner.h>  // Nuestro scanner
#include <QTextStream>
using namespace std;
extern int yyparse(); //
//static QList<discosmontados> discosenmemoria
int p;
extern int linea; // Linea del token
extern int columna; // Columna de los tokens
extern int yylineno;
int main(int argc, char *argv[])
{



    string lista ="";
    for (int i=1; i < argc; i++){
        lista += argv[i];
        lista += " ";

    }
    string p="------------------------------Comando ingresado------------------------------\n";
    //QTextStream qtin(stdin);
    QString line;

    line = QString::fromStdString(lista);
    if(line!="salir"){
        if(line.isEmpty()==false){
            YY_BUFFER_STATE buffer = yy_scan_string(line.toUtf8().constData());


            linea = 0;
            columna = 0;
            yylineno = 0;

            if(yyparse()==0) // Si nos da un número negativo, signifca error.
            {
                printf("\n\Comando ejecutado correctamente\n\n");

            }else {

                printf("\n\nhay errores\n\n");
            }

        }
    }


    return 0;
}


