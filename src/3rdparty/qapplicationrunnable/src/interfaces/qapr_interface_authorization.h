#pragma once

#include "./qapr_interface_database.h"
#include "./qapr_session.h"

namespace QApr {

//!
//! \brief The InterfaceAuthorization class
//!camada criada para implementacao a camada de autorizacao
class Q_APR_EXPORT InterfaceAuthorization : public QApr::InterfaceDatabase
{
    Q_OBJECT
    Q_DECLARE_OBJECT()
public:
    //!
    //! \brief InterfaceAuthorization
    //! \param parent
    //!
    Q_INVOKABLE explicit InterfaceAuthorization(QObject *parent = nullptr);

    //!
    //! \brief ~InterfaceAuthorization
    //!
    Q_INVOKABLE ~InterfaceAuthorization();

    //!
    //! \brief sessionObject
    //! \return
    //!
    virtual QApr::Session&sessionObject();

    //!
    //! \brief credential
    //! \return
    //!
    virtual const QApr::SessionCredential&credential();

    QT_DEPRECATED_X("Use this->sessionObject()")
    virtual const QUuid domain_uuid();


    QT_DEPRECATED_X("Use this->sessionObject()")
    virtual const QUuid service_uuid();


    QT_DEPRECATED_X("Use this->sessionObject()")
    virtual const QUuid account_uuid();


    QT_DEPRECATED_X("Use this->sessionObject()")
    virtual const QUuid session_uuid();


    QT_DEPRECATED_X("Use this->sessionObject()")
    virtual const QVariant token() const;

private:
    void *p = nullptr;
};

}
