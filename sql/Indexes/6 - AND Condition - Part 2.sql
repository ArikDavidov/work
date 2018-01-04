-- Displaying Index
SHOW INDEX FROM film FROM sakila;

SELECT *
FROM INFORMATION_SCHEMA.STATISTICS
WHERE TABLE_NAME = 'film';



-- SELECT Statement
EXPLAIN SELECT title, rental_duration, length
FROM film
WHERE rental_duration = 6 AND length = 100;

-- Creating Index
CREATE INDEX idx_film_rental_duration ON film (rental_duration);
CREATE INDEX idx_film_length ON film (length);
CREATE INDEX idx_film_length_rental_duration ON film (length,rental_duration);
CREATE INDEX idx_film_rental_duration_length ON film (rental_duration,length);

-- SELECT Statement
EXPLAIN SELECT title, rental_duration, length
FROM film
WHERE rental_duration = 6 AND length = 100;

-- SELECT Statement
EXPLAIN SELECT title, length, rental_duration
FROM film
WHERE rental_duration = 6 AND length = 100;

-- SELECT Statement
EXPLAIN SELECT title, rental_duration, length
FROM film
WHERE length = 100 AND rental_duration = 6;

-- Droping Index
DROP INDEX idx_film_length_rental_duration ON film;
DROP INDEX idx_film_rental_duration_length ON film;
DROP INDEX idx_film_length ON film;
DROP INDEX idx_film_rental_duration ON film;


















