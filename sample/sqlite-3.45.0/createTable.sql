--创建数据库表
create table user
(
    id		        integer		    NOT NULL,
    name	        varchar(255)	NOT NULL,
    product_type	varchar(32)		NOT NULL,
    create_time		data					,
    update_time 	data					,
    PRIMARY KEY		(id)
);