#pragma once

#include <QtReforce/QOrm>
#include <QtReforce/QApr>
#include <QSqlDatabase>

namespace ServerService {

class ServerInterface : public QApr::Interface{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ServerInterface(QObject *parent=nullptr);

    QUuid published_uuid;
    Q_INVOKABLE virtual bool authorization();

    static const QVariantHash &publishers();
    static const QVariantHash &providers();

    Q_INVOKABLE virtual bool requestBeforeInvoke();
};
}
