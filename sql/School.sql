create database School;
use School;
show tables;

CREATE TABLE Students (id INT(10) PRIMARY KEY AUTO_INCREMENT,
						FirstName VARCHAR(32) NOT NULL,
                        LastName VARCHAR(32) NOT NULL,
                        subject1 INT(10),
                        subject2 INT(10),
                        subject3 INT(10));

INSERT INTO Students(FirstName, LastName)
VALUES ('Ahinoam', 'Nini'),
		('Gal', 'Gadot'),
		('Darth', 'Vader'),
		('Dr', 'Evil');


CREATE TABLE Subjects (id INT(10) PRIMARY KEY AUTO_INCREMENT,
						SubjectsName VARCHAR(35) NOT NULL,
                        TeacherId INT(10));


CREATE TABLE Teachers (id INT(10) PRIMARY KEY AUTO_INCREMENT,
						FirstName VARCHAR(30) NOT NULL,
                        LastName VARCHAR(35) NOT NULL,
                        teachigSubject INT(10));
ALTER TABLE Subjects
ADD FOREIGN KEY (TeacherId) REFERENCES Teachers (id);

ALTER TABLE Teachers
ADD FOREIGN KEY (teachigSubject) REFERENCES Subjects (id);

INSERT INTO Subjects(SubjectsName)
VALUES ('Music', 1),
		('Math', 2);



INSERT INTO Teachers(FirstName, LastName, teachigSubject)
VALUES ('The', 'One', 1),
		('Agent', 'Smith', 2);


SELECT * FROM Students;
SELECT * FROM Subjects;
SELECT * FROM Teachers;

DROP TABLE Teachers;
DROP TABLE Subjects;
DROP TABLE Students;

