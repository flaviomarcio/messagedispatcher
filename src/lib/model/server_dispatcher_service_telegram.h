#pragma once

#include "./server_dispatcher_service.h"

namespace ServerService {

class DispatcherServiceTelegram : public DispatcherService
{
    Q_OBJECT
public:
    DECLARE_DISPATCHER_CONSTRUCTOR(DispatcherServiceTelegram)
private:
};

}
