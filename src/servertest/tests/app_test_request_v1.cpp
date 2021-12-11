#ifndef TestRequestV1_H
#define TestRequestV1_H

#include "./qapr_test.h"

class TestRequestV1 : public QApr::SDKGoogleTest {
public:
    const int server_port=9999;
    const QString token_published_uuid=toMd5("acl_account_token");
};
static QUuid schedule_uuid;
static QStringList schedule_uuidList;
static QStringList schedule_uuidUnique;
static QVariantList task_uuidList;

QRPC_DECLARE_REQUEST_CLASS(GoogleTestRequestSchedule,QRpc::AppJson,v1/schedule)
QRPC_DECLARE_REQUEST_CLASS(GoogleTestRequestMessage,QRpc::AppJson,v1/message)



#define d_GoogleTestRequestSchedule(request)\
    GoogleTestRequestSchedule request;\
    request.header().setAuthorization(QRpc::Service,token_published_uuid);\
    request.setPort(server_port);\

#define d_GoogleTestRequestMessage(request)\
    GoogleTestRequestMessage request;\
    request.header().setAuthorization(QRpc::Service,token_published_uuid);\
    request.setPort(server_port);\

TEST_F(TestRequestV1, start)
{
    auto&http=this->service().colletions().protocol(QRpc::Http);
    http.setPort(server_port);
    EXPECT_EQ(this->serviceStart(),true)<<"fail: service start";
}

TEST_F(TestRequestV1, ping)
{
    d_GoogleTestRequestMessage(request);

    auto&response=request.call("ping",QVariant());
    EXPECT_EQ(response.isOk(),true)<<"fail";
    auto dt=QDate::fromString(response.body(),Qt::ISODate);
    EXPECT_EQ(dt,QDate::currentDate())<<"fail";
}

TEST_F(TestRequestV1, createSend_fake)
{
    d_GoogleTestRequestMessage(request);
    const static auto toList=QVector<QString>{"112233445566778899-1","112233445566778899-2"};
    for(auto&to:toList){
        QVariantMap map;
        map.insert("uuid",QUuid::createUuid());
        map.insert("type",qsl_fy(fake));
        map.insert("to",to);
        map.insert("payload","...Message..");
        auto&response=request.call("send",map);
        EXPECT_EQ(response.isOk(),true)<<"fail";
        auto vMap=response.bodyMap();
        schedule_uuid=vMap.value("uuid").toUuid();
        EXPECT_EQ(schedule_uuid.isNull(),false)<<"fail";
    }
}

TEST_F(TestRequestV1, createSend_sms)
{
    d_GoogleTestRequestMessage(request);

    const static auto toList=QVector<QString>{"+55(98)9 9135-8855", "5598991358855"};

    int i=0;
    for(auto&phone:toList){
        QVariantMap map;
        map.insert("uuid",QUuid::createUuid());
        map.insert("type",qsl_fy(sms));
        map.insert("to",phone);
        map.insert("payload",QString("...Message.., text:%1").arg(++i));
        auto&response=request.call("send",map);
        EXPECT_EQ(response.isOk(),true)<<"fail";
        auto vMap=response.bodyMap();
        schedule_uuid=vMap.value("uuid").toUuid();
        EXPECT_EQ(schedule_uuid.isNull(),false)<<"fail";
    }

}

TEST_F(TestRequestV1, createSend_e_mail)
{
    d_GoogleTestRequestMessage(request);

    const static auto toList=QVector<QString>{"email1@magma-ma.com.br", "email2@magma-ma.com.br"};

    int i=0;
    for(auto&to:toList){
        QVariantMap map;
        map.insert("uuid",QUuid::createUuid());
        map.insert("type",qsl_fy(email));
        map.insert("to",to);
        map.insert("payload",QString("...Message.., text:%1").arg(++i));
        auto&response=request.call("send",map);
        EXPECT_EQ(response.isOk(),true)<<"fail";
        auto vMap=response.bodyMap();
        schedule_uuid=vMap.value("uuid").toUuid();
        EXPECT_EQ(schedule_uuid.isNull(),false)<<"fail";
    }

}

