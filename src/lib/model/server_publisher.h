#pragma once

#include "./server_model.h"

namespace ServerService {

    class Publisher: public Model
    {
        Q_OBJECT
        QORM_MODEL(Publisher)
        QORM_DECLARE_TABLE(msg00baa,_,publisher)
    public:
        QORM_DECLARE_PROPERTY(QUuid         , uuid            , uuidGenerator() )
        QORM_DECLARE_PROPERTY(QDateTime     , dt              , now()           )
        QORM_DECLARE_PROPERTY(QString       , name            , QString()       )
        QORM_DECLARE_PROPERTY(QString       , title           , QString()       )
        QORM_DECLARE_PROPERTY(QString       , token_md5       , QString()       )
        QORM_DECLARE_PROPERTY(bool          , enabled         , false           )
    public:
        QORM_MODEL_CONSTRUCTOR(Publisher, ServerService::Model)
    };
    QORM_DECLARE_DAO(Publisher)

}
