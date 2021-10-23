set search_path=public;
create extension if not exists "uuid-ossp";

insert into msg_v1.msg00baa_provider
(
 msg00baa_uuid
,msg00baa_name
,msg00baa_token
,msg00baa_token_type
,msg00baa_token_exp
,msg00baa_token_iat
,msg00baa_protocol
,msg00baa_hostname
,msg00baa_path
,msg00baa_port
,msg00baa_method
,msg00baa_username
,msg00baa_password
,msg00baa_enabled
)
values
(
 '6b9c530f-cdc8-44f7-beb8-1227a7b4c94b'
,'ZENVIA'
,''
,0--jwt
,'2030-01-01'
,now()
,'https'
,'api-rest.zenvia.com'
,'services/send-sms'
,80
,1--0--GET, --1-POST
,'sadickjorg.smsonline'
,'pJAbT45ALK'
,true
)
on conflict(msg00baa_uuid) do nothing;

insert into msg_v1.msg00ba_publisher(msg00ba_uuid, msg00ba_name, msg00ba_title, msg00ba_enabled)
values
 ('4c8d2583-9033-4e3a-b4ef-8b785d460e51','magma','Magma tecnologia',true)
,('9ac80935-cf66-41a5-ab0a-18143bbf684e','Dom','Clinica Dom',true)
,('ee092eab-a956-407a-a187-ecaa631c06ae','Cantinho Doce','Cantinho Doce',true)
,('fe134b67-119f-428c-b567-b12d7aa0e554','Dicor','Dicor',true)
,('736c61eb-8fe4-43a0-81db-4a840f13915d','Up Vestibulares','Up Vestibulares',true)
on conflict(msg00ba_uuid) do nothing;
