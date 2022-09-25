#pragma once

#include <QHash>
#include <QMap>
#include <QUuid>
#include <QtReforce/QOrm>

namespace ServerService {

class ControllerBase : public QOrm::Controller
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ControllerBase(QObject *parent = nullptr);
};

}
