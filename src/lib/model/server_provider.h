#pragma once

#include "./server_model.h"

namespace ServerService {

    class Provider: public Model {
        Q_OBJECT
        QORM_MODEL(Provider)
        QORM_DECLARE_TABLE(msg00aaa,_,provider)
    public:

        QORM_DECLARE_PROPERTY(QUuid       , uuid      , uuidGenerator() )
        QORM_DECLARE_PROPERTY(QDateTime   , dt        , now()           )
        QORM_DECLARE_PROPERTY(QString     , name      , QString()       )
        QORM_DECLARE_PROPERTY(QByteArray  , settings  , QByteArray()    )
        QORM_DECLARE_PROPERTY(bool        , enabled   , false           )

    public:
        QORM_MODEL_CONSTRUCTOR(Provider, ServerService::Model)
    };

    QORM_DECLARE_DAO(Provider)

}
