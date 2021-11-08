#pragma once

#include "./qapr_consts.h"
#include "./qapr_global.h"
#include "./qorm_object_db.h"
#include "./qrpc_interface_record.h"
#include <QSqlDatabase>

namespace QApr {

//!
//! \brief The InterfaceBase class
//!base inicial criada para aplicacoes, contem metodos e verificacao e alguns utilitarios
class Q_APR_EXPORT InterfaceBase : public QRpc::QRPCInterfaceCheck
{
    Q_OBJECT
    Q_DECLARE_OBJECT()
    QORM_CONNECTION_SUPPORT
public:
    //!
    //! \brief InterfaceBase
    //! \param parent
    //!
    Q_INVOKABLE explicit InterfaceBase(QObject *parent = nullptr);

    //!
    //! \brief ~InterfaceBase
    //!
    Q_INVOKABLE ~InterfaceBase();

    QT_DEPRECATED_X(" trocar o uso por Q_DECLARE_VU;")
    virtual VariantUtil &vu();

    //!
    //! \brief check
    //! \return
    //!method de verificacao simples
    Q_INVOKABLE virtual QVariant check();

    //!
    //! \brief ping
    //! \return
    //!
    Q_INVOKABLE virtual QVariant ping();

    //!
    //! \brief fullCheck
    //! \return
    //!
    Q_INVOKABLE virtual QVariant fullCheck();

    //!
    //! \brief connectionsCheck
    //! \return
    //!
    Q_INVOKABLE virtual QVariant connectionsCheck();

    //!
    //! \brief businessCheck
    //! \return
    //!
    Q_INVOKABLE virtual QVariant businessCheck();


private:
    void *p = nullptr;
};

}