TEST_F(TestRequestV1, createSend_push_notification)
{
    d_GoogleTestRequestMessage(request);

    const static auto toList=QVector<QString>{"5598991358855", "5598981148707"};

    int i=0;
    for(auto&phone:toList){
        QVariantMap map;
        map.insert("uuid",QUuid::createUuid());
        map.insert("type",qsl_fy(pushnotification));
        map.insert("to",phone);
        map.insert("payload",QString("...Message.., text:%1").arg(++i));
        auto&response=request.call("send",map);
        EXPECT_EQ(response.isOk(),true)<<"fail";
        auto vMap=response.bodyMap();
        schedule_uuid=vMap.value("uuid").toUuid();
        EXPECT_EQ(schedule_uuid.isNull(),false)<<"fail";
    }

}


TEST_F(TestRequestV1, createcreateSend_telegram)
{
    d_GoogleTestRequestMessage(request);

    const static auto toList=QVector<QString>{"5598991358855", "5598981148707"};

    int i=0;
    for(auto&phone:toList){
        QVariantMap map;
        map.insert("uuid",QUuid::createUuid());
        map.insert("type",qsl_fy(telegram));
        map.insert("to",phone);
        map.insert("payload",QString("...Message.., text:%1").arg(++i));
        auto&response=request.call("send",map);
        EXPECT_EQ(response.isOk(),true)<<"fail";
        auto vMap=response.bodyMap();
        schedule_uuid=vMap.value("uuid").toUuid();
        EXPECT_EQ(schedule_uuid.isNull(),false)<<"fail";
    }

}

TEST_F(TestRequestV1, createSend_whatsapp)
{
    d_GoogleTestRequestMessage(request);

    const static auto toList=QVector<QString>{"5598991358855", "5598981148707"};

    int i=0;
    for(auto&phone:toList){
        QVariantMap map;
        map.insert("uuid",QUuid::createUuid());
        map.insert("type",qsl_fy(whatsapp));
        map.insert("to",phone);
        map.insert("payload",QString("...Message.., text:%1").arg(++i));
        auto&response=request.call("send",map);
        EXPECT_EQ(response.isOk(),true)<<"fail";
        auto vMap=response.bodyMap();
        schedule_uuid=vMap.value("uuid").toUuid();
        EXPECT_EQ(schedule_uuid.isNull(),false)<<"fail";
    }

}


TEST_F(TestRequestV1, create)
{
    d_GoogleTestRequestSchedule(request);

    auto&response=request.call("create",QVariant());
    EXPECT_EQ(response.isOk(),true)<<"fail";
    auto vMap=response.bodyMap();
    schedule_uuid=vMap.value("uuid").toUuid();
    EXPECT_EQ(schedule_uuid.isNull(),false)<<"fail";
}

