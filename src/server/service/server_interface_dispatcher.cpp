#include "./server_interface_dispatcher.h"
#include "./server_dispatcher_pool.h"

namespace ServerService {


InterfaceDispatcher::InterfaceDispatcher(QObject *parent):ServerInterface(parent)
{

}

InterfaceDispatcher::~InterfaceDispatcher()
{

}

QVariant InterfaceDispatcher::send()
{
    auto&instance=DispatcherPool::i();
    QRPC_METHOD_CHECK_POST();
    QRPC_V_SET_BODY_MAP(body);
    if(body.isEmpty())
        this->request().co().setBadRequest();
    else{
        emit instance.dispacher(body[qsl("uuid")].toUuid(), body);
        return QVariant();
    }
    QRPC_RETURN_ERROR();
}

}
