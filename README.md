# Manual de usuario

#### Comandos funcionales
* [Exec](#Exec)     
* [Fdisk](#Fdisk)     
* [Mkdisk](#Mkdisk)     
* [Mount](#Mount)     
* [Mkfs](#Mkfs)     
* [Rep](#Rep)     
* [Rmdisk](#Rmdisk)     
* [Umount](#Umount)     


<a name="Exec"/>

### Comando Exec

*******
**Descripcion**

*El programa podrá ejecutar scripts con el comando exec. Debe mostrar el contenido de la línea que está leyendo y su resultado.*

**Parámetros**

* Path: *Especifica el nombre del script que se va a ejecutar.*

**Uso**

exec -path= rutaDelArchivo

*******
<a name="Fdisk"/>

### Comando Fdisk
*******
**Descripcion**

*Este comando administra las particiones en el archivo que representa al disco duro, es decir crear, elimina y modifica particiones primarias, extendidas y lógicas.*

**Parámetros**

* Path: *Será la ruta en la que se encuentra el disco en el que se creará la partición.*
* size: *Este parámetro recibirá un número que indicará el tamaño de la partición a crear.*
* u: *Este parámetro recibirá una letra que indicará las unidades que utilizará el parámetro size. B -> bites; K -> Kilobytes; M -> Megabytes.*
* type: *Indicará que tipo de partición se creará. Si no se coloca, la partición por defecto a crear será una primaria. P -> Primaria; E -> Extendida; L -> Lógica.*
* f: *Indicará el ajuste que utilizará la partición para asignar espacio. BF -> Best Fit; WF -> Worst Fit; FF -> First Fit. Por defecto tomará el peor ajuste.*
* delete: *Este parámetro indica que se eliminará una partición.*
* add: *Este parámetro se utilizará para agregar o quitar espacio de la partición.*
* name: *Indicará el nombre de la partición.*

**Uso**

* *Crear Partición*

fdisk –Size=tamañoDisco –path=rutaDisco –name=nombreParticion 

* *Eliminar partición*

fdisk delete=tipoEliminacion -name= nombreParticion -path=rutaDisco

* *Agregar espacio a una partición*

fdisk add=tamaño u=unidad -path=rutaDisco -name=nombreParticion


*******

<a name="Mkdisk"/>

### Comando Mkdisk
*******
**Descripcion**

*Este comando creará un archivo binario que simulará un disco duro, estos archivos binarios tendrán la extensión dk y su contenido al inicio será 0.*

**Parámetros**


* size: *Este parámetro recibirá un número que indicará el tamaño del disco a crear.*
* f: *Indicará el ajuste que utilizará el disco para crear particiones. BF -> Best Fit; WF -> Worst Fit; FF -> First Fit. Por defecto tomará el peor ajuste.*
* u: *Este parámetro recibirá una letra que indicará las unidades que utilizará el parámetro size. K -> Kilobytes; M -> Megabytes.*
* Path: *Este parámetro será la ruta en el que se creará el archivo que representará el disco duro.*


**Uso**

* *Crear Disco*

Mkdisk -Size=tamañoDisco –u=unidadDisco -path=rutaDisco


*******
<a name="Mount"/>

### Comando Mount
*******
**Descripcion**

*Este comando montará una partición del disco en el sistema e imprimira en consola un resumen de todas las particiones montadas actualmente.*

**Parámetros**

* Path: *Este parámetro será la ruta en la que se encuentra el disco que se montará en el sistema.*
* name: *Indica el nombre de la partición a cargar.*

**Uso**

* *Montar una partición*

mount -path=rutaDisco -name=nombreParticion

*******
<a name="Mkfs"/>

### Comando Mkfs

*******
**Descripcion**

*Este comando realiza un formateo completo de la partición, se formateará como ext2 por defecto si en caso el parámetro fs no está definido. También creará un archivo en la raíz llamado users.txt que tendrá los usuarios y contraseñas del sistema de archivos.*

**Parámetros**

* id: *Indicará el id que se generó con el comando mount.*
* type: *Indicará que tipo de formateo se realizará. Fast o Full serán las opciones que se podrán utilizar para el formateo.*
* fs: *Indica el sistema de archivos a formatear. 2fs para ext2 y 3fs para ext3.*

**Uso**

* *Formatear una partición*

mkfs -type=tipoFormateo -id=particionMontada

*******
<a name="Rep"/>

### Comando Rep

*******
**Descripcion**

*Recibirá el nombre del reporte que se desea y lo generará con graphviz en una carpeta existente.*

**Parámetros**

* name: *Nombre del reporte a generar. Las opciones funcionales son: MBR y Disk.*
* path: *Indica una carpeta y el nombre que tendrá el reporte.*
* id: *Indica el id de la partición que se utilizará.*
* ruta: *Funcionará para el reporte file y ls.*
* root: *Para uso exclusivo del reporte Tree.*

**Uso**

* *Crear un reporte*

rep –id=particionMontada -Path=rutaReporte -name=nombreTipoReporte

*******
<a name="Rmdisk"/>

### Comando Rmdisk

*******
**Descripcion**

*Este parámetro elimina un archivo que representa a un disco duro mostrando un mensaje de confirmación para eliminar.*

**Parámetros**

* path: *Este parámetro será la ruta en el que se eliminará el archivo que representará el disco duro.*

**Uso**

* *Eliminar un disco*

rmDisk -path=direccionDisco

*******
<a name="Umount"/>

### Comando Umount

*******
**Descripcion**

*Este parámetro elimina un archivo que representa a un disco duro mostrando un mensaje de confirmación para eliminar.*

**Parámetros**

* id: *Especifica el id de la partición que se desmontará.*

**Uso**

* *Desmontar una partición*

umount -id=particionMontada

*******





