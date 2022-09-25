#pragma once

#include "./server_interface.h"

namespace ServerService {

class InterfaceMessage : public ServerInterface
{
    Q_OBJECT
    Q_ANNOTATION(InterfaceMessage, {apiBasePath(QStringLiteral("v1/message"))})
public:
    Q_INVOKABLE explicit InterfaceMessage(QObject *parent=nullptr);

    Q_ANNOTATION(send, nl({opPost}))
    Q_INVOKABLE QVariant send();

    Q_ANNOTATION(counters, nl({opGet}))
    Q_INVOKABLE QVariant counters();
};

QRPC_CONTROLLER_AUTO_REGISTER(InterfaceMessage)

}
