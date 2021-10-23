QT += core
QT += sql
QT -= gui
QT -= location
QT += network
QT += websockets

CONFIG += silent
CONFIG += c++17
CONFIG += silent

include($$PWD/../../src/lib/lib-test.pri)
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
