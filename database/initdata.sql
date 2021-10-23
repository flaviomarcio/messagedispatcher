set search_path=public;
create extension if not exists "uuid-ossp";

insert into msg_v1.msg00aaa_provider
(
 msg00aaa_uuid
,msg00aaa_name
,msg00aaa_settings
,msg00aaa_enabled
)
values
(
     md5('0')::uuid
    ,'Fake'
    ,'{"enabled":true}'
    ,true
),
(
     md5('1')::uuid
    ,'ZENVIA'
    ,'{"protocol":"http","hostName":"api-rest.zenvia.com","method":"POST","port":80,"route":"services/send-sms","enabled":true}'
    ,true
),
(
     md5('2')::uuid
    ,'GMail'
    ,'{"protocol":"https","hostName":"smtp.gmail.com","method":"POST","port":465,"enabled":true}'
    ,true
),
(
     md5('3')::uuid
    ,'uhserver'
    ,'{"protocol":"https","hostName":"smtps.uhserver.com","method":"POST","port":465,"enabled":true}'
    ,true
)
on conflict(msg00aaa_uuid) do update set
     msg00aaa_name=excluded.msg00aaa_name
    ,msg00aaa_settings=excluded.msg00aaa_settings
    ,msg00aaa_enabled=excluded.msg00aaa_enabled
;

