set search_path=public;
create extension if not exists "uuid-ossp";

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

truncate table msg_v1.msg00baa_publisher cascade;
insert into msg_v1.msg00baa_publisher(msg00baa_uuid, msg00baa_token_md5, msg00baa_name, msg00baa_title, msg00baa_enabled)
values
 (md5('1')::uuid, md5('acl_account_token')::uuid ,'magma','Magma tecnologia',true)
on conflict(msg00baa_uuid) do update set msg00baa_token_md5=excluded.msg00baa_token_md5;


insert into msg_v1.msg00bad_publisher_token
(
     msg00bad_uuid
    ,msg00bad_publisher_uuid
    ,msg00bad_name
    ,msg00bad_token_md5
    ,msg00bad_enabled
)
values
(
     md5('0')::uuid
    ,md5('1')::uuid
    ,'Token'
    ,md5('acl_managment_token')::uuid
    ,true
)
on conflict(msg00bad_uuid) do nothing;


insert into msg_v1.msg00bac_publisher_provider
(
     msg00bac_uuid
    ,msg00bac_publisher_uuid
    ,msg00bac_provider_uuid
    ,msg00bac_provider_type
    ,msg00bac_settings
    ,msg00bac_enabled
)
values
(
     md5('0')::uuid
    ,md5('1')::uuid
    ,md5('0')::uuid
    ,0--dsFake
    ,'{"headers":{}}'
    ,true
),
(
     md5('1')::uuid
    ,md5('1')::uuid
    ,md5('1')::uuid
    ,1--dsSms
    ,'{"headers":{"authorization":"Basic c2FkaWNram9yZy5zbXNvbmxpbmU6cEpBYlQ0NUFMSw==","Accept":"application/json","Content-Type":"application/json"}}'
    ,true
),
(
     md5('2')::uuid
    ,md5('1')::uuid
    ,md5('2')::uuid
    ,2--dsMail
    ,'{"userName":"developer@magma-ma.com.br","password":"4NC7%Sb="}'
    ,true
),
(
     md5('3')::uuid
    ,md5('1')::uuid
    ,md5('0')::uuid--fake
    ,4--
    ,''
    ,true
),
(
     md5('4')::uuid
    ,md5('1')::uuid
    ,md5('0')::uuid--fake
    ,8--
    ,''
    ,true
),
(
     md5('5')::uuid
    ,md5('1')::uuid
    ,md5('0')::uuid--fake
    ,16--
    ,''
    ,true
)
on conflict(msg00bac_uuid) do update set
     msg00bac_publisher_uuid=excluded.msg00bac_publisher_uuid
    ,msg00bac_provider_uuid=excluded.msg00bac_provider_uuid
    ,msg00bac_settings=excluded.msg00bac_settings
    ,msg00bac_enabled=excluded.msg00bac_enabled
;
