-- Check Indexes
SHOW INDEX FROM film FROM sakila;
SHOW INDEX FROM film;

-- Check Indexes
SELECT *
FROM INFORMATION_SCHEMA.STATISTICS
WHERE TABLE_NAME = 'film';

-- Analyze Table
ANALYZE TABLE film;

-- Optimize Table
OPTIMIZE TABLE film;

-- ALTER TABLE
ALTER TABLE film;




-- Creating Index
CREATE INDEX idx_film_length ON film (length);

-- Droping Index
DROP Index idx_film_length ON film;