#pragma once

#include "./server_dispatcher_service.h"

namespace ServerService {

class DispatcherServiceEMail : public DispatcherService
{
    Q_OBJECT
public:
    DECLARE_DISPATCHER_CONSTRUCTOR(DispatcherServiceEMail)

    /**
     * @brief received
     * @param vSettings
     * @param uuid
     * @param v
     */
    virtual void received(const QUuid &uuid, const QVariant&v);
};

}
