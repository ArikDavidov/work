create database ex1;
use ex1;

show tables;

CREATE TABLE Students (id INT(10) PRIMARY KEY AUTO_INCREMENT,
						FirstName VARCHAR(30) NOT NULL,
                        LastName VARCHAR(35) NOT NULL,
                        enrol_date TIMESTAMP);

SELECT * FROM Students;

INSERT INTO Students(FirstName, LastName, enrol_date)
VALUES ('Gal', 'Gadot', NOW()),
		('Darth', 'Vader', NOW()),
		('Dr', 'Evil', NOW()),
		('Ahinoam', 'Nini', NOW()),
		('The', 'One', NOW()),
		('Agent', 'Smith', NOW());

SELECT LastName, enrol_date FROM Students;


CREATE TABLE PhoneNumbers (id INT(10) PRIMARY KEY AUTO_INCREMENT,
						StudentsId INT(10) NOT NULL,
                        PhoneNumbers VARCHAR(16) NOT NULL);

INSERT INTO PhoneNumbers(StudentsId, PhoneNumbers) VALUES
	(1, '0541231111'),
	(1, '0541232222'),
	(2, '0541233333'),
	(2, '0541234444'),
	(2, '0541235555'),
	(3, '0541236666'),
	(3, '0541237777'),
	(3, '0541238888'),
	(3, '0541239999');

SELECT * FROM PhoneNumbers;


SELECT * FROM Students LEFT JOIN PhoneNumbers
	ON Students.id = PhoneNumbers.StudentsId order by Students.LastName;





CREATE TABLE Emails (id INT(10) PRIMARY KEY AUTO_INCREMENT,
						StudentsId INT(10) NOT NULL,
                        Emails VARCHAR(64) NOT NULL);

INSERT INTO Emails(StudentsId, Emails) VALUES
			(1, 'Agent.Smith@gmail.com'),
			(1, 'Agent.Smith1@gmail.com'),
			(1, 'Agent.Smith2@gmail.com'),
			(1, 'Agent.Smith3@gmail.com'),
			(1, 'Agent.Smith4@hpindigo.com'),
			(1, 'Agent.Smith5@hpindigo.com'),
			(1, 'Agent.Smith6@hpindigo.com'),
			(1, 'Agent.Smith7@hpindigo.com'),
			(1, 'The.One@gmail.com'),
			(1, 'Morty.Smith@gmail.com'),
			(1, 'Gal.Gadot@gmail.com'),
			(1, 'darth.Vader@gmail.com'),
			(1, 'Dr.Evil@gmail.com'),
			(1, 'Hana.Vader@gmail.com'),
			(1, 'Dr.Evil@gmail.com');

                        
SELECT * FROM s1.Contacts;
SELECT * FROM s1.Contacts_1;
SELECT * FROM s1.Emails_A_1;

USE s1;
SELECT * FROM Contacts_1;

SELECT Email_Address FROM Emails_A_1 WHERE C_F_id = 3;
SELECT DISTINCT Email_Address FROM Emails_A_1 WHERE C_F_id = 3;




 
