#include "./server_dao_schedule.h"
#include "./qorm_query.h"
#include "./server_schedule_task.h"

namespace ServerService {

DaoSchedule::DaoSchedule(QObject *parent) : QOrm::Dao(parent)
{

}

DaoSchedule::~DaoSchedule()
{

}

ResultValue &DaoSchedule::tasks_count_month(const QUuid &published_uuid, const QDate &dt)
{
    Q_DECLARE_DU;
    QOrm::Query query(this);
    auto&select=query.builder().select();
    select.
        fields().count();
    select
        .from(ScheduleTaskR)
        .where()
        .equal(ScheduleTaskM.published_uuid_field(), published_uuid)
        .between(ScheduleTaskM.dt_field(), du.minMonthDateTime(dt), du.maxMonthDateTime(dt));

    if(!query.exec())
        return this->lr(query.lastError());

    if (!query.next())
        return this->lr(QVariant(0));

    return this->lr(query.value(0));
}

ResultValue &DaoSchedule::tasks_count_day(const QUuid &published_uuid, const QDate &dt)
{
    Q_DECLARE_DU;
    QOrm::Query query(this);
    auto&select=query.builder().select();
    select.
        fields().count();
    select
        .from(ScheduleTaskR)
        .where()
        .equal(ScheduleTaskM.published_uuid_field(), published_uuid)
        .between(ScheduleTaskM.dt_field(), du.minDateTime(dt), du.maxDateTime(dt));

    if(!query.exec())
        return this->lr(query.lastError());

    if (!query.next())
        return this->lr(QVariant(0));

    return this->lr(query.value(0));
}

}
