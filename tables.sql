create table if not exists keys (
    service varchar(256) not null,
    login varchar(512) not null,
    password integer not null,
    modify_date date,
    primary key (service, login)
);