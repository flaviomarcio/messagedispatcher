#pragma once

#include <QHash>
#include <QMap>
#include <QUuid>
#include "./server_model.h"

#include "./qorm_controller.h"

namespace ServerService {

class ControllerBase : public QOrm::Controller
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ControllerBase(QObject *parent = nullptr);
    Q_INVOKABLE ~ControllerBase();
};

}
