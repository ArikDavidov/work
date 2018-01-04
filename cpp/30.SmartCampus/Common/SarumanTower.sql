CREATE DATABASE SarumanTower;
use SarumanTower;

CREATE TABLE Agent
(
    Id INT PRIMARY KEY AUTO_INCREMENT,
    DeviceId VARCHAR(256),
    DeviceTypeId INT,
	LocationId INT,
    LogId INT,
    Configuration VARCHAR(256)
);

CREATE TABLE DeviceType
(
    DeviceTypeId INT PRIMARY KEY AUTO_INCREMENT,
    DeviceTypeName VARCHAR(256)
);

create table Location
(
	LocationId int PRIMARY KEY AUTO_INCREMENT,
    LocationName varchar(255),
    PID int
);

CREATE TABLE Log
(
    LogId INT PRIMARY KEY AUTO_INCREMENT,
    LogName VARCHAR(256)
);

INSERT INTO Agent(DeviceId, DeviceTypeId, LocationId, LogId, Configuration) VALUES
	('door_01', 1, 8, 1, 'always closed'),
	('door_02', 1, 8, 1, NULL),
	('door_03', 1, 9, 1, 'always open'),
	('motion_01', 2, 9, 1, NULL),
	('motion_02', 2, 10, 1, NULL),
	('motion_03', 2, 10, 1, 'always on'),
	('motion_04', 2, 11, 1, 'always off'),
	('motion_05', 2, 12, 1, NULL),
	('motion_06', 2, 13, 1, NULL),
	('smoke_01', 3, 14, 2, NULL);

INSERT INTO DeviceType(DeviceTypeName) VALUES
	('Evil_Corp_door_sennsor_1000'),
	('Evil_Corp_motion_detector_550'),
	('Evil_Corp_smoke_detector_900');

INSERT INTO Location(LocationName, PID) VALUES
	('floor_minus_03', NULL),
	('floor_minus_02', NULL),
	('floor_minus_01', NULL),
	('floor_00', NULL),
	('floor_01', NULL),
	('floor_02', NULL),
	('floor_03', NULL),
	('room_011', 4),
	('room_025', 4),
	('room_032', 4),
	('room_m311', 1),
	('room_m225', 2),
	('room_m132', 3),
	('room_221', 6);

INSERT INTO Log(LogName) VALUES
	('security'),
	('fire');

SELECT DeviceId
    , DeviceTypeName AS DeviceType
    , CASE WHEN r.LocationId IS NOT NULL THEN ff.LocationName ELSE f.LocationName END AS Floor
    , r.LocationName AS Room
    , LogName AS Log
    , Configuration
FROM Agent a
JOIN DeviceType d ON d.DeviceTypeId = a.DeviceTypeId
JOIN Log l ON l.LogId =  a.LogId
LEFT JOIN Location r ON r.LocationId = a.LocationId AND r.PID IS NOT NULL
LEFT JOIN Location f ON f.LocationId = a.LocationId AND f.PID IS NULL
JOIN Location ff ON r.PID = ff.LocationId;


SELECT DeviceId
    , DeviceTypeName AS DeviceType
    , f.LocationName AS Floor
    , r.LocationName AS Room
    , LogName AS Log
    , Configuration
FROM Agent a
JOIN DeviceType d ON d.DeviceTypeId = a.DeviceTypeId
JOIN Log l ON l.LogId =  a.LogId
JOIN Location r ON r.LocationId = a.LocationId
JOIN Location f ON f.LocationId = r.PID;



