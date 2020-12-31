CREATE TABLE KeyValueTest
(
KeyUID INT PRIMARY KEY,
Value VARCHAR(32)
) ENGINE=INNODB;

DESCRIBE KeyValueTest;

insert into KeyValueTest (KeyUID, Value) Values (1, "Hello world!");
select * from KeyValueTest;