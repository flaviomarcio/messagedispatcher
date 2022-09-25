#pragma once

#include "./server_interface.h"

namespace ServerService {

class InterfaceSchedule : public ServerInterface
{
    Q_OBJECT
    Q_ANNOTATION(InterfaceSchedule, {apiBasePath(QStringLiteral("v1/schedule"))})
public:
    Q_INVOKABLE explicit InterfaceSchedule(QObject *parent=nullptr);

    Q_ANNOTATION(create, nl({opPost}))
    Q_INVOKABLE QVariant create();

    Q_ANNOTATION(insert, nl({opPost}))
    Q_INVOKABLE QVariant insert();

    Q_ANNOTATION(send, nl({opPost}))
    Q_INVOKABLE QVariant send();

    Q_ANNOTATION(cancel, nl({opPost}))
    Q_INVOKABLE QVariant cancel();

    Q_ANNOTATION(stat, nl({opPost}))
    Q_INVOKABLE QVariant stat();

    Q_ANNOTATION(stat_task, nl({opPost}))
    Q_INVOKABLE QVariant stat_task();

    Q_ANNOTATION(stats, nl({opPost}))
    Q_INVOKABLE QVariant stats();
};

QRPC_CONTROLLER_AUTO_REGISTER(InterfaceSchedule)

}
