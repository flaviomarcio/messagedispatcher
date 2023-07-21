alter table msg_v1.msg00bac_publisher_provider add constraint ck_msg00bac_provider_type check(msg00bac_provider_type>=0);
alter table msg_v1.msg00bac_publisher_provider add constraint fk_msg00bac_publisher_uuid foreign key (msg00bac_publisher_uuid) references msg_v1.msg00baa_publisher(msg00baa_uuid);
alter table msg_v1.msg00bac_publisher_provider add constraint fk_msg00bac_provider_uuid foreign key (msg00bac_provider_uuid) references msg_v1.msg00aaa_provider(msg00aaa_uuid);
alter table msg_v1.msg00bad_publisher_token add constraint fk_msg00bad_publisher_uuid foreign key (msg00bad_publisher_uuid) references msg_v1.msg00baa_publisher(msg00baa_uuid);
alter table msg_v1.msg01ab_schedule_task add constraint fk_msg01ab_schedule_uuid foreign key (msg01ab_schedule_uuid) references msg_v1.msg01aa_schedule(msg01aa_uuid);
alter table msg_v1.msg01ab_schedule_task add constraint fk_msg01ab_published_provider_uuid foreign key (msg01ab_published_provider_uuid) references msg_v1.msg00bac_publisher_provider(msg00bac_uuid);
