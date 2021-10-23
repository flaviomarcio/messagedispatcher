set search_path=public;
create extension if not exists "uuid-ossp";

create schema if not exists msg_v1;

alter table msg_v1.msg00aaa_provider add constraint pk_msg00aaa primary key(msg00aaa_uuid);
alter table msg_v1.msg00baa_publisher add constraint pk_msg00ba primary key(msg00baa_uuid);

alter table msg_v1.msg00bac_publisher_provider add constraint pk_msg00ac primary key(msg00bac_uuid);
alter table msg_v1.msg00bac_publisher_provider add constraint ck_msg00bac_provider_type check(msg00bac_provider_type>=0);
alter table msg_v1.msg00bac_publisher_provider add constraint fk_msg00bac_publisher_uuid foreign key (msg00bac_publisher_uuid) references msg_v1.msg00baa_publisher(msg00baa_uuid);
alter table msg_v1.msg00bac_publisher_provider add constraint fk_msg00bac_provider_uuid foreign key (msg00bac_provider_uuid) references msg_v1.msg00aaa_provider(msg00aaa_uuid);

alter table msg_v1.msg00bad_publisher_token add constraint pk_msg00bad primary key(msg00bad_uuid);
alter table msg_v1.msg00bad_publisher_token add constraint fk_msg00bad_publisher_uuid foreign key (msg00bad_publisher_uuid) references msg_v1.msg00baa_publisher(msg00baa_uuid);

alter table msg_v1.msg01aa_schedule add constraint pk_msg01aa primary key(msg01aa_uuid);

alter table msg_v1.msg01ab_schedule_task add constraint pk_msg01ab primary key(msg01ab_uuid);
alter table msg_v1.msg01ab_schedule_task add constraint fk_msg01ab_schedule_uuid foreign key (msg01ab_schedule_uuid) references msg_v1.msg01aa_schedule(msg01aa_uuid);
alter table msg_v1.msg01ab_schedule_task add constraint fk_msg01ab_published_provider_uuid foreign key (msg01ab_published_provider_uuid) references msg_v1.msg00bac_publisher_provider(msg00bac_uuid);
