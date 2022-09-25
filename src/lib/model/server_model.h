#pragma once

#include <QtReforce/QOrm>

namespace ServerService {

class Q_ORM_EXPORT Model : public QOrm::Model
{
    Q_OBJECT
public:
    QORM_MODEL(Model)
    QORM_DECLARE_TABLE_SCHEMA(msg_v1)
    QORM_DECLARE_TABLE_PRIMARY_KEY_NON_AUTO()
    QORM_DECLARE_TABLE_PRIMARY_KEY(uuid)
    QORM_DECLARE_TABLE_SEQUENCE()
public:
    QORM_MODEL_CONSTRUCTOR(Model, QOrm::Model)
};

}
