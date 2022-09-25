#include "./server_base_dao.h"

namespace ServerService {

DaoBase::DaoBase(QObject *parent) : QOrm::Dao(parent)
{

}

}
