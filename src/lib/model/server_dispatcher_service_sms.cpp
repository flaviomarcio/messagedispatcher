#include "server_dispatcher_service_sms.h"
#include "./server_publisher.h"
#include "./server_schedule_task.h"
#include "./qrpc_request.h"
#include "./qapr_application.h"

namespace ServerService {

#define NEW_MODE_

void DispatcherServiceSMS::received(const QUuid &uuid, const QVariant &v)
{
    QVariantHash vRequestMap;
    auto vHash=v.toHash();
    {
        auto vBody=vHash[qsl_fy(vTask)].toHash();
        auto to=qsl("+")+vBody[qsl("to")].toString().replace(qsl("+"),qsl_null);
        to=to.replace(qsl("++"),qsl("+"));
        if(!to.startsWith("+55"))
            to=qsl("+55")+to.replace(qsl("+"),qsl_null);
        QVariantHash property;
        property.insert(qsl("from"), vBody[qsl("from")]);
        property.insert(qsl("to"), to);
        property.insert(qsl("id"), uuid.toString());
        property.insert(qsl("msg"), vBody[qsl("payload")]);
        property.insert(qsl("schedule"), QVariant());
        property.insert(qsl("aggregateId"), QVariant());
        property.insert(qsl("flashSms"), false);
        property.insert(qsl("schedule"), QVariant());
        property.insert(qsl("callbackOption"), QVariant());
        vRequestMap[qsl("sendSmsRequest")]=property;
    }

    {
        QRpc::ServiceSetting setting(this);
        setting+=vHash[qsl_fy(setting)];
        QRpc::QRPCRequest req;
        req=setting;
        req.setBody(vRequestMap);
        auto&response=req.call(setting.route(), vRequestMap);
        QVariantHash vResponse, request;
        {
            request[qsl("request")]= vRequestMap;
            request[qsl("response")]= req.response().bodyHash();
        }
        vResponse[qsl("statusCode")]= response.statusCode();
        vResponse[qsl("qtStatusCode")]= response.qtStatusCode();
        vResponse[qsl("request")]= request;
        if(response.isOk()){
            emit request_success(uuid, vResponse);
        }
        else {
            emit request_error(uuid, vResponse);
        }
    }
}

}
