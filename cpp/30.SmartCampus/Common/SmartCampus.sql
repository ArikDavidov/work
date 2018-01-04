create database SmartCammpus;
use SmartCammpus;

show tables;

create table Location
(
	LocationId int PRIMARY KEY AUTO_INCREMENT,
    LocationName varchar(255),
    PID int
);

INSERT INTO Location(LocationName, PID) VALUES
	('Building_A', NULL),
	('Building_B', NULL),
	('Building_C', NULL),
	('Floor_01', 1),
	('Floor_02', 2),
	('Floor_03', 1),
	('Room_011', 4),
	('Room_025', 5),
	('Room_032', 6);

select * from Location;

-- truncate Table Location;

select lll.*
from Location l
inner join Location ll on l.LocationID = ll.PID
inner join Location lll on ll.LocationID = lll.PID
where l.LocationName = 'Building_A' and ll.LocationName = 'Floor_01';

select l2.*, l1.LocationName as ParentName, case when l2.LocationName = 'Floor_01' then 'Bottom floor' else 'Top floor' end as FloorType
from Location l1
inner join Location l2 on l1.LocationID = l2.PID
where l1.LocationName = 'Building_A' or l1.LocationName = 'Building_B';

drop table test;

