set search_path=public;
create extension if not exists "uuid-ossp";

drop schema if exists msg_v1 cascade;
create schema if not exists msg_v1;

drop table if exists msg_v1.msg00baa_provider cascade;
create table msg_v1.msg00baa_provider(
 msg00baa_uuid uuid not null
,msg00baa_dt timestamp not null default now()
,msg00baa_name varchar(100) not null
,msg00baa_token text not null
,msg00baa_token_type int not null
,msg00baa_token_exp timestamp not null
,msg00baa_token_iat timestamp not null
,msg00baa_protocol varchar(10) not null
,msg00baa_hostname varchar(100) not null
,msg00baa_username varchar(50) not null
,msg00baa_password varchar(50) not null
,msg00baa_port int not null
,msg00baa_path varchar(100) not null
,msg00baa_method int not null
,msg00baa_enabled bool not null
,constraint pk_msg00baa primary key(msg00baa_uuid)
);
create unique index unq_msg00baa_name on msg_v1.msg00baa_provider(msg00baa_name);

drop table if exists msg_v1.msg00ba_publisher cascade;
create table msg_v1.msg00ba_publisher(
 msg00ba_uuid uuid not null
,msg00ba_dt timestamp not null default now()
,msg00ba_name varchar(100) not NULL
,msg00ba_title varchar(100) not null
,msg00ba_enabled bool not null
,constraint pk_msg00ba primary key(msg00ba_uuid)
);
create unique index unq_msg00ba_name on msg_v1.msg00ba_publisher(msg00ba_name);


drop table if exists msg_v1.msg01aa_schedule cascade;
create table msg_v1.msg01aa_schedule(
 msg01aa_uuid uuid not null
,msg01aa_dt timestamp not null default now()
,msg01aa_published_uuid uuid not null
,msg01aa_state int not null
,constraint pk_msg01aa primary key(msg01aa_uuid)
);


drop table if exists msg_v1.msg01ab_schedule_task cascade;
create table msg_v1.msg01ab_schedule_task(
 msg01ab_uuid uuid not null
,msg01ab_dt timestamp not null default now()
,msg01ab_schedule_uuid uuid not null
,msg01ab_published_uuid uuid --not null
,msg01ab_customer_uuid uuid --not null
,msg01ab_type int not null
,msg01ab_state int not null
,msg01ab_to varchar(50)not null
,msg01ab_payload varchar(1000)not null
,constraint pk_msg01ab primary key(msg01ab_uuid)
,constraint fk_msg01ab_schedule_uuid foreign key (msg01ab_schedule_uuid) references msg_v1.msg01aa_schedule(msg01aa_uuid)
);

drop table if exists msg_v1.msg01ac_schedule_task_state cascade;
create table msg_v1.msg01ac_schedule_task_state(
 msg01ac_uuid uuid not null
,msg01ac_dt timestamp not null default now()
,msg01ac_task_uuid uuid --not null
,msg01ac_provider_uuid uuid --not null
,msg01ac_state int not null
,msg01ac_output int not null
,constraint pk_msg01ac primary key(msg01ac_uuid)
,constraint fk_msg01ac_task_uuid foreign key (msg01ac_task_uuid) references msg_v1.msg01ab_schedule_task(msg01ab_uuid)
,constraint fk_msg01ac_provider_uuid foreign key (msg01ac_provider_uuid) references msg_v1.msg00baa_provider(msg00baa_uuid)
);
