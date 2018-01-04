USE sakila;

-- Create Sample Table
CREATE TABLE TestTable (
ID INT UNSIGNED NOT NULL AUTO_INCREMENT,
FirstName VARCHAR(64) NOT NULL DEFAULT '',
LastName VARCHAR(64) NOT NULL DEFAULT '',
FullName VARCHAR(128) NOT NULL DEFAULT '',
PRIMARY KEY (ID),
KEY ix_TestTable_FN_LN (FirstName, LastName));

EXPLAIN TestTable;

-- Populate Table
INSERT INTO TestTable (FirstName, LastName, FullName)
SELECT First_Name, Last_Name, CONCAT(First_Name,' ', Last_Name)
FROM actor;

-- -------------------------------------------------------------------
-- -------------------------------------------------------------------

-- SELECT Statement
EXPLAIN SELECT FirstName, LastName
FROM TestTable
ORDER BY ID;

-- SELECT Statement
EXPLAIN SELECT FirstName, LastName
FROM TestTable
ORDER BY FirstName;

-- SELECT Statement
EXPLAIN SELECT FirstName, LastName
FROM TestTable
ORDER BY LastName;

-- SELECT Statement
EXPLAIN SELECT FirstName, LastName
FROM TestTable
ORDER BY FullName;

-- -------------------------------------------------------------------
-- -------------------------------------------------------------------

-- SELECT Statement
EXPLAIN SELECT FirstName, LastName
FROM TestTable
WHERE ID = 100;

-- SELECT Statement
EXPLAIN SELECT FirstName, LastName
FROM TestTable
WHERE ID = 100
ORDER BY ID;

-- SELECT Statement
EXPLAIN SELECT FirstName, LastName
FROM TestTable
WHERE ID = 100
ORDER BY FirstName;

-- SELECT Statement
EXPLAIN SELECT FirstName, LastName
FROM TestTable
WHERE ID = 100
ORDER BY FullName;

-- -------------------------------------------------------------------
-- -------------------------------------------------------------------

-- SELECT Statement
EXPLAIN SELECT FirstName, LastName
FROM TestTable
WHERE FirstName = 'ALBERT';

-- SELECT Statement
EXPLAIN SELECT FirstName, LastName
FROM TestTable
WHERE FirstName = 'ALBERT'
ORDER BY ID;

-- SELECT Statement
EXPLAIN SELECT FirstName, LastName
FROM TestTable
WHERE FirstName = 'ALBERT'
ORDER BY FirstName;

-- SELECT Statement
EXPLAIN SELECT FirstName, LastName
FROM TestTable
WHERE FirstName = 'ALBERT'
ORDER BY FullName;

-- -------------------------------------------------------------------
-- -------------------------------------------------------------------

-- SELECT Statement
EXPLAIN SELECT FirstName, LastName
FROM TestTable
WHERE LastName = 'GRANT';

-- SELECT Statement
EXPLAIN SELECT FirstName, LastName
FROM TestTable
WHERE LastName = 'GRANT'
ORDER BY ID;

-- SELECT Statement
EXPLAIN SELECT FirstName, LastName
FROM TestTable
WHERE LastName = 'GRANT'
ORDER BY FirstName;

-- SELECT Statement
EXPLAIN SELECT FirstName, LastName
FROM TestTable
WHERE LastName = 'GRANT'
ORDER BY FullName;

-- -------------------------------------------------------------------
-- -------------------------------------------------------------------

-- Clean up
DROP TABLE TestTable;

















