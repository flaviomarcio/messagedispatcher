#pragma once

#include <QList>
#include "./qstm_macro.h"

#define DeclareProviderType(v)\
    enum v{dsFake=0, dsSms=1, dsMail=2, dsPushNotification=4, dsTelegram=8, dsWhatsApp=16}


DeclareProviderType(ProviderType);


static const QHash<QString,ProviderType> TaskTypeMap
    (
        {
            {qsl_number(dsMail), dsMail},
            {qsl_fy(dsMail), dsMail},
            {qsl_fy(dsmail), dsMail},
            {qsl_fy(mail), dsMail},
            {qsl_fy(email), dsMail},
            {qsl_fy(e-mail), dsMail},

            {qsl_number(dsSms), dsSms},
            {qsl_fy(dsSms), dsSms},
            {qsl_fy(dssms), dsSms},
            {qsl_fy(sms), dsSms},

            {qsl_number(dsPushNotification), dsPushNotification},
            {qsl_fy(dsPushNotification), dsPushNotification},
            {qsl_fy(dspushnotification), dsPushNotification},
            {qsl_fy(pushnotification), dsPushNotification},

            {qsl_number(dsTelegram), dsTelegram},
            {qsl_fy(dsTelegram), dsTelegram},
            {qsl_fy(dstelegram), dsTelegram},
            {qsl_fy(telegram), dsTelegram},

            {qsl_number(dsWhatsApp), dsWhatsApp},
            {qsl_fy(dsWhatsApp), dsWhatsApp},
            {qsl_fy(dswhatsapp), dsWhatsApp},
            {qsl_fy(whatsapp), dsWhatsApp}
        } );

static const auto TaskTypeList=QList<ProviderType>()<<dsFake<<dsMail<<dsSms<<dsPushNotification<<dsTelegram<<dsWhatsApp;
