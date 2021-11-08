#pragma once

#include <QHash>
#include <QMap>
#include <QUuid>
#include "./server_model.h"

#include "./qorm_dao.h"

namespace ServerService {

class DaoBase : public QOrm::Dao
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DaoBase(QObject *parent = nullptr);
    Q_INVOKABLE ~DaoBase();

signals:

};

}
