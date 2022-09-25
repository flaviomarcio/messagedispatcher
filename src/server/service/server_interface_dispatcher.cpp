#include "./server_interface_dispatcher.h"
#include "./server_dispatcher_pool.h"

namespace ServerService {


InterfaceDispatcher::InterfaceDispatcher(QObject *parent):ServerInterface(parent)
{

}

QVariant InterfaceDispatcher::send()
{
    auto&instance=DispatcherPool::i();
    QRPC_V_SET_BODY_MAP(body);
    if(body.isEmpty())
        this->request().co().setBadRequest();
    else{
        emit instance.dispacher(body[QStringLiteral("uuid")].toUuid(), body);
        return {};
    }
    QRPC_RETURN_ERROR();
}

}
