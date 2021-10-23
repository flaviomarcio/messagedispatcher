#pragma once

#include "./server_dispatcher_service.h"

namespace ServerService {

class DispatcherServiceSMS : public DispatcherService
{
    Q_OBJECT
public:
    /**
     * @brief DispatcherServiceSMS
     * @param parent
     */
    DECLARE_DISPATCHER_CONSTRUCTOR(DispatcherServiceSMS)

    /**
     * @brief received
     * @param settings
     * @param uuid
     * @param v
     */
    virtual void received(const QUuid &uuid, const QVariant&v);
};

}
