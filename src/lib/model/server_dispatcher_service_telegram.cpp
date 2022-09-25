#include "server_dispatcher_service_telegram.h"
#include "./server_publisher.h"
#include "./server_schedule_task.h"
#include <QtReforce/QRpc>
#include <QtReforce/QApr>
#include <QVariantMap>

namespace ServerService {

struct ConstsDispatcherTelegram{
    QRpc::ServiceSetting setting;
    void init(){
        auto&manager=QApr::Application::i().manager();
        setting=manager.setting(QStringLiteral("dispatcher-telegram"));
    }
};

Q_GLOBAL_STATIC(ConstsDispatcherTelegram, __constsDispatcherTelegram);
static auto&constsDispatcherTelegram=*__constsDispatcherTelegram;

}
