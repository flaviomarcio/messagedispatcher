#pragma once

#include <QHash>
#include <QMap>
#include <QUuid>
#include <QtReforce/QOrm>

namespace ServerService {

class DaoBase : public QOrm::Dao
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DaoBase(QObject *parent = nullptr);
signals:

};

}
