#pragma once

#include "./server_interface.h"

namespace ServerService {

class InterfaceDispatcher : public ServerInterface
{
    Q_OBJECT
    Q_ANNOTATION(InterfaceDispatcher, {apiBasePath(QStringLiteral("v1/dispatcher"))})
public:
    Q_INVOKABLE explicit InterfaceDispatcher(QObject *parent=nullptr);

    Q_ANNOTATION(send, nl({opPost}))
    Q_INVOKABLE QVariant send();
};

QRPC_CONTROLLER_AUTO_REGISTER(InterfaceDispatcher)

}
