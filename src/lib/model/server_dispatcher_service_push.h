#pragma once

#include "./server_dispatcher_service.h"

namespace ServerService {

class DispatcherServicePush : public DispatcherService
{
    Q_OBJECT
public:
    DECLARE_DISPATCHER_CONSTRUCTOR(DispatcherServicePush)

    /**
     * @brief received
     * @param settings
     * @param uuid
     * @param v
     */
    virtual void received(const QUuid &uuid, const QVariant&v);

};

}
