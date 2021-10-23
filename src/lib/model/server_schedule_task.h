#pragma once

#include "./server_model.h"

namespace ServerService {

    DeclareProviderType(ScheduleTaskType);

    class ScheduleTask: public Model
    {
        Q_OBJECT
        QORM_MODEL(ScheduleTask)
        QORM_DECLARE_TABLE(msg01ab,_,schedule_task)
    public:
        DeclareProviderType(ScheduleTaskType);
        Q_ENUM(ScheduleTaskType)

        enum State{Wait=0, Error=1, Sent=1, Canceled=2};
        Q_ENUM(State)

        QORM_DECLARE_PROPERTY(QUuid       , uuid                    , uuidGenerator()   )
        QORM_DECLARE_PROPERTY(QDateTime   , dt                      , now()             )
        QORM_DECLARE_PROPERTY(QUuid       , schedule_uuid           , QUuid()           )
        QORM_DECLARE_PROPERTY(QUuid       , published_uuid          , QUuid()           )
        QORM_DECLARE_PROPERTY(QUuid       , published_provider_uuid , QUuid()           )
        QORM_DECLARE_PROPERTY(QUuid       , customer_uuid           , QUuid()           )
        QORM_DECLARE_PROPERTY(int         , type                    , dsFake            )
        QORM_DECLARE_PROPERTY(QByteArray  , to                      , QByteArray()      )
        QORM_DECLARE_PROPERTY(QByteArray  , subject                 , QByteArray()      )
        QORM_DECLARE_PROPERTY(State       , state                   , State::Wait       )
        QORM_DECLARE_PROPERTY(QByteArray  , payload                 , QByteArray()      )
        QORM_DECLARE_PROPERTY(QByteArray  , attachment              , QByteArray()      )

        QORM_DECLARE_WRAPPER_FIELD(,uuid, uuid)
        QORM_DECLARE_WRAPPER_FIELD(,state, state)

    public:
        QORM_MODEL_CONSTRUCTOR(ScheduleTask, ServerService::Model)
    };
    QORM_DECLARE_DAO(ScheduleTask)
}
