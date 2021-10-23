#include "server_dispatcher_service_telegram.h"
#include "./server_publisher.h"
#include "./server_schedule_task.h"
#include "./qrpc_request.h"
#include <QVariantMap>
#include "./qapr_application.h"

namespace ServerService {

struct ConstsDispatcherTelegram{
    QRpc::ServiceSetting setting;
    void init(){
        auto&manager=QApr::Application::instance().manager();
        setting=manager.setting(QStringLiteral("dispatcher-telegram"));
    }
};

Q_GLOBAL_STATIC(ConstsDispatcherTelegram, __constsDispatcherTelegram);
static auto&constsDispatcherTelegram=*__constsDispatcherTelegram;

}
