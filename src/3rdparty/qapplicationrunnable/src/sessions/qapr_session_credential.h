#pragma once

#include <QUuid>
#include <QVariantHash>
#include "./qapr_global.h"
#include "./qstm_object.h"

namespace QApr {

class Q_APR_EXPORT SessionCredential : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Credentials
     * @param parent
     */
    Q_INVOKABLE explicit SessionCredential(QObject *parent = nullptr);

    /**
     * @brief ~Credentials
     */
    Q_INVOKABLE ~SessionCredential();

    /**
     * @brief toVariant
     * @return
     *
     * return QVariantHash with credential information
     */
    virtual QVariantHash toVariant()const;

    /**
     * @brief isValid
     * @return
     *
     * validate values SessionCredential
     */
    virtual bool isValid()const;


    /**
     * @brief permits
     * @return
     */
    virtual QVariantHash &permits() const;

    /**
     * @brief setPermits
     * @param permits
     */
    virtual SessionCredential &setPermits(const QVariantHash &permits);

    /**
     * @brief uuid
     * @return
     *
     * generic uuid for identification
     */
    virtual QUuid &uuid() const;

    /**
     * @brief setUuid
     * @param value
     */
    virtual SessionCredential &setUuid(const QUuid &value);

    /**
     * @brief domain_uuid
     * @return
     *
     * isolation level for systems
     */
    virtual QUuid domain_uuid()const;
    /**
     * @brief set_domain_uuid
     * @param uuid
     * @return
     *
     * set domain
     */
    virtual SessionCredential&set_domain_uuid(const QVariant &uuid);

    /**
     * @brief account_uuid
     * @return
     *
     * account identification
     */
    virtual QUuid account_uuid()const;

    /**
     * @brief set_account_uuid
     * @param uuid
     * @return
     *
     * set account_uuid
     */
    virtual SessionCredential&set_account_uuid(const QVariant &uuid);

    /**
     * @brief session_uuid
     * @return
     *
     * session identitication for account
     */
    virtual QUuid session_uuid()const;

    /**
     * @brief set_session_uuid
     * @param uuid
     * @return
     *
     * set session_uuid
     */
    virtual SessionCredential&set_session_uuid(const QVariant &uuid);

    /**
     * @brief service_uuid
     * @return
     *
     * service identification
     *
     */
    virtual QUuid service_uuid()const;
    /**
     * @brief set_service_uuid
     * @param uuid
     * @return
     *
     * set service_uuid
     */
    virtual SessionCredential&set_service_uuid(const QVariant &uuid);

    /**
     * @brief body
     * @return
     *
     * full body of SessionCredential
     */
    virtual QVariantHash&body()const;
    /**
     * @brief setBody
     * @param value
     * @return
     *
     * set body
     */
    virtual SessionCredential&setBody(const QVariantHash&value);

    /**
     * @brief profile
     * @return
     *
     * account body
     */
    virtual QVariant profile()const;

    /**
     * @brief setAccount
     * @param value
     * @return
     *
     * set account body
     */
    virtual SessionCredential&setProfile(const QVariant&value);

    /**
     * @brief session
     * @return
     *
     * session body of account
     */
    virtual QVariant session()const;

    /**
     * @brief setSession
     * @param value
     * @return
     *
     * set session body
     */
    virtual SessionCredential&setSession(const QVariant&value);

    /**
     * @brief token
     * @return
     *
     * token body
     */
    virtual QVariant token()const;

    /**
     * @brief setToken
     * @param value
     * @return
     *
     * set token payload
     */
    virtual SessionCredential&setToken(const QVariant&value);

private:
    void*p=nullptr;
};

}
