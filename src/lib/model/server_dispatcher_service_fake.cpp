#include "server_dispatcher_service_fake.h"
#include "./server_publisher.h"
#include "./server_schedule_task.h"
#include "./qrpc_request.h"
#include "./qapr_application.h"

namespace ServerService {

void DispatcherServiceFake::received(const QUuid &uuid, const QVariant &v)
{
    Q_UNUSED(uuid)
    Q_UNUSED(v)
    sWarning()<<uuid.toString();
}

}
