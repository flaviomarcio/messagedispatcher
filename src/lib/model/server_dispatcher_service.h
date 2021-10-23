#pragma once

#include "./qrpc_service_thread.h"
#include "./qstm_util_variant.h"

namespace ServerService {

struct DispatcherServiceMessage{
public:
    QString username;
    QString password;
    QString from;
    QString to;
    QString toName;
    QString id;
    QString subject;
    QString message;
    QVariant aggregateId;
    QVariant flashMessage=false;
    QVariant schedule;
    QVariant callbackOption;
    QVariantList attachment;
    explicit DispatcherServiceMessage(){
    }
    explicit DispatcherServiceMessage(const QVariantHash&v){
        this->set(v);
    }

    DispatcherServiceMessage&operator+=(const QVariant&v){
        QVariantList vv;
        if(v.type()==v.List || v.type()==v.StringList)
            vv=v.toList();
        else
            vv<<v;
        for(auto&v:vv)
            this->set(v.toHash());
        return*this;
    }

    DispatcherServiceMessage&set(const QVariantHash&vBody){
        VariantUtil vu;
        if(vBody.contains(qsl_fy(userName)))
            this->username=vBody.value(qsl_fy(userName)).toString();
        else if(vBody.contains(qsl_fy(username)))
            this->username=vBody.value(qsl_fy(username)).toString();

        if(vBody.contains(qsl_fy(password)))
            this->password=vBody.value(qsl_fy(password)).toString();
        else if(vBody.contains(qsl_fy(passWord)))
            this->password=vBody.value(qsl_fy(passWord)).toString();

        if(vBody.contains(qsl_fy(from)))
            this->from=vBody.value(qsl_fy(from)).toString();
        else if(vBody.contains(qsl_fy(userName)))
            this->from=vBody.value(qsl_fy(userName)).toString();
        else if(vBody.contains(qsl_fy(username)))
            this->from=vBody.value(qsl_fy(username)).toString();

        if(vBody.contains(qsl_fy(to)))
            this->to=vBody.value(qsl_fy(to)).toString();

        if(vBody.contains(qsl_fy(toName)))
            this->toName=vBody.value(qsl_fy(toName)).toString();

        if(vBody.contains(qsl_fy(id)))
            this->id=vBody.value(qsl_fy(id)).toString();

        if(vBody.contains(qsl_fy(subject)))
            this->subject=vBody.value(qsl_fy(subject)).toString();
        else if(vBody.contains(qsl_fy(title)))
            this->subject=vBody.value(qsl_fy(title)).toString();

        if(vBody.contains(qsl_fy(message)))
            this->message=vBody.value(qsl_fy(message)).toString();
        else if(vBody.contains(qsl_fy(payload)))
            this->message=vBody.value(qsl_fy(payload)).toString();

        this->schedule=QVariant();
        this->aggregateId=QVariant();
        this->flashMessage=false;
        this->schedule=QVariant();
        this->callbackOption=QVariant();

        if(vBody.contains(qsl_fy(attachment)))
            this->attachment=vu.toList(vBody.value(qsl_fy(attachment)));
        return*this;
    }
};


#define DECLARE_DISPATCHER_CONSTRUCTOR(className)\
Q_INVOKABLE explicit className(const QVariant&setting, QObject *parent = nullptr):DispatcherService(setting, parent){}\
Q_INVOKABLE ~className(){}

class DispatcherService : public QRpc::ServiceThread
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DispatcherService(const QVariant&setting, QObject *parent = nullptr);
    Q_INVOKABLE ~DispatcherService();

    /**
     * @brief received
     * @param uuid
     * @param v
     *
     * programe aqui o dispatcher
     */
    virtual void received(const QUuid &uuid, const QVariant&v);

    /**
     * @brief settings
     * @return
     */
    virtual const QVariantHash &settings() const;
    virtual void setSettings(const QVariantHash &value);

signals:
    void settingsChanged();

private:
    void*p=nullptr;
};

}
