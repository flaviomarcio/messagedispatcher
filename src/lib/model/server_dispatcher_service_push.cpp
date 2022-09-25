#include "server_dispatcher_service_push.h"
#include "./server_publisher.h"
#include "./server_schedule_task.h"
#include <QtReforce/QRpc>
#include <QtReforce/QApr>

namespace ServerService {

void DispatcherServicePush::received(const QUuid &uuid, const QVariant&v)
{
    QString serverKey;
    QVariantMap vMap;
    {
        auto vBodyContent=v.toMap();

        QVariantMap data;
        data.insert("data",   vBodyContent["data"]);//qualquer map chave valor que o dispositivo precice receber. Geralmente é utilizado para tratamento interno de negocio.

        QVariantMap notification;
        notification.insert("title",   vBodyContent["title"]);
        notification.insert("body",   vBodyContent["body"]);
        notification.insert("image",   vBodyContent["imageUrl"]);


        QVariantMap payload;
        payload.insert("data", data);
        payload.insert("notification", notification);
        payload.insert("direct_book_ok", vBodyContent["direct_book_ok"]);
        payload.insert("to"            , vBodyContent["deviceKey"]); //key da instancia do aplicativo no dispositivo ou key para um tópico cadastrado no FCM

        vMap = payload;
    }

    {
        const QByteArray hostname = QString("https://fcm.googleapis.com/fcm/").toLatin1();
        const QByteArray route="send";

        QRpc::Request req;
        req.header().setRawHeader("Content-Type","application/json");
        req.header().setRawHeader("Authorization",QString("key=%1").arg(serverKey).toLatin1());
        req.header().setContentType(QRpc::AppJson);

        req.body().setBody(vMap);

        req.setProtocol("https");
        req.setHostName(hostname);
        req.setPort(80);

        auto&response=req.call(route, vMap);

        if(response.isOk()){
//            {"multicast_id":388936321720733172,"success":1,"failure":0,"canonical_ids":0,"results":[{"message_id":"0:1601568351568498%31bd1c9631bd1c96"}]} //exemplo de mensagem de retorno
            emit request_success(uuid, vMap);
        }
        else {
            QVariantMap responseMap;
            sWarning()<<QString("%1").arg(responseMap["success"].toString())<<QString("%1").arg(responseMap["results"].toString());
            responseMap.insert("statecode", response.statusCode());
            responseMap.insert("qtStatusCode", response.qtStatusCode());
            responseMap.insert("body", req.response().bodyMap());

            QVariantMap vBody;
            vBody.insert("request", vBody);
            vBody.insert("response", responseMap);
            emit request_success(uuid, vBody);
        }

    }

}

//bool DispatcherServicePush::authenticate()
//{
//    return true;
//}

//QVariantMap DispatcherServicePush::buildRequestBody()
//{
//    return QVariantMap();
//}

}
