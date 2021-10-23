#pragma once

#include "./qapr_interface.h"
#include <QUuid>

namespace ServerService {

    class ServerInterface : public QApr::Interface{
        Q_OBJECT
    public:
        Q_INVOKABLE explicit ServerInterface(QObject *parent=nullptr);
        Q_INVOKABLE ~ServerInterface();
        QUuid published_uuid;
        Q_INVOKABLE virtual bool authorization();

        static const QVariantHash &publishers();
        static const QVariantHash &providers();

        Q_INVOKABLE virtual bool requestBeforeInvoke();
    };
}
