HEADERS += \
    $$PWD/server_dispatcher_pool.h \
    $$PWD/server_dispatcher_service.h \
    $$PWD/server_dispatcher_service_fake.h \
    $$PWD/server_dispatcher_service_email.h \
    $$PWD/server_dispatcher_service_push.h \
    $$PWD/server_dispatcher_service_sms.h \
    $$PWD/server_dispatcher_service_telegram.h \
    $$PWD/server_dispatcher_service_whatsapp.h \
    $$PWD/server_model.h \
    $$PWD/server_provider.h \
    $$PWD/server_publisher.h \
    $$PWD/server_publisher_tokens.h \
    $$PWD/server_publisher_provider.h \
    $$PWD/server_schedule.h \
    $$PWD/server_schedule_task.h \
    $$PWD/server_types.h

SOURCES += \
    $$PWD/server_dispatcher_pool.cpp \
    $$PWD/server_dispatcher_service.cpp \
    $$PWD/server_dispatcher_service_fake.cpp \
    $$PWD/server_dispatcher_service_email.cpp \
    $$PWD/server_dispatcher_service_push.cpp \
    $$PWD/server_dispatcher_service_sms.cpp \
    $$PWD/server_dispatcher_service_telegram.cpp \
    $$PWD/server_dispatcher_service_whatsapp.cpp \

INCLUDEPATH += $$PWD
