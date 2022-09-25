#pragma once

#include <QList>
#include <QtReforce/QStm>

#define DeclareProviderType(v)\
    enum v{dsFake=0, dsSms=1, dsMail=2, dsPushNotification=4, dsTelegram=8, dsWhatsApp=16}


DeclareProviderType(ProviderType);


static const QHash<QString,ProviderType> TaskTypeMap
    (
        {
            {qsl_number(dsMail), dsMail},
            {QT_STRINGIFY2(dsMail), dsMail},
            {QT_STRINGIFY2(dsmail), dsMail},
            {QT_STRINGIFY2(mail), dsMail},
            {QT_STRINGIFY2(email), dsMail},
            {QT_STRINGIFY2(e-mail), dsMail},

            {qsl_number(dsSms), dsSms},
            {QT_STRINGIFY2(dsSms), dsSms},
            {QT_STRINGIFY2(dssms), dsSms},
            {QT_STRINGIFY2(sms), dsSms},

            {qsl_number(dsPushNotification), dsPushNotification},
            {QT_STRINGIFY2(dsPushNotification), dsPushNotification},
            {QT_STRINGIFY2(dspushnotification), dsPushNotification},
            {QT_STRINGIFY2(pushnotification), dsPushNotification},

            {qsl_number(dsTelegram), dsTelegram},
            {QT_STRINGIFY2(dsTelegram), dsTelegram},
            {QT_STRINGIFY2(dstelegram), dsTelegram},
            {QT_STRINGIFY2(telegram), dsTelegram},

            {qsl_number(dsWhatsApp), dsWhatsApp},
            {QT_STRINGIFY2(dsWhatsApp), dsWhatsApp},
            {QT_STRINGIFY2(dswhatsapp), dsWhatsApp},
            {QT_STRINGIFY2(whatsapp), dsWhatsApp}
        } );

static const auto TaskTypeList=QList<ProviderType>()<<dsFake<<dsMail<<dsSms<<dsPushNotification<<dsTelegram<<dsWhatsApp;
