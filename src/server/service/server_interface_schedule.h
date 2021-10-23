#pragma once

#include "./server_interface.h"

namespace ServerService {

    class InterfaceSchedule : public ServerInterface
    {
        Q_OBJECT
        QRPC_DECLARE_ROUTE(InterfaceSchedule,"v1/schedule")
    public:
        Q_INVOKABLE explicit InterfaceSchedule(QObject *parent=nullptr);
        Q_INVOKABLE ~InterfaceSchedule();

        Q_INVOKABLE QVariant create();
        Q_INVOKABLE QVariant insert();
        Q_INVOKABLE QVariant send();
        Q_INVOKABLE QVariant cancel();
        Q_INVOKABLE QVariant stat();
        Q_INVOKABLE QVariant stat_task();
        Q_INVOKABLE QVariant stats();
    };

    QRPC_CONTROLLER_AUTO_REGISTER(InterfaceSchedule)

}
