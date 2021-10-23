#pragma once

#include "./server_dispatcher_service.h"

namespace ServerService {

class DispatcherServiceWhatsApp : public DispatcherService
{
    Q_OBJECT
public:
    DECLARE_DISPATCHER_CONSTRUCTOR(DispatcherServiceWhatsApp)
private:
};

}
