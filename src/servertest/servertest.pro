QT += testlib

CONFIG += testcase
CONFIG += console
CONFIG -= debug_and_release

TEMPLATE = app
TARGET = MessageServerTest

LIBS += -lgmock
LIBS += -lgtest

include($$PWD/../server/server-test.pri)

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/tests/app_test_request_v1.cpp

