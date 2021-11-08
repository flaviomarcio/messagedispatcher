#pragma once

#include "./server_base_controller.h"

namespace ServerService {
    class ControllerShedule : public ControllerBase
    {
        Q_OBJECT
    public:
        explicit ControllerShedule(QObject *parent = nullptr);
        ~ControllerShedule();

        ResultValue &create(const QUuid &published_uuid);

        ResultValue &insert(const QUuid &published_uuid, const QUuid &schedule_uuid, const QVariant &type, const QVariant &uuid, const QVariant &to, const QVariant &payload);

        ResultValue &send(const QUuid &published_uuid, const QUuid &schedule_uuid);

        ResultValue &cancel(const QUuid &published_uuid, const QUuid &schedule_uuid);

        ResultValue &stat(const QUuid &published_uuid, const QUuid &schedule_uuid);

        ResultValue &stat_task(const QUuid &published_uuid, const QUuid &task_uuid);

        ResultValue &send(const QUuid &published_uuid, const QUuid&customer_uuid, const QVariant &type, const QByteArray &to, const QByteArray &subject, const QByteArray &payload, const QVariant&attachment);

        ResultValue &stats();

        ResultValue &counters(const QUuid&published_uuid);
    };

}
