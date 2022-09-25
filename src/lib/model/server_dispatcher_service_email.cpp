#include "./server_dispatcher_service_email.h"
#include "./server_publisher.h"
#include "./server_schedule_task.h"
#include "./SimpleMail"
#include <QtReforce/QRpc>
#include <QtReforce/QApr>

using namespace SimpleMail;

namespace ServerService {

struct ConstsDispatcherMail{
    QRpc::ServiceSetting setting;
    void init(){
        auto&manager=QApr::Application::i().manager();
        setting=manager.setting(QStringLiteral("dispatcher-email"));
    }
};

Q_GLOBAL_STATIC(ConstsDispatcherMail, __constsDispatcherMail);
static auto&constsDispatcherMail=*__constsDispatcherMail;

void DispatcherServiceEMail::received(const QUuid &uuid, const QVariant &v)
{
    QRpc::ServiceSetting settings(this);
    DispatcherServiceMessage msg;
    {
        auto vHash=v.toHash();
        settings+=vHash[QT_STRINGIFY2(setting)];
        msg+=vHash[QT_STRINGIFY2(setting)];
        msg+=vHash[QT_STRINGIFY2(vTask)];
    }

    if(!settings.isValid())
        sWarning()<<QStringLiteral("the setting mail engine is not valid");
    else{
        Sender smtp(settings.hostName(), settings.port(), Sender::SslConnection);
        smtp.setConnectionTimeout(60000);
        smtp.setUser(msg.username);
        smtp.setPassword(msg.password);
        MimeMessage message;

        EmailAddress sender(msg.from, msg.subject);
        message.setSender(sender);

        EmailAddress to(msg.to, msg.toName);
        message.addTo(to);
        message.setSubject(msg.subject);

        if(!msg.message.isEmpty()){
            auto text=new MimeText;
            text->setText(msg.message);
            message.addPart(text);
        }

        for(auto&v:msg.attachment){
            auto map=v.toHash();
            auto name=map.value(QT_STRINGIFY2(name)).toString().trimmed();
            auto body=QByteArray::fromHex(map.value(QT_STRINGIFY2(body)).toByteArray()).trimmed();
            if(name.isEmpty() && body.isEmpty())
                continue;
            else{
                auto attachment= new MimeAttachment(body, name);
                message.addPart(attachment);
            }
        }

        VariantUtil vu;
        if (!smtp.sendMail(message)){
            sWarning()<<QStringLiteral("the mail was not sent:")<<smtp.lastError();
            sWarning()<<QStringLiteral("   setting:")<<vu.toStr(settings.toHash());
            emit request_error(uuid, smtp.lastError());
        }
        else{
            sInfo()<<QStringLiteral("the mail has been sended");
            emit request_success(uuid, QVariant());
        }

    }
}


}
