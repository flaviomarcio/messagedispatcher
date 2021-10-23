#pragma once

#include "./server_model.h"

namespace ServerService {

    class PublisherProvider: public Model {
        Q_OBJECT
        QORM_MODEL(PublisherProvider)
        QORM_DECLARE_TABLE(msg00bac,_,publisher_provider)
    public:
        QORM_DECLARE_PROPERTY(QUuid       , uuid            , QUuid()           )
        QORM_DECLARE_PROPERTY(QUuid       , publisher_uuid  , QUuid()           )
        QORM_DECLARE_PROPERTY(QUuid       , provider_uuid   , QUuid()           )
        QORM_DECLARE_PROPERTY(int         , provider_type   , 0                 )
        QORM_DECLARE_PROPERTY(QByteArray  , settings        , QByteArray()      )
        QORM_DECLARE_PROPERTY(bool        , enabled         , false             )

    public:
        QORM_MODEL_CONSTRUCTOR(PublisherProvider, ServerService::Model)
    };

    QORM_DECLARE_DAO(PublisherProvider)

}
