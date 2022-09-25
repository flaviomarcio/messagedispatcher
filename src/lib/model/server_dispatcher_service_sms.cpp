#include "server_dispatcher_service_sms.h"
#include "./server_publisher.h"
#include "./server_schedule_task.h"
#include <QtReforce/QRpc>
#include <QtReforce/QApr>

namespace ServerService {

#define NEW_MODE_

void DispatcherServiceSMS::received(const QUuid &uuid, const QVariant &v)
{
    QVariantHash vRequestMap;
    auto vHash=v.toHash();
    {
        auto vBody=vHash[QT_STRINGIFY2(vTask)].toHash();
        auto to=QStringLiteral("+")+vBody[QStringLiteral("to")].toString().replace(QStringLiteral("+"),QString{});
        to=to.replace(QStringLiteral("++"),QStringLiteral("+"));
        if(!to.startsWith("+55"))
            to=QStringLiteral("+55")+to.replace(QStringLiteral("+"),QString{});
        QVariantHash property;
        property.insert(QStringLiteral("from"), vBody[QStringLiteral("from")]);
        property.insert(QStringLiteral("to"), to);
        property.insert(QStringLiteral("id"), uuid.toString());
        property.insert(QStringLiteral("msg"), vBody[QStringLiteral("payload")]);
        property.insert(QStringLiteral("schedule"), QVariant());
        property.insert(QStringLiteral("aggregateId"), QVariant());
        property.insert(QStringLiteral("flashSms"), false);
        property.insert(QStringLiteral("schedule"), QVariant());
        property.insert(QStringLiteral("callbackOption"), QVariant());
        vRequestMap[QStringLiteral("sendSmsRequest")]=property;
    }

    {
        QRpc::ServiceSetting setting(this);
        setting+=vHash[QT_STRINGIFY2(setting)];
        QRpc::Request req;
        req=setting;
        req.setBody(vRequestMap);
        auto&response=req.call(setting.route(), vRequestMap);
        QVariantHash vResponse, request;
        {
            request[QStringLiteral("request")]= vRequestMap;
            request[QStringLiteral("response")]= req.response().bodyHash();
        }
        vResponse[QStringLiteral("statusCode")]= response.statusCode();
        vResponse[QStringLiteral("qtStatusCode")]= response.qtStatusCode();
        vResponse[QStringLiteral("request")]= request;
        if(response.isOk()){
            emit request_success(uuid, vResponse);
        }
        else {
            emit request_error(uuid, vResponse);
        }
    }
}

}
