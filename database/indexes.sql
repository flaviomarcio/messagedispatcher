set search_path=public;
create extension if not exists "uuid-ossp";

create unique index if not exists unq_msg00aaa_name on msg_v1.msg00aaa_provider(msg00aaa_name);
create unique index if not exists unq_msg00baa_name on msg_v1.msg00baa_publisher(msg00baa_name);
