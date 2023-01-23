#include "./server_interface.h"
#include <QtReforce/QApr>
#include <QCoreApplication>
#include <QMutex>
#include <QVariantHash>
#include "./server_provider.h"
#include "./server_publisher.h"

namespace ServerService {

static QMutex ___mutex;
static QVariantHash __providers;
static QVariantHash __publishers;

static void init(){
    static bool ___init=false;
    if(!___init){
        QMutexLocker locker(&___mutex);
        if(!___init){
            auto&pool=QApr::Application::i().pool();
            auto db=pool.get();
            QApr::Interface c(nullptr);
            if(c.setConnection(db)){
                QVariantHash providers;
                QVariantHash publishers;
                {
                    ProviderGDao providerGDao(&c);
                    auto list=providerGDao.recordList().resultList();
                    for(auto&v:list){
                         Provider provider(&c,v);
                         providers.insert(provider.uuid().toString(), v);
                    }
                }

                {
                    VariantUtil vu;
                    PublisherGDao providerGDao(&c);
                    auto list=providerGDao.recordList().resultList();
                    for(auto&v:list){
                         Publisher model(&c,v);
                         auto s=(model.token_md5().isEmpty())?model.uuid().toString():model.token_md5();
                         auto token=vu.toUuid(s).toString();
                         publishers.insert(token, v);
                    }
                }
                __providers=providers;
                __publishers=publishers;
                ___init=(!__providers.isEmpty() && !__publishers.isEmpty());
                db.close();
            }
        }
    }
}

Q_COREAPP_STARTUP_FUNCTION(init);

ServerInterface::ServerInterface(QObject *parent):QApr::Interface(parent)
{

}

bool ServerInterface::authorization()
{
    if(!QApr::Interface::authorization())
        return {};
    Q_DECLARE_VU;
    auto service_uuid = vu.toUuid(this->rq().authorizationService());
    auto vModel=__publishers.value(service_uuid.toString());
    auto uuid=QUuid(service_uuid);
    if(!vModel.isValid()){
        service_uuid=QUuid::fromString(this->rq().authorizationBearer());
        uuid=QUuid(service_uuid);
        vModel=__publishers.value(uuid.toString());
    }
    if(vModel.isValid()){
        Publisher model(vModel);
        this->published_uuid=model.uuid();
    }
    return !this->published_uuid.isNull();
}

const QVariantHash &ServerInterface::publishers()
{
    return __publishers;
}

const QVariantHash &ServerInterface::providers()
{
    return __providers;
}

bool ServerInterface::requestBeforeInvoke()
{
    if(QApr::Interface::requestBeforeInvoke())
        return true;
    return false;
}

}
