#pragma once

#include "./server_interface.h"

namespace ServerService {

    class InterfaceMessage : public ServerInterface
    {
        Q_OBJECT
        QRPC_DECLARE_ROUTE(InterfaceMessage,qsl("v1/message"))
    public:
        Q_INVOKABLE explicit InterfaceMessage(QObject *parent=nullptr);
        Q_INVOKABLE ~InterfaceMessage();

        Q_INVOKABLE QVariant send();
        Q_INVOKABLE QVariant counters();
    };

    QRPC_CONTROLLER_AUTO_REGISTER(InterfaceMessage)

}
