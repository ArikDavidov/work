create database Registrar;
use Registrar;

show tables;

create table SectionRegister
(
	SectionRegisterId int PRIMARY KEY AUTO_INCREMENT,
    SectionName varchar(255),
    Address VARCHAR(16),
    SubsPort int,
    EvtsPort int
);

select * from SectionRegister;
truncate Table SectionRegister;
drop table SectionRegister;

DELETE FROM SectionRegister WHERE SectionName = 'Dungeon';
select SectionRegisterId FROM SectionRegister WHERE SectionName = 'Dungeon';



