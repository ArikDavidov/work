USE sakila;

-- Displaying Index
SHOW INDEX FROM film FROM sakila;

SELECT *
FROM INFORMATION_SCHEMA.STATISTICS
WHERE TABLE_NAME = 'film';



-- SELECT Statement
EXPLAIN SELECT title, rental_duration, length
FROM film
WHERE rental_duration = 6 OR length = 100;

-- Creating Index
CREATE INDEX idx_film_rental_duration ON film (rental_duration);
CREATE INDEX idx_film_length ON film (length);
-- Creating Index
CREATE INDEX idx_film_rental_duration_length ON film (rental_duration,length);
CREATE INDEX idx_film_length_rental_duration ON film (length,rental_duration);

-- SELECT Statement
EXPLAIN SELECT title, rental_duration, length 
FROM film
WHERE rental_duration = 6 AND length = 100;

-- SELECT Statement
EXPLAIN SELECT title, rental_duration, length 
FROM film FORCE INDEX (idx_film_length_rental_duration)
WHERE rental_duration = 6 AND length = 100;

-- SELECT Statement
EXPLAIN SELECT title, rental_duration, length 
FROM film USE INDEX (idx_film_rental_duration,idx_film_length,idx_film_length_rental_duration)
WHERE rental_duration = 6 AND length = 100;

-- SELECT Statement
EXPLAIN SELECT title, rental_duration, length 
FROM film IGNORE INDEX (idx_film_length_rental_duration,idx_film_rental_duration_length,idx_film_length,idx_film_rental_duration)
WHERE rental_duration = 6 AND length = 100;

-- Droping Index
DROP INDEX idx_film_length ON film;
DROP INDEX idx_film_rental_duration ON film;
-- Droping Index
DROP INDEX idx_film_length_rental_duration ON film;
DROP INDEX idx_film_rental_duration_length ON film;
















