#pragma once

#include <QtReforce/QRpc>
#include <QtReforce/QStm>

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
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        if(v.typeId()==QMetaType::QVariantList || v.typeId()==QMetaType::QStringList)
#else
        if(v.type()==QVariant::List || v.type()==QVariant::StringList)
#endif

            vv=v.toList();
        else
            vv<<v;
        for(auto&v:vv)
            this->set(v.toHash());
        return*this;
    }

    DispatcherServiceMessage&set(const QVariantHash&vBody){
        VariantUtil vu;
        if(vBody.contains(QT_STRINGIFY2(userName)))
            this->username=vBody.value(QT_STRINGIFY2(userName)).toString();
        else if(vBody.contains(QT_STRINGIFY2(username)))
            this->username=vBody.value(QT_STRINGIFY2(username)).toString();

        if(vBody.contains(QT_STRINGIFY2(password)))
            this->password=vBody.value(QT_STRINGIFY2(password)).toString();
        else if(vBody.contains(QT_STRINGIFY2(passWord)))
            this->password=vBody.value(QT_STRINGIFY2(passWord)).toString();

        if(vBody.contains(QT_STRINGIFY2(from)))
            this->from=vBody.value(QT_STRINGIFY2(from)).toString();
        else if(vBody.contains(QT_STRINGIFY2(userName)))
            this->from=vBody.value(QT_STRINGIFY2(userName)).toString();
        else if(vBody.contains(QT_STRINGIFY2(username)))
            this->from=vBody.value(QT_STRINGIFY2(username)).toString();

        if(vBody.contains(QT_STRINGIFY2(to)))
            this->to=vBody.value(QT_STRINGIFY2(to)).toString();

        if(vBody.contains(QT_STRINGIFY2(toName)))
            this->toName=vBody.value(QT_STRINGIFY2(toName)).toString();

        if(vBody.contains(QT_STRINGIFY2(id)))
            this->id=vBody.value(QT_STRINGIFY2(id)).toString();

        if(vBody.contains(QT_STRINGIFY2(subject)))
            this->subject=vBody.value(QT_STRINGIFY2(subject)).toString();
        else if(vBody.contains(QT_STRINGIFY2(title)))
            this->subject=vBody.value(QT_STRINGIFY2(title)).toString();

        if(vBody.contains(QT_STRINGIFY2(message)))
            this->message=vBody.value(QT_STRINGIFY2(message)).toString();
        else if(vBody.contains(QT_STRINGIFY2(payload)))
            this->message=vBody.value(QT_STRINGIFY2(payload)).toString();

        this->schedule=QVariant();
        this->aggregateId=QVariant();
        this->flashMessage=false;
        this->schedule=QVariant();
        this->callbackOption=QVariant();

        if(vBody.contains(QT_STRINGIFY2(attachment)))
            this->attachment=vu.toList(vBody.value(QT_STRINGIFY2(attachment)));
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
