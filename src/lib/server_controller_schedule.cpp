#include "./server_controller_schedule.h"
#include "./server_publisher.h"
#include "./server_provider.h"
#include "./server_publisher_provider.h"
#include "./server_schedule.h"
#include "./server_schedule_task.h"
#include "./server_dispatcher_pool.h"
#include "./qorm_query.h"

namespace ServerService {

    ControllerShedule::ControllerShedule(QObject *parent) : ControllerBase(parent)
    {
    }

    ControllerShedule::~ControllerShedule()
    {

    }

    ResultValue &ControllerShedule::create(const QUuid&published_uuid)
    {
        ScheduleGDao dao(this);
        Schedule schedule(this);
        schedule.set_published_uuid(published_uuid);
        schedule.set_state(schedule.Wait);
        if(!dao.insert(schedule))
            return this->lr();
        else
            return this->lr(schedule.toWrapper());
    }

    ResultValue &ControllerShedule::insert(const QUuid&published_uuid, const QUuid&schedule_uuid, const QVariant&type, const QVariant&uuid, const QVariant&to, const QVariant&payload)
    {
        ScheduleGDao dao(this);
        Schedule schedule(this, schedule_uuid);
        if(!dao.reload(schedule))
            return this->lr().setNotFound();
        else if(schedule.published_uuid()!=published_uuid)
            return this->lr().setUnauthorized();
        else if(schedule.state()!=schedule.Wait)
            return this->lr().setUnauthorized(tr("Invalid state"));
        else{

            auto provider_type=TaskTypeMap.value(type.toString().trimmed().toLower());

            Q_DECLARE_VU;

            auto vvm=vu
                           .makeVVM(PublisherProviderM.publisher_uuid_field(), published_uuid)
                           .makeVVM(PublisherProviderM.provider_type_field(), provider_type)
                           .toVVM();

            Provider provider(this);
            ProviderGDao providerDao(this);
            PublisherProvider publisherProvider(this);
            PublisherProviderGDao publisherProviderDao(this);
            if(!publisherProviderDao.reload(publisherProvider, vvm))
                return this->lr().setNotImplemented(tr("Invalid publisherProvider: '%1'").arg(type.toString()));
            else if(!providerDao.reload(provider, publisherProvider.provider_uuid()))
                return this->lr().setNotImplemented(tr("Invalid provider: '%1'").arg(type.toString()));
            else if(!provider.enabled())
                return this->lr().setNotImplemented(tr("Invalid provider disabled: '%1'").arg(provider.name()));
            else{
                //payload
                QVariantList listDestine;
                QVariantList listPayload;

                if(to.type()==QVariant::List || to.type()==QVariant::StringList)
                    listDestine=to.toList();
                else
                    listDestine<<to;

                if(payload.type()==QVariant::List || payload.type()==QVariant::StringList)
                    listPayload=payload.toList();
                else
                    listPayload<<payload;

                QVariantList vList;

                ScheduleTaskGDao dao(this);
                for(auto&to:listDestine){
                    to=to.toByteArray().replace(qbl("+"),qbl_null).replace(qbl("-"),qbl_null).replace(qbl("("),qbl_null).replace(qbl(")"),qbl_null).replace(qbl(" "),qbl_null).trimmed();
                    for(auto&payload:listDestine){
                        ScheduleTask task(this);
                        task.set_published_uuid(uuid.toUuid());
                        task.set_type(publisherProvider.provider_type());
                        task.set_published_provider_uuid(publisherProvider.uuid());
                        task.set_schedule_uuid(schedule.uuid());
                        task.set_to(to.toByteArray());
                        task.set_payload(payload.toByteArray());
                        if(!dao.insert(task))
                            return this->lr();
                        else{
                            auto map=task.toWrapper();
                            map.insert(qsl("customer_uuid"),uuid);
                            vList<<map;
                        }
                    }
                }
                QVariantMap map;
                map.insert(qsl("schedule_uuid"), schedule_uuid);
                map.insert(qsl("tasks"), vList);
                return this->lr(map);
            }

        }
    }

    ResultValue &ControllerShedule::send(const QUuid&published_uuid, const QUuid &schedule_uuid)
    {
        ScheduleGDao dao(this);
        Schedule schedule(this, schedule_uuid);
        if(!dao.lock(schedule))
            return this->lr().setNotFound();
        else if(schedule.published_uuid()!=published_uuid)
            return this->lr().setUnauthorized();
        else if(schedule.state()==schedule.Send)
            return this->lr(schedule.toWrapper());
        else if(schedule.state()==schedule.Sent)
            return this->lr(schedule.toWrapper());
        else if(schedule.state()==schedule.Canceled)
            return this->lr().setUnauthorized(tr("schedule canceled"));
        else if(schedule.state()!=schedule.Wait)
            return this->lr().setUnauthorized(tr("Invalid state"));
        else if(!schedule.set_state(schedule.Send))
            return this->lr();
        else if(!dao.update(schedule))
            return this->lr();
        else
            return this->lr(schedule.toWrapper());
    }

    ResultValue &ControllerShedule::cancel(const QUuid&published_uuid, const QUuid &schedule_uuid)
    {
        ScheduleGDao dao(this);
        Schedule schedule(this, schedule_uuid);
        if(!dao.lock(schedule))
            return this->lr().setNotFound();
        else if(schedule.published_uuid()!=published_uuid)
            return this->lr().setUnauthorized();
        else if(schedule.state()==schedule.Canceled)
            return this->lr(schedule.toWrapper());
        else if(schedule.state()!=schedule.Send)
            return this->lr().setUnauthorized(tr("Invalid state"));
        else if(!schedule.set_state(schedule.Canceled))
            return this->lr().setUnauthorized(tr("Invalid state"));
        else if(!dao.update(schedule))
            return this->lr();
        else
            return this->lr(schedule.toWrapper());
    }

