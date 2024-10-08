/* 插入 */
insert into role
        (role_id, role_describe)
VALUES  (      1,   '123321   ');

/* 更新 */
update role set
    role_id = 2,
    role_describe = '123'
where role_id = 1;