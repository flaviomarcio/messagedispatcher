#include "./server_base_controller.h"
#include <QTranslator>

namespace ServerService {

ControllerBase::ControllerBase(QObject *parent) : QOrm::Controller(parent)
{

}

ControllerBase::~ControllerBase()
{

}

}
