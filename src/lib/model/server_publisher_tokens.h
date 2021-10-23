#pragma once

#include "./server_model.h"

namespace ServerService {

    class PublisherToken: public Model {
        Q_OBJECT
        QORM_MODEL(PublisherToken)
        QORM_DECLARE_TABLE(msg00bad,_,publisher_token)
    public:
        QORM_DECLARE_PROPERTY(QUuid       , uuid            , QUuid()           )
        QORM_DECLARE_PROPERTY(QUuid       , publisher_uuid  , QUuid()           )
        QORM_DECLARE_PROPERTY(QByteArray  , name            , QByteArray()      )
        QORM_DECLARE_PROPERTY(QByteArray  , token_md5       , QByteArray()      )
        QORM_DECLARE_PROPERTY(bool        , enabled         , false             )

    public:
        QORM_MODEL_CONSTRUCTOR(PublisherToken, ServerService::Model)
    };

    QORM_DECLARE_DAO(PublisherToken)

}
