#pragma once

#include "./server_interface.h"

namespace ServerService {

    class InterfaceDispatcher : public ServerInterface
    {
        Q_OBJECT
        QRPC_DECLARE_ROUTE(InterfaceDispatcher,"v1/dispatcher")
    public:
        Q_INVOKABLE explicit InterfaceDispatcher(QObject *parent=nullptr);
        Q_INVOKABLE ~InterfaceDispatcher();

        Q_INVOKABLE QVariant send();
    };

    QRPC_CONTROLLER_AUTO_REGISTER(InterfaceDispatcher)

}
