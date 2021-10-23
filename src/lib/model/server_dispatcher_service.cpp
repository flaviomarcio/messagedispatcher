#include "./server_dispatcher_service.h"
#include "./qapr_application.h"


namespace ServerService {

#define dPvt()\
    auto&p =*reinterpret_cast<DispatcherServicePvt*>(this->p)

class DispatcherServicePvt{
public:
    DispatcherService*parent=nullptr;
    QVariantHash settings;
    explicit DispatcherServicePvt(DispatcherService*parent){
        this->parent=parent;
    }
    virtual ~DispatcherServicePvt(){
    }
};


DispatcherService::DispatcherService(const QVariant &setting, QObject *parent) : QRpc::ServiceThread(nullptr)
{
    Q_UNUSED(parent)
    this->p = new DispatcherServicePvt(this);
    dPvt();
    p.settings=setting.toHash();
}

DispatcherService::~DispatcherService()
{
    dPvt();
    delete&p;
}

void DispatcherService::received(const QUuid &uuid, const QVariant &v){
    QRpc::ServiceThread::received(uuid,v);
}

const QVariantHash &DispatcherService::settings() const
{
    dPvt();
    return p.settings;
}

void DispatcherService::setSettings(const QVariantHash &value)
{
    dPvt();
    p.settings = value;
}

}
