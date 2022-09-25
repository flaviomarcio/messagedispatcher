#include "./server_dispatcher_pool.h"
#include "./server_schedule_task.h"
#include "./server_dispatcher_service.h"
#include "./server_dispatcher_service_fake.h"
#include "./server_dispatcher_service_email.h"
#include "./server_dispatcher_service_push.h"
#include "./server_dispatcher_service_sms.h"
#include "./server_dispatcher_service_telegram.h"
#include "./server_dispatcher_service_whatsapp.h"
#include <QCoreApplication>
#include <QHash>
#include <QObject>

#define dPvt()\
    auto&p =*reinterpret_cast<DispatcherPoolPvt*>(this->p)

namespace ServerService {

typedef QHash<int, const QMetaObject*> ___ServiceMetaObject;
Q_GLOBAL_STATIC(___ServiceMetaObject,__serviceMetaObject);

static auto&serviceMetaObject=*__serviceMetaObject;

static DispatcherPool*__dispatcher_pool_instance__=nullptr;


static void __dinit_pool__(){
    if(__dispatcher_pool_instance__!=nullptr){
        __dispatcher_pool_instance__->quit();
        __dispatcher_pool_instance__->wait();
        delete __dispatcher_pool_instance__;
        __dispatcher_pool_instance__=nullptr;
    }
}

static void __init_pool__(){
    if(__dispatcher_pool_instance__==nullptr){
        serviceMetaObject.insert(dsFake, &DispatcherServiceFake::staticMetaObject);
        serviceMetaObject.insert(dsMail, &DispatcherServiceEMail::staticMetaObject);
        serviceMetaObject.insert(dsSms, &DispatcherServiceSMS::staticMetaObject);
        serviceMetaObject.insert(dsPushNotification, &DispatcherServicePush::staticMetaObject);
        serviceMetaObject.insert(dsTelegram, &DispatcherServiceTelegram::staticMetaObject);
        serviceMetaObject.insert(dsWhatsApp, &DispatcherServiceWhatsApp::staticMetaObject);
        __dispatcher_pool_instance__=new DispatcherPool(nullptr);
        __dispatcher_pool_instance__->start();
        while(__dispatcher_pool_instance__->eventDispatcher()!=nullptr)
            QThread::msleep(1);
        QThread::sleep(1);
    }
    qAddPostRoutine(__dinit_pool__); //gera loop infinito e nao deixa a aplicacao terminar
}


//Q_COREAPP_STARTUP_FUNCTION(__init_pool__)


typedef QList<DispatcherService*> DispatcherMap;
class DispatcherPoolPvt:public QObject{
public:
    QMap<int, DispatcherMap*> poolList;
    DispatcherPool*parent=nullptr;

    explicit DispatcherPoolPvt(DispatcherPool*parent=nullptr):QObject(parent){
        this->parent=parent;
        QObject::connect(this->parent, &DispatcherPool::dispacher, this, &DispatcherPoolPvt::on_dispacher);
    }

    ~DispatcherPoolPvt(){
    }

    void init(){
        auto&p=*this;
        for(auto&type:TaskTypeList){
            auto pool=p.poolList.value(type);
            if(pool==nullptr){
                pool=new DispatcherMap();
                p.poolList.insert(type, pool);
            }

            auto metaObject=serviceMetaObject.value(type);
            if(metaObject!=nullptr){
                QVariantHash settings;
                if(metaObject->inherits(&DispatcherService::staticMetaObject)){
                    auto object=metaObject->newInstance( Q_ARG(QVariant, settings ), Q_ARG(QObject*, nullptr ));
                    if(object==nullptr)
                        sWarning()<<QStringLiteral("inited fail:%1").arg(metaObject->className());
                    else{
                        auto thread=dynamic_cast<DispatcherService*>(object);
                        thread->setObjectName(thread->metaObject()->className());
                        pool->append(thread);
                        thread->start();
                        sWarning()<<QStringLiteral("inited:%1").arg(metaObject->className());
                    }
                }
            }
        }
    }

    void dinit(){
        auto&p=*this;
        auto pList=p.poolList.values();
        for(auto&list:pList){
            for(auto&v:*list){
                v->quit();
            }
        }

        for(auto&list:pList){
            for(auto&v:*list){
                if(v->wait(1000))
                    delete v;
                else
                    v->deleteLater();
            }
            delete list;
        }

        p.poolList.clear();
    }

public slots:
    void on_dispacher(const QUuid&uuid, const QVariant&v){
        auto vHash=v.toHash();
        auto&vTask=vHash[QT_STRINGIFY2(vTask)];
        ScheduleTask task(this, vTask);
        if(task.isValid()){
            auto&p=*this;

            auto type=task.type();
            auto pool=p.poolList.value(type);
            if(pool!=nullptr){
                DispatcherService*service=nullptr;
                for(auto&v:*pool){
                    if(v==nullptr)
                        continue;
                    else if(service==nullptr)
                        service=v;
                    else if(v->stats().received<service->stats().received)
                        service=v;
                    else
                        continue;
                }
                if(service!=nullptr){
                    service->dispatcher(uuid, v);
                }
            }
        }
    }
};

DispatcherPool::DispatcherPool(QObject *parent) : QThread(nullptr)
{
    Q_UNUSED(parent)
    this->p=new DispatcherPoolPvt(this);
}

DispatcherPool &DispatcherPool::i()
{
    if(__dispatcher_pool_instance__==nullptr)
        __init_pool__();
    return*__dispatcher_pool_instance__;
}

void DispatcherPool::run()
{
    dPvt();
    p.init();
    this->exec();
    p.dinit();
}

}
