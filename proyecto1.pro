QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        estructuras.cpp \
        main.cpp \
        obj_cat.cpp \
        obj_chgrp.cpp \
        obj_chmod.cpp \
        obj_chown.cpp \
        obj_cp.cpp \
        obj_edit.cpp \
        obj_exec.cpp \
        obj_fdisk.cpp \
        obj_find.cpp \
        obj_login.cpp \
        obj_logout.cpp \
        obj_loss.cpp \
        obj_mkdir.cpp \
        obj_mkdisk.cpp \
        obj_mkfs.cpp \
        obj_mkgrp.cpp \
        obj_mkusr.cpp \
        obj_mount.cpp \
        obj_mv.cpp \
        obj_pause.cpp \
        obj_recovery.cpp \
        obj_ren.cpp \
        obj_rep.cpp \
        obj_rm.cpp \
        obj_rmdisk.cpp \
        obj_rmgrp.cpp \
        obj_rmusr.cpp \
        obj_touch.cpp \
        obj_umount.cpp \
        parser.cpp \
        scanner.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    lexico.l \
    parser.y

HEADERS += \
    estructuras.h \
    obj_cat.h \
    obj_chgrp.h \
    obj_chmod.h \
    obj_chown.h \
    obj_cp.h \
    obj_edit.h \
    obj_exec.h \
    obj_fdisk.h \
    obj_find.h \
    obj_login.h \
    obj_logout.h \
    obj_loss.h \
    obj_mkdir.h \
    obj_mkdisk.h \
    obj_mkfs.h \
    obj_mkgrp.h \
    obj_mkusr.h \
    obj_mount.h \
    obj_mv.h \
    obj_pause.h \
    obj_recovery.h \
    obj_ren.h \
    obj_rep.h \
    obj_rm.h \
    obj_rmdisk.h \
    obj_rmgrp.h \
    obj_rmusr.h \
    obj_touch.h \
    obj_umount.h \
    parser.h \
    scanner.h
