set search_path=public;
create extension if not exists "uuid-ossp";

create schema if not exists msg_v1;

create table if not exists msg_v1.msg00aaa_provider(msg00aaa_uuid uuid not null);
alter table msg_v1.msg00aaa_provider add if not exists msg00aaa_dt timestamp not null default now();
alter table msg_v1.msg00aaa_provider add if not exists msg00aaa_name varchar(100) not null;
alter table msg_v1.msg00aaa_provider add if not exists msg00aaa_settings text not null default '';
alter table msg_v1.msg00aaa_provider add if not exists msg00aaa_enabled bool not null;

create table if not exists msg_v1.msg00baa_publisher (msg00baa_uuid uuid not null);
alter table msg_v1.msg00baa_publisher add if not exists msg00baa_dt timestamp not null default now();
alter table msg_v1.msg00baa_publisher add if not exists msg00baa_name varchar(100) not null;
alter table msg_v1.msg00baa_publisher add if not exists msg00baa_title varchar(100) not null;
alter table msg_v1.msg00baa_publisher add if not exists msg00baa_token_md5 varchar(100) not null default '';
alter table msg_v1.msg00baa_publisher add if not exists msg00baa_enabled bool not null;

create table if not exists msg_v1.msg00bac_publisher_provider(msg00bac_uuid uuid not null);
alter table msg_v1.msg00bac_publisher_provider add if not exists msg00bac_publisher_uuid uuid not null;
alter table msg_v1.msg00bac_publisher_provider add if not exists msg00bac_provider_uuid uuid not null;
alter table msg_v1.msg00bac_publisher_provider add if not exists msg00bac_provider_type int not null;
alter table msg_v1.msg00bac_publisher_provider add if not exists msg00bac_settings text not null default '';
alter table msg_v1.msg00bac_publisher_provider add if not exists msg00bac_enabled bool not null;

create table if not exists msg_v1.msg00bad_publisher_token(msg00bad_uuid uuid not null);
alter table msg_v1.msg00bad_publisher_token add if not exists msg00bad_publisher_uuid uuid not null;
alter table msg_v1.msg00bad_publisher_token add if not exists msg00bad_name varchar(50) not null default '';
alter table msg_v1.msg00bad_publisher_token add if not exists msg00bad_token_md5 varchar(50) not null default '';
alter table msg_v1.msg00bad_publisher_token add if not exists msg00bad_enabled bool not null;

create table if not exists msg_v1.msg01aa_schedule(msg01aa_uuid uuid not null);
alter table msg_v1.msg01aa_schedule add if not exists msg01aa_dt timestamp not null default now();
alter table msg_v1.msg01aa_schedule add if not exists msg01aa_published_uuid uuid not null;
alter table msg_v1.msg01aa_schedule add if not exists msg01aa_state int not null;

create table if not exists msg_v1.msg01ab_schedule_task(msg01ab_uuid uuid not null);
alter table msg_v1.msg01ab_schedule_task add if not exists msg01ab_dt timestamp not null default now();
alter table msg_v1.msg01ab_schedule_task add if not exists msg01ab_schedule_uuid uuid not null;
alter table msg_v1.msg01ab_schedule_task add if not exists msg01ab_published_uuid uuid;
alter table msg_v1.msg01ab_schedule_task add if not exists msg01ab_published_provider_uuid uuid not null;
alter table msg_v1.msg01ab_schedule_task add if not exists msg01ab_customer_uuid uuid;
alter table msg_v1.msg01ab_schedule_task add if not exists msg01ab_type int not null;
alter table msg_v1.msg01ab_schedule_task add if not exists msg01ab_state int not null;
alter table msg_v1.msg01ab_schedule_task add if not exists msg01ab_to varchar(50)not null;
alter table msg_v1.msg01ab_schedule_task add if not exists msg01ab_subject varchar(50)not null default '';
alter table msg_v1.msg01ab_schedule_task add if not exists msg01ab_payload varchar(1000)not null default '';
alter table msg_v1.msg01ab_schedule_task add if not exists msg01ab_attachment text not null default '';

drop table if exists msg_v1.msg01ac_schedule_task_state cascade;
