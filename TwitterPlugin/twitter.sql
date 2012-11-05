CREATE TABLE twitter (
    oauth_provider character(10),
    oauth_uid uuid,
    oauth_token text,
    oauth_secret text,
    username text,
    version integer,
    id serial NOT NULL,
    password character(255)
);
