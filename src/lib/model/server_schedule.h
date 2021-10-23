#pragma once

#include "./server_model.h"

namespace ServerService {

    class Schedule: public Model
    {
        Q_OBJECT
        QORM_MODEL(Schedule)
        QORM_DECLARE_TABLE(msg01aa,_,schedule)
    public:
        enum State{Wait=0, Error=1, Send=2, Sent=3, Canceled=4};
        Q_ENUM(State)
        QORM_DECLARE_PROPERTY(QUuid       , uuid            , uuidGenerator() )
        QORM_DECLARE_PROPERTY(QDateTime   , dt              , now()           )
        QORM_DECLARE_PROPERTY(QUuid       , published_uuid  , QUuid()         )
        QORM_DECLARE_PROPERTY(State       , state           , State::Wait     )

        QORM_DECLARE_WRAPPER_FIELD(,uuid,uuid)
        QORM_DECLARE_WRAPPER_FIELD(,state,state)
    public:
        QORM_MODEL_CONSTRUCTOR(Schedule, ServerService::Model)
    };
    QORM_DECLARE_DAO(Schedule)

}
