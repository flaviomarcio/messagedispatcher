QTREFORCE_NO_QRMK=true
DEFINES+=QTREFORCE_NO_QRMK
CONFIG+=QTREFORCE_NO_QRMK

QTREFORCE_NO_QMFE=true
DEFINES+=QTREFORCE_NO_QMFE
CONFIG+=QTREFORCE_NO_QMFE

QTREFORCE_NO_GUI=true
DEFINES+=QTREFORCE_NO_GUI
CONFIG+=QTREFORCE_NO_GUI

QTREFORCE_NO_QJSONWEBTOKEN=true
DEFINES+=QTREFORCE_NO_QJSONWEBTOKEN
CONFIG+=QTREFORCE_NO_QJSONWEBTOKEN

QTREFORCE_NO_QTOKENUTIL=true
DEFINES+=QTREFORCE_NO_QTOKENUTIL
CONFIG+=QTREFORCE_NO_QTOKENUTIL

QTREFORCE_NO_QCROSSCACHE=true
DEFINES+=QTREFORCE_NO_QCROSSCACHE
CONFIG+=QTREFORCE_NO_QCROSSCACHE

QTREFORCE_NO_QAPIDOC=true
DEFINES+=QTREFORCE_NO_QAPIDOC
CONFIG+=QTREFORCE_NO_QAPIDOC

QT += core
QT += sql
QT -= gui
QT -= location
QT += network
QT += websockets

CONFIG += silent
CONFIG += c++17
CONFIG += silent

include($$PWD/../../src/lib/lib.pri)
include($$PWD/service/service.pri)
include($$PWD/service/service_notify.pri)

INCLUDEPATH += $$PWD

RESOURCES+= \
    $$PWD/app.qrc

DISTFILES += \
    $$PWD/../../database/constraints.sql \
    $$PWD/../../database/initdata.sql \
    $$PWD/../../database/fakedata.sql \
    $$PWD/../../database/tables.sql \
    $$PWD/../../database/indexes.sql \
    $$PWD/others/curl_script
