#include "server_dispatcher_service_fake.h"
#include "./server_publisher.h"
#include "./server_schedule_task.h"
#include <QtReforce/QRpc>
#include <QtReforce/QApr>

namespace ServerService {

void DispatcherServiceFake::received(const QUuid &uuid, const QVariant &v)
{
    Q_UNUSED(uuid)
    Q_UNUSED(v)
    sWarning()<<uuid.toString();
}

}
