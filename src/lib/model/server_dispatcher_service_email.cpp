#include "./server_dispatcher_service_email.h"
#include "./qapr_application.h"
#include "./server_publisher.h"
#include "./server_schedule_task.h"
#include "./qrpc_request.h"
#include "./qapr_application.h"

#include "./SimpleMail"
using namespace SimpleMail;

namespace ServerService {

struct ConstsDispatcherMail{
    QRpc::ServiceSetting setting;
    void init(){
        auto&manager=QApr::Application::instance().manager();
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
        settings+=vHash[qsl_fy(setting)];
        msg+=vHash[qsl_fy(setting)];
        msg+=vHash[qsl_fy(vTask)];
    }

    if(!settings.isValid())
        sWarning()<<qsl("the setting mail engine is not valid");
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
            auto name=map.value(qsl_fy(name)).toString().trimmed();
            auto body=QByteArray::fromHex(map.value(qsl_fy(body)).toByteArray()).trimmed();
            if(name.isEmpty() && body.isEmpty())
                continue;
            else{
                auto attachment= new MimeAttachment(body, name);
                message.addPart(attachment);
            }
        }

        VariantUtil vu;
        if (!smtp.sendMail(message)){
            sWarning()<<qsl("the mail was not sent:")<<smtp.lastError();
            sWarning()<<qsl("   setting:")<<vu.toStr(settings.toHash());
            emit request_error(uuid, smtp.lastError());
        }
        else{
            sInfo()<<qsl("the mail has been sended");
            emit request_success(uuid, QVariant());
        }

    }
}


}
