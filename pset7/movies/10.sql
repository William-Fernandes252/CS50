SELECT people.name 
FROM people JOIN directors ON people.id = directors.person_id JOIN movies ON movies.id = directors.movie_id JOIN ratings ON directors.movie_id = ratings.movie_id 
WHERE ratings.rating >= 9.0;