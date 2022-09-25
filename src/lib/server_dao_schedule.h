#pragma once

#include <QHash>
#include <QMap>
#include <QUuid>
#include <QtReforce/QOrm>

namespace ServerService {

class DaoSchedule : public QOrm::Dao
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DaoSchedule(QObject *parent = nullptr);


    //!
    //! \brief tasks_count_total
    //! \param published_uuid
    //! \return
    //!
    ResultValue &tasks_count_total(const QUuid&published_uuid);

    //!
    //! \brief tasks_count_month
    //! \param published_uuid
    //! \param dt
    //! \return
    //!
    ResultValue &tasks_count_month(const QUuid&published_uuid, const QDate&dt);

    //!
    //! \brief tasks_count_day
    //! \param published_uuid
    //! \param dt
    //! \return
    //!
    ResultValue &tasks_count_day(const QUuid&published_uuid, const QDate&dt);


signals:

};

}
