#include "obj_exec.h"

obj_exec::obj_exec()
{
    this->path = "";
    this->nombreArchivo = "/dsmount.data";
    this->currentDir = "";
}


int obj_exec::ejecutar(){
    fstream newfile;
    if (this->path == ""){
        cout<<"Error, no se ingreso una ruta valida."<<endl;
    }
    newfile.open(this->path,ios::in);
    if (newfile.is_open()){
       string lista;
       while(getline(newfile, lista)){
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
       }
       newfile.close();
    }

    if( remove(this->currentDir.c_str()) != 0 ){
        printf("Error, el archivo no existe.");
        return -1;
    }

    return 0;
}



int obj_exec::getCurrentDir(){
    char buffer[PATH_MAX];
    if (getcwd(buffer, sizeof(buffer)) != NULL) {
        printf("El directorio actual es: %s\n", buffer);
        for (int i=0; i< sizeof(buffer);i++){
            if (i==88){
                //Nada
                cout<<endl;
            }
            if (buffer[i]==NULL){
                break;
            }
            this->currentDir+= buffer[i];
        }
        this->currentDir+= this->nombreArchivo;
        cout<<this->currentDir<<endl;
    } else {
        perror("Error, el directorio no existe.");
        return -1;
    }
    return 0;
}
