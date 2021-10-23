#ifndef SERVERSERVICE_DAOBASE_H
#define SERVERSERVICE_DAOBASE_H

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

} // namespace ServerService

#endif // SERVERSERVICE_DAOBASE_H
