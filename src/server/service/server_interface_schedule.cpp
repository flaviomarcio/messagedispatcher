#include "./server_interface_schedule.h"
#include "./server_controller_schedule.h"

namespace ServerService {


InterfaceSchedule::InterfaceSchedule(QObject *parent):ServerInterface(parent)
{

}

QVariant InterfaceSchedule::create()
{
    ControllerShedule controller(this);
    if(controller.create(this->published_uuid))
        return controller.lr().resultVariant();
    QRPC_RETURN_ERROR();
}

QVariant InterfaceSchedule::insert()
{
    QRPC_V_SET_UUID(schedule_uuid);
    QRPC_V_SET_UUID(uuid);
    QRPC_V_SET(type);
    QRPC_V_SET(to);
    QRPC_V_SET(payload);
    QRPC_V_CHECK_BODY_PARSER();
    ControllerShedule controller(this);
    if(controller.insert(this->published_uuid, schedule_uuid, type, uuid, to, payload))
        return controller.lr().resultVariant();
    QRPC_RETURN_ERROR();
}

QVariant InterfaceSchedule::send()
{
    QRPC_V_SET_UUID(schedule_uuid);
    QRPC_V_CHECK_BODY_PARSER();
    ControllerShedule controller(this);
    if(controller.send(this->published_uuid, schedule_uuid))
        return controller.lr().resultVariant();
    QRPC_RETURN_ERROR();
}

QVariant InterfaceSchedule::cancel()
{
    QRPC_V_SET_UUID(schedule_uuid);
    QRPC_V_CHECK_BODY_PARSER();
    ControllerShedule controller(this);
    if(controller.cancel(this->published_uuid, schedule_uuid))
        return controller.lr().resultVariant();
    QRPC_RETURN_ERROR();
}

QVariant InterfaceSchedule::stat()
{
    QRPC_V_SET_UUID(uuid);
    QRPC_V_CHECK_BODY_PARSER();
    ControllerShedule controller(this);
    if(controller.stat(this->published_uuid, uuid))
        return controller.lr().resultVariant();
    QRPC_RETURN_ERROR();
}

QVariant InterfaceSchedule::stat_task()
{
    QRPC_V_SET_UUID(uuid);
    QRPC_V_CHECK_BODY_PARSER();
    ControllerShedule controller(this);
    if(controller.stat_task(this->published_uuid, uuid))
        return controller.lr().resultVariant();
    QRPC_RETURN_ERROR();
}

QVariant InterfaceSchedule::stats()
{
    ControllerShedule controller(this);
    if(controller.stats())
        return controller.lr().resultVariant();
    QRPC_RETURN_ERROR();
}

}
