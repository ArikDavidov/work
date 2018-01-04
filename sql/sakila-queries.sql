USE sakila;
SELECT actor.last_name, actor.first_name FROM actor, film_actor
	WHERE actor.actor_id = film_actor.actor_id AND film_actor.film_id = 5;

SELECT * FROM film_actor
	WHERE film_actor.film_id = 5;
    
SELECT film_actor.film_id, actor.first_name, actor.last_name
	FROM film, actor, film_actor
	WHERE (film_actor.film_id = 5 AND film_actor.actor_id = actor.actor_id);
    
SELECT film_actor.film_id, actor.first_name, actor.last_name
	FROM film, actor, film_actor
	WHERE film.title = 'ALABAMA DEVIL'
		AND film.film_id = film_actor.film_id
		AND film_actor.actor_id = actor.actor_id;
    
SELECT * FROM actor WHERE first_name LIKE '_a%';
SELECT * FROM actor WHERE first_name between 'a%' and 'c%';
SELECT * FROM actor WHERE first_name in ('ariel', 'fred', 'john');

SELECT film_id from film where title like 'alabama%';
SELECT actor_id FROM film_actor where film_id = 9;

SELECT first_name, last_name, actor_id FROM actor WHERE actor_id IN
			(SELECT actor_id FROM film_actor WHERE film_id IN
            (SELECT film_id FROM film WHERE title LIKE 'alabama%'));


SELECT film_actor.film_id, actor.first_name, actor.last_name
	FROM film, actor, film_actor
	WHERE (film_actor.film_id = 5 AND film_actor.actor_id = actor.actor_id);

SELECT title from film WHERE film_id in 
(select film_id from film_actor WHERE actor_id in 
			(SELECT actor_id FROM film_actor WHERE film_id IN
            (SELECT film_id FROM film WHERE title LIKE 'alabama%')));
            
            
SELECT a.first_name, a.last_name, f.title FROM actor a, film f WHERE actor_id IN
			(SELECT actor_id FROM film_actor WHERE film_id IN
            (SELECT f,film_id FROM film f WHERE title LIKE 'alabama%'))
            ORDER BY a.first_mane;
            
SELECT f.title, a.first_name from film f, actor a WHERE f.film_id = 40
				AND a.actor_id in (SELECT actor_id FROM film_actor WHERE film_id IN
            (SELECT film_id FROM film WHERE title LIKE 'alabama%'));

SELECT film_id, actor_id FROM film_actor WHERE actor_id IN
			(SELECT actor_id FROM film_actor WHERE film_id IN
         Students   (SELECT film_id FROM film WHERE title LIKE 'alabama%'));


SELECT a.first_name, fa.film_id
		from actor a JOIN film_actor fa ON a.actor_id = fa.actor_id
        order by a.actor_id;
        
SELECT f.title, fa.actor_id
	from film_actor fa join film f on fa.film_id = f.film_id
	order by fa.actor_id;


CREATE TEMPORARY TABLE IF NOT EXISTS cte AS 
(
	select fa.actor_id
	from film_actor fa
	JOIN film f ON f.film_id = fa.film_id
	where f.title like 'MATRIX%'
);
select fa.actor_id, f.title, a.first_name
from film_actor fa
JOIN film f ON f.film_id = fa.film_id
JOIN actor a ON a.actor_id = fa.actor_id
join cte c on a.actor_id = c.actor_id;

SELECT VERSION();




select fa.actor_id, f.title, a.first_name
from film_actor fa
JOIN film f ON f.film_id = fa.film_id
JOIN actor a ON a.actor_id = fa.actor_id
where a.actor_id in(
	select fa.actor_id
	from film_actor fa
	JOIN film f ON f.film_id = fa.film_id
	where title like 'MATRIX%');
    

SELECT first_name, last_name
FROM customer
JOIN rental ON customer.customer_id = rental.customer_id
where return_date is null;






SELECT title
FROM film
where film_id in(
	SELECT film_id
	FROM film
	WHERE title LIKE 'A%')
AND film_id in(
	SELECT film_id
	FROM film_actor
	JOIN actor on actor.actor_id = film_actor.actor_id
	WHERE actor.first_name LIKE 'John%')
AND film_id in(
	SELECT film_id
	FROM film_actor
	JOIN actor on actor.actor_id = film_actor.actor_id
	WHERE (actor.first_name LIKE 'NICK%'
	OR actor.first_name LIKE 'Albert%'));

    
    
   
   
   
SELECT film_id
	FROM film_actor
	JOIN actor on actor.actor_id = film_actor.actor_id
	WHERE actor.first_name LIKE 'John%'

show index from film from sakila;



