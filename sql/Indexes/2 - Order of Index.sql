-- Displaying Index
SHOW INDEX FROM film FROM sakila;

SELECT *
FROM INFORMATION_SCHEMA.STATISTICS
WHERE TABLE_NAME = 'film';

-- Creating Index
CREATE INDEX idx_film_length ON film (length);

-- Creating Index
CREATE INDEX idx_film_length_desc ON film (length DESC);

-- Query using Index
SELECT film_id, length
FROM film
WHERE length = 100;

-- Explain Index Usage
EXPLAIN SELECT film_id, length
FROM film
WHERE length = 100;

-- Droping Index
DROP INDEX idx_film_length ON film;
DROP INDEX idx_film_length_desc ON film;




