    ResultValue &ControllerShedule::stat(const QUuid&published_uuid, const QUuid &schedule_uuid)
    {
        ScheduleGDao dao(this);
        Schedule schedule(this, schedule_uuid);
        if(!dao.reload(schedule))
            return this->lr().setNotFound();
        else if(schedule.published_uuid()!=published_uuid)
            return this->lr().setUnauthorized();
        else
            return this->lr(schedule.toWrapper());
    }

    ResultValue &ControllerShedule::stat_task(const QUuid &published_uuid, const QUuid &task_uuid)
    {
        ScheduleTaskGDao scheduleTaskGDao(this);
        ScheduleGDao scheduleGDao(this);

        Schedule schedule(this);
        ScheduleTask scheduleTask(this, task_uuid);
        if(!scheduleTaskGDao.reload(scheduleTask))
            return this->lr().setNotFound();
        else if(!schedule.set_uuid(scheduleTask.schedule_uuid()))
            return this->lr();
        else if(!scheduleGDao.reload(schedule))
            return this->lr().setNotFound();
        else if(schedule.published_uuid()!=published_uuid)
            return this->lr().setUnauthorized();
        else
            return this->lr(scheduleTask.toWrapper());
    }

    ResultValue &ControllerShedule::send(const QUuid &published_uuid, const QUuid &customer_uuid, const QVariant&type, const QByteArray &to, const QByteArray &subject, const QByteArray &payload, const QVariant &attachment)
    {
        ScheduleGDao daoSchedule(this);
        Schedule schedule(this);

        Publisher publisher(this);
        publisher.set_uuid(published_uuid);
        PublisherGDao publisherDao(this);

        schedule.set_published_uuid(published_uuid);
        schedule.set_state(schedule.Wait);

        auto s_to=QString::fromUtf8(to).replace(qsl("+"),qsl_null).replace(qsl("-"),qsl_null).replace(qsl("("),qsl_null).replace(qsl(")"),qsl_null).replace(qsl(" "),qsl_null).trimmed().toUtf8();

        if(s_to.isEmpty())
            return this->lr().setValidation(qsl("Invalid 'to'"));
        else if(!publisherDao.reload(publisher))
            return this->lr().setNotFound();
        else if(!daoSchedule.insert(schedule))
            return this->lr();
        else{

            auto provider_type=TaskTypeMap.value(type.toString().trimmed().toLower());

            Q_DECLARE_VU;

            auto vvm=vu.clear()
                           .makeVVM(PublisherProviderM.publisher_uuid_field(), published_uuid)
                           .makeVVM(PublisherProviderM.provider_type_field(), provider_type)
                           .makeVVM(PublisherProviderM.enabled_field(), true)
                           .toVVM();

            Provider provider(this);
            ProviderGDao providerDao(this);
            PublisherProvider publisherProvider(this);
            PublisherProviderGDao publisherProviderDao(this);
            if(!publisherProviderDao.reload(publisherProvider, vvm))
                return this->lr().setNotImplemented(tr("Invalid publisherProvider: '%1', %2").arg(type.toString(),publisherProviderDao.lr().toString()));
            else if(publisherProvider.isEmptyPK())
                return this->lr().setNotImplemented(tr("Invalid publisherProvider record: '%1'").arg(type.toString()));
            else if(!providerDao.reload(provider, publisherProvider.provider_uuid()))
                return this->lr().setNotImplemented(tr("Invalid provider: '%1'").arg(type.toString()));
            else if(!provider.enabled())
                return this->lr().setNotImplemented(tr("Invalid provider disabled: '%1'").arg(provider.name()));
            else{

                const auto payload_title=publisher.title().trimmed().toUtf8();
                const auto payload_body=payload+qsl_key_return+payload_title;

                ScheduleTaskGDao daoTask(this);
                ScheduleTask task(this);
                task.set_schedule_uuid(schedule.uuid());
                task.set_published_uuid(published_uuid);
                task.set_published_provider_uuid(publisherProvider.uuid());
                task.set_type(publisherProvider.provider_type());
                task.set_to(s_to);
                task.set_subject(subject);
                task.set_customer_uuid(customer_uuid);
                task.set_payload(payload_body);
                task.set_attachment(vu.toByteArray(attachment));
                if(!daoTask.insert(task))
                    return this->lr();
                else if(!schedule.set_state(schedule.Sent))
                    return this->lr();
                else if(!daoSchedule.update(schedule))
                    return this->lr();
                else{
                    auto&instance=DispatcherPool::i();
                    if(!instance.isRunning())
                        sWarning()<<qsl("the engine service is not activated");
                    else{
                        auto setting=qvl()<<vu.toVariantObject(provider.settings())<<vu.toVariantObject(publisherProvider.settings());
                        qvh vBody;
                        vBody.insert(qsl_fy(vTask),task.toHash());
                        vBody.insert(qsl_fy(setting),setting);
                        emit instance.dispacher(task.uuid(), vBody);
                    }
                    return this->lr(schedule.toWrapper());
                }
            }

        }
        return this->lr();
    }

    ResultValue &ControllerShedule::stats()
    {
        Q_DECLARE_VU;
        return this->lr(vu.mMap(qsl("stats"),0).toHash());
    }

}
