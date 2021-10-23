include($$PWD/../3rdparty/simplemail/simplemail.pri)
include($$PWD/../3rdparty/qstm/qstm.pri)
include($$PWD/../3rdparty/qorm/qorm.pri)
include($$PWD/../3rdparty/qrpc/qrpc.pri)
include($$PWD/../3rdparty/qapplicationrunnable/qapplicationrunnable.pri)
include($$PWD/model/server.model.pri)

INCLUDEPATH+=$$PWD

HEADERS += \
    $$PWD/server_base_controller.h \
    $$PWD/server_base_dao.h \
    $$PWD/server_controller_schedule.h


SOURCES += \
    $$PWD/server_base_controller.cpp \
    $$PWD/server_base_dao.cpp \
    $$PWD/server_controller_schedule.cpp