TEST_F(TestRequestV1, insert_single_push)
{
    for (int msg = 1000; msg < 1010; ++msg) {
        d_GoogleTestRequestSchedule(request);
        QVariantMap map;
        map.insert("schedule_uuid", schedule_uuid);
        map.insert("type", qsl_fy(PushNotification));
        map.insert("uuid", QUuid::createUuid());
        map.insert("to",QString("+55(98)8888-9999"));
        {
            QVariantList vList;
            for (int msg = 1000; msg < 1005; ++msg) {
                vList<<QString("message %1").arg(msg);
            }
            map.insert("payload",vList);
        }
        auto&response = request.call("insert", map);
        EXPECT_EQ(response.isOk(),true)<<"fail";
        if(response.isOk()){
            auto bodyMap=response.bodyMap();
            EXPECT_EQ(bodyMap.isEmpty(),false)<<"fail";
            EXPECT_EQ(bodyMap.contains("schedule_uuid"),true)<<"fail";
            EXPECT_EQ(bodyMap.contains("tasks"),true)<<"fail";

            auto v_schedule_uuid=bodyMap.value("schedule_uuid");

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
            if(v_schedule_uuid.typeId()==QMetaType::QVariantList || v_schedule_uuid.typeId()==QMetaType::QStringList){
#else
            if(v_schedule_uuid.type()==QVariant::List || v_schedule_uuid.type()==QVariant::StringList){
#endif
                for(auto&v:v_schedule_uuid.toList()){
                    if(!schedule_uuidList.contains(v.toString()))
                        schedule_uuidList<<v.toString();
                }
            }
            else{
                auto&v=v_schedule_uuid;
                if(!schedule_uuidList.contains(v.toString()))
                    schedule_uuidList<<v.toString();
            }

            auto vTask=bodyMap.value("tasks");
            QVariantList vTaskList;
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
            if(vTask.typeId()==QMetaType::QVariantList || vTask.typeId()==QMetaType::QStringList){
#else
            if(vTask.type()==QVariant::List || vTask.type()==QVariant::StringList){
#endif
                for(auto&v:vTask.toList())
                    vTaskList<<v;
            }
            else{
                vTaskList<<vTask;
            }
            for(auto&v:vTaskList){
                auto map=v.toMap();
                task_uuidList<<map.value("uuid");
            }
        }
    }
}

TEST_F(TestRequestV1, insert_massive)
{
    for (int msg = 1000; msg < 1010; ++msg) {
        d_GoogleTestRequestSchedule(request);
        QVariantMap map;
        map.insert("schedule_uuid", schedule_uuid);
        map.insert("uuid", QUuid::createUuid());
        map.insert("type", qsl_fy(telegram));
        {
            QVariantList vList;
            for (int msg = 1000; msg < 1010; ++msg) {
                vList<<QString("+5598%1%1").arg(msg);
            }
            map.insert("to",vList);
        }
        {
            QVariantList vList;
            for (int msg = 1000; msg < 1100; ++msg) {
                vList<<QString("message %1").arg(msg);
            }
            map.insert("payload",vList);
        }
        auto&response = request.call("insert", map);
        EXPECT_EQ(response.isOk(),true)<<"fail";
        if(response.isOk()){
            auto bodyMap=response.bodyMap();
            EXPECT_EQ(bodyMap.isEmpty(),false)<<"fail";
            EXPECT_EQ(bodyMap.contains("schedule_uuid"),true)<<"fail";
            EXPECT_EQ(bodyMap.contains("tasks"),true)<<"fail";

            auto v_schedule_uuid=bodyMap.value("schedule_uuid");

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
            if(v_schedule_uuid.typeId()==QMetaType::QVariantList || v_schedule_uuid.typeId()==QMetaType::QStringList){
#else
            if(v_schedule_uuid.type()==QVariant::List || v_schedule_uuid.type()==QVariant::StringList){
#endif
                for(auto&v:v_schedule_uuid.toList()){
                    if(!schedule_uuidList.contains(v.toString()))
                        schedule_uuidList<<v.toString();
                }
            }
            else{
                auto&v=v_schedule_uuid;
                if(!schedule_uuidList.contains(v.toString()))
                    schedule_uuidList<<v.toString();
            }

            auto vTask=bodyMap.value("tasks");
            QVariantList vTaskList;
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
            if(vTask.typeId()==QMetaType::QVariantList || vTask.typeId()==QMetaType::QStringList){
#else
            if(vTask.type()==QVariant::List || vTask.type()==QVariant::StringList){
#endif
                for(auto&v:vTask.toList())
                    vTaskList<<v;
            }
            else{
                vTaskList<<vTask;
            }
            for(auto&v:vTaskList){
                auto map=v.toMap();
                task_uuidList<<map.value("uuid");
            }
        }
    }
}

TEST_F(TestRequestV1, stat_before_send)
{
    d_GoogleTestRequestSchedule(request);
    for(auto&v:schedule_uuidList){
        QUuid uuid=toUUID(v);
        QVariantMap map;
        map.insert("uuid", uuid);
        auto&response=request.call("stat", map);
        EXPECT_EQ(response.isOk(),true)<<"fail";
        if(response.isOk()){
            auto body=response.bodyMap();
            EXPECT_EQ(body.contains("uuid"),true)<<"fail";
            EXPECT_EQ(body.contains("state"),true)<<"fail";
            EXPECT_EQ(body.value("uuid").toUuid().toString(),uuid.toString())<<"fail";
            EXPECT_EQ(body.value("state").toInt()==0/*Wait*/,true)<<"fail";
        }
    }
}

TEST_F(TestRequestV1, send)
{
    d_GoogleTestRequestSchedule(request);
    for(auto&v:schedule_uuidList){
        QUuid uuid=toUUID(v);
        QVariantMap map;
        map.insert("schedule_uuid", uuid);
        auto&response=request.call("send", map);
        EXPECT_EQ(response.isOk(),true)<<"fail";
        if(response.isOk()){
            auto body=response.bodyMap();
            EXPECT_EQ(body.isEmpty(),false)<<"fail";
            EXPECT_EQ(body.contains("uuid"),true)<<"fail";
            EXPECT_EQ(body.contains("state"),true)<<"fail";
            EXPECT_EQ(body.value("uuid").toUuid().toString(),uuid.toString())<<"fail";
            EXPECT_EQ(body.value("state").toInt()==2/*Send*/,true)<<"fail";
        }
    }
}

TEST_F(TestRequestV1, counters)
{
    d_GoogleTestRequestMessage(request);

    auto&response=request.call(QRpc::Get,"counters",QVariant());
    EXPECT_EQ(response.isOk(),true)<<"fail";
    auto hash=response.bodyHash();
    EXPECT_EQ(hash.isEmpty(),false)<<"fail";
    EXPECT_EQ(hash.contains(qsl("tasks_count_day")),true)<<"fail";
    EXPECT_EQ(hash.contains(qsl("tasks_count_month")),true)<<"fail";

    EXPECT_EQ(hash.value(qsl("tasks_count_day")).toInt()>0,true)<<"fail";
    EXPECT_EQ(hash.value(qsl("tasks_count_month")).toInt()>0,true)<<"fail";
}

TEST_F(TestRequestV1, stat_after_send)
{
    d_GoogleTestRequestSchedule(request);
    for(auto&v:schedule_uuidList){
        QUuid uuid=toUUID(v);
        QVariantMap map;
        map.insert("uuid", uuid);
        auto&response=request.call("stat", map);
        EXPECT_EQ(response.isOk(),true)<<"fail";
        if(response.isOk()){
            auto body=response.bodyMap();
            EXPECT_EQ(body.contains("uuid"),true)<<"fail";
            EXPECT_EQ(body.contains("state"),true)<<"fail";
            EXPECT_EQ(body.value("uuid").toUuid().toString(),uuid.toString())<<"fail";
            EXPECT_EQ(body.value("state").toInt()==2/*Send*/ || body.value("state").toInt()==3/*Sent*/,true)<<"fail";
        }
    }
}

TEST_F(TestRequestV1, stat_task)
{
    d_GoogleTestRequestSchedule(request);
    for(auto&v:task_uuidList){
        QUuid uuid=toUUID(v);
        QVariantMap map;
        map.insert("uuid", uuid);
        auto&response=request.call("stat_task", map);
        EXPECT_EQ(response.isOk(),true)<<"fail";
        if(response.isOk()){
            auto body=response.bodyMap();
            EXPECT_EQ(body.isEmpty(),false)<<"fail";
            EXPECT_EQ(body.contains("uuid"),true)<<"fail";
            EXPECT_EQ(body.value("state").toInt()==0/*Wait*/ || body.value("state").toInt()==2/*Sent*/,true)<<"fail";
            EXPECT_EQ(body.value("uuid").toUuid().toString(),uuid.toString())<<"fail";
        }
    }
}

TEST_F(TestRequestV1, cancel)
{
    d_GoogleTestRequestSchedule(request);
    for(auto&v:schedule_uuidList){
        QUuid uuid=toUUID(v);
        QVariantMap map;
        map.insert("schedule_uuid", uuid);
        auto&response=request.call("cancel", map);
        EXPECT_EQ(response.isOk(),true)<<"fail";
        if(response.isOk()){
            auto body=response.bodyMap();
            EXPECT_EQ(body.isEmpty(),false)<<"fail";
            EXPECT_EQ(body.contains("uuid"),true)<<"fail";
            EXPECT_EQ(body.contains("state"),true)<<"fail";
            EXPECT_EQ(body.value("uuid").toUuid().toString(),uuid.toString())<<"fail";
            EXPECT_EQ(body.value("state").toInt(),4/*Canceled*/)<<"fail";
        }
    }
}

TEST_F(TestRequestV1, stats)
{
    d_GoogleTestRequestSchedule(request);
    QVariantMap map;
    auto&response=request.call("stats", map);
    if(response.isOk()){
        auto body=response.bodyMap();
        EXPECT_EQ(body.isEmpty(),false)<<"fail";
    }
}


TEST_F(TestRequestV1, stop)
{
    QThread::sleep(5);
    EXPECT_EQ(this->serviceStop(),true)<<"fail: service stop";
}

#endif // TestRequestV1_H
