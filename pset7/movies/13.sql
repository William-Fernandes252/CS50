SELECT people.name FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON people.id = stars.person_id WHERE movies.title IN 
(SELECT movies.title FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON people.id = stars.person_id WHERE people.name = "Kevin Bacon" AND people.birth = 1958)
AND NOT (people.name = "Kevin Bacon" AND people.birth = 1958);