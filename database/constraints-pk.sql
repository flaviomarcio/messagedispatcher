alter table msg_v1.msg00aaa_provider add constraint pk_msg00aaa primary key(msg00aaa_uuid);
alter table msg_v1.msg00baa_publisher add constraint pk_msg00ba primary key(msg00baa_uuid);
alter table msg_v1.msg00bac_publisher_provider add constraint pk_msg00ac primary key(msg00bac_uuid);
alter table msg_v1.msg00bad_publisher_token add constraint pk_msg00bad primary key(msg00bad_uuid);
alter table msg_v1.msg01aa_schedule add constraint pk_msg01aa primary key(msg01aa_uuid);
alter table msg_v1.msg01ab_schedule_task add constraint pk_msg01ab primary key(msg01ab_uuid);
