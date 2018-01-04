-- Displaying Index
SHOW INDEX FROM film FROM sakila;
SHOW INDEX FROM film;

SELECT *
FROM INFORMATION_SCHEMA.STATISTICS
WHERE TABLE_NAME = 'film';

-- Creating Index
CREATE INDEX idx_film_length ON film (length);

-- Query using Index
SELECT film_id, length
FROM film
WHERE length = 100;

-- Explain Index Usage
EXPLAIN SELECT film_id, length
FROM film
WHERE length = 100;

-- Droping Index
DROP Index idx_film_length ON film;




















