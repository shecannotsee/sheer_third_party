CREATE TABLE users (
    id               integer     primary key        autoincrement,
    first_name text  not null,
    last_name text   not null,
    birth_date       integer     not null,
    image_url        text,
    type_id          integer     not null
);

CREATE TABLE user_types (
    id              integer         primary key     autoincrement,
    name            text            not null        DEFAULT 'name_placeholder'
);
