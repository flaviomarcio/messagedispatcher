#pragma once

#include <QObject>
#include <QThread>
#include <QList>
#include "./server_types.h"

namespace ServerService {

class DispatcherPool : public QThread
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DispatcherPool(QObject *parent = nullptr);
public:
    static DispatcherPool&i();
    void run() override;
private:
    void*p=nullptr;
signals:
    void dispacher(const QUuid&uuid, const QVariant&v);
};

}
