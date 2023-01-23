#include "./server_interface_message.h"
#include "./server_controller_schedule.h"

namespace ServerService {


InterfaceMessage::InterfaceMessage(QObject *parent):ServerInterface(parent)
{

}

QVariant InterfaceMessage::send()
{
    QRPC_V_SET_UUID(uuid);
    QRPC_V_SET(type);
    QRPC_V_SET_BYTE(to);
    QRPC_V_CHECK_BODY_PARSER();
    QRPC_V_SET_BYTE(subject);
    QRPC_V_SET_BYTE(payload);
    QRPC_V_SET(attachment);
    ControllerShedule controller(this);
    if(!controller.send(this->published_uuid, uuid, type, to, subject, payload, attachment))
        this->rq().co(controller.lr().sc());
    else
        return controller.lr().resultVariant();
    QRPC_RETURN_ERROR();
}

QVariant InterfaceMessage::counters()
{
    ControllerShedule controller(this);
    if(!controller.counters(this->published_uuid))
        this->rq().co(controller.lr().sc());
    else
        return controller.lr().resultVariant();
    QRPC_RETURN_ERROR();
}

}
