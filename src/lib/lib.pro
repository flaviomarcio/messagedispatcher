#!include(../../../infrastructure.pri ) {
#    error("infrastructure.pri not exists!")
#}

QT += core
QT += sql
QT += location

TARGET = itHappensSecurityLib
TEMPLATE = lib
CONFIG += silent

INCLUDEPATH += ../infrastructure

LIBS += -L$$OUT_PWD/../../../../../core                      -linfraCore
LIBS += -L$$OUT_PWD/../../../../../mvc                       -linfraMVC

include($$PWD/itsecuritylib.pri)
