include($$PWD/../3rdparty/simplemail/simplemail.pri)
include($$PWD/../3rdparty/qtreforce-sdk/qtreforce-sdk-test.pri)

include($$PWD/model/server.model.pri)

INCLUDEPATH+=$$PWD

HEADERS += \
    $$PWD/server_base_controller.h \
    $$PWD/server_base_dao.h \
    $$PWD/server_dao_schedule.h \
    $$PWD/server_controller_schedule.h


SOURCES += \
    $$PWD/server_base_controller.cpp \
    $$PWD/server_base_dao.cpp \
    $$PWD/server_dao_schedule.cpp \
    $$PWD/server_controller_schedule.cpp
