create database SmartHomeDb;
use SmartHomeDb;
show tables;

CREATE TABLE Students (id INT(10) PRIMARY KEY AUTO_INCREMENT,
						config VARCHAR(32) NOT NULL,
                        LastName VARCHAR(32) NOT NULL,
                        subject1 INT(10),
                        subject2 INT(10),
                        subject3 INT(10));
                        
                        
CREATE TABLE Agents (
    AgentsId int,
    Config varchar(255),
	Location int,
	TypeId int,
    FirstName varchar(255),
    Description varchar(255),
    Log varchar(255)
);


