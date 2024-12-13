create table if not exists drivers
(
    id         bigserial primary key,
    first_name varchar(50)                                    not null,
    last_name  varchar(50)                                    not null,
    phone      varchar(15) check (phone ~ '^\+?[0-9]{7,15}$') not null unique,
    created_at timestamp default current_timestamp            not null,
    updated_at timestamp default current_timestamp            not null
);

create table if not exists vehicles
(
    id         bigserial primary key,
    brand      varchar(50)                         not null,
    type       varchar                             not null,
    created_at timestamp default current_timestamp not null,
    updated_at timestamp default current_timestamp not null
);

create table if not exists cargoes
(
    id         bigserial primary key,
    name       varchar(50)                         not null,
    weight     double precision check (weight > 0) not null,
    sender     varchar(100)                        not null,
    receipt    varchar(100)                        not null,
    created_at timestamp default current_timestamp not null,
    updated_at timestamp default current_timestamp not null
);

create table if not exists routes
(
    id          bigserial primary key,
    driver_id   bigserial                           not null references drivers (id) on delete set null on update cascade,
    vehicles_id bigserial                           not null references vehicles (id) on delete set null on update cascade,
    cargoes_id  bigserial                           not null references cargoes (id) on delete set null on update cascade,
    start_point varchar(150)                        not null,
    end_point   varchar(150)                        not null,
    status      varchar                             not null,
    created_at  timestamp default current_timestamp not null,
    updated_at  timestamp default current_timestamp not null
);

do
$$
    begin
        if not exists (select 1
                       from pg_indexes
                       where tablename = 'routes'
                         and indexname = 'idx_routes_driver_id') then
            create index idx_routes_driver_id on routes (driver_id);
        end if;

        if not exists (select 1
                       from pg_indexes
                       where tablename = 'routes'
                         and indexname = 'idx_routes_vehicles_id') then
            create index idx_routes_vehicles_id on routes (vehicles_id);
        end if;

        if not exists (select 1
                       from pg_indexes
                       where tablename = 'routes'
                         and indexname = 'idx_routes_cargoes_id') then
            create index idx_routes_cargoes_id on routes (cargoes_id);
        end if;
    end
$$;

create or replace function update_timestamp()
    returns trigger as
$$
begin
    new.updated_at = current_timestamp;
    return new;
end;
$$ language plpgsql;

do
$$
    begin
        if not exists (select 1
                       from pg_trigger
                       where tgname = 'trg_update_timestamp_drivers') then
            create trigger trg_update_timestamp_drivers
                before update
                on drivers
                for each row
            execute function update_timestamp();
        end if;

        if not exists (select 1
                       from pg_trigger
                       where tgname = 'trg_update_timestamp_vehicles') then
            create trigger trg_update_timestamp_vehicles
                before update
                on vehicles
                for each row
            execute function update_timestamp();
        end if;

        if not exists (select 1
                       from pg_trigger
                       where tgname = 'trg_update_timestamp_cargoes') then
            create trigger trg_update_timestamp_cargoes
                before update
                on cargoes
                for each row
            execute function update_timestamp();
        end if;

        if not exists (select 1
                       from pg_trigger
                       where tgname = 'trg_update_timestamp_routes') then
            create trigger trg_update_timestamp_routes
                before update
                on routes
                for each row
            execute function update_timestamp();
        end if;
    end
$$;

