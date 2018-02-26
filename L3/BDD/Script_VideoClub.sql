DROP TABLE IF EXISTS emprunt;
DROP TABLE IF EXISTS dvd;
DROP TABLE IF EXISTS acteur;
DROP TABLE IF EXISTS film;
DROP TABLE IF EXISTS client;
DROP TABLE IF EXISTS personne;
DROP TABLE IF EXISTS magasin;
DROP TABLE IF EXISTS genre;


-- CREATION DES TABLES
CREATE TABLE personne (
	id_pers serial PRIMARY KEY,
	nom_pers varchar(60) NOT NULL,
	prenom_pers varchar(60) NOT NULL
);

CREATE TABLE magasin (
	id_magasin serial PRIMARY KEY,
	nom_magasin varchar(60) NOT NULL,
	adresse varchar(100)
);

CREATE TABLE client (
	id_client serial PRIMARY KEY,
	nom_client varchar(60) NOT NULL,
	prenom_client varchar(60) NOT NULL,
	adresse varchar(100) NOT NULL,
	caution int NOT NULL
);

CREATE TABLE genre(
	id_genre serial PRIMARY KEY,
	nom_genre varchar(60) NOT NULL,
	type_public varchar(50) NOT NULL	
);

CREATE TABLE film (
	id_film serial PRIMARY KEY,
	titre varchar(100) NOT NULL,
	duree int NOT NULL,
	id_genre int REFERENCES genre,
	id_pers int REFERENCES personne
);

CREATE TABLE acteur (
	id_pers int REFERENCES personne(id_pers),
	id_film int REFERENCES film(id_film),
	PRIMARY KEY (id_pers, id_film)
);

CREATE TABLE dvd (
	id_dvd serial PRIMARY KEY,
	etat varchar(30) NOT NULL,
	date_mes date NOT NULL,
	id_magasin int REFERENCES magasin(id_magasin),
	id_film int REFERENCES film
);

CREATE TABLE emprunt (
	date_deb date NOT NULL,
	date_fin date,
	id_client int REFERENCES personne(id_pers),
	id_dvd int REFERENCES dvd(id_dvd),
	PRIMARY KEY (id_client, id_dvd, date_deb)
);


INSERT INTO personne VALUES (DEFAULT, 'De Niro', 'Robert');
INSERT INTO personne VALUES (DEFAULT, 'Ford', 'Harrison');
INSERT INTO personne VALUES (DEFAULT, 'Di Caprio', 'Leonardo');
INSERT INTO personne VALUES (DEFAULT, 'Lucas', 'George');
INSERT INTO personne VALUES (DEFAULT, 'Cameron', 'James');
INSERT INTO personne VALUES (DEFAULT, 'Winslet', 'Kate');
INSERT INTO personne VALUES (DEFAULT, 'Fisher', 'Carrie');
INSERT INTO personne VALUES (DEFAULT, 'Hamill', 'Mark');

INSERT INTO magasin VALUES (DEFAULT, 'VideoFutur','Rue du pain - Le Mans');
INSERT INTO magasin VALUES (DEFAULT, 'FuturVideo','Avenue des Anges - Paris');

INSERT INTO client VALUES (DEFAULT,'T','Toto', 'Boulevard des tutu - Le Mans', 60);
INSERT INTO client VALUES (DEFAULT,'X','Titi', 'Boulevard des tete - Le Mans', 30);

INSERT INTO genre VALUES (DEFAULT, 'Science Fiction', '+12 ans');
INSERT INTO genre VALUES (DEFAULT, 'Drame', '+12 ans');
INSERT INTO genre VALUES (DEFAULT, 'Horreur', '+18 ans');


INSERT INTO film VALUES (DEFAULT, 'Star Wars IV', '210', (select id_genre from genre where nom_genre='Science Fiction'),(select id_pers from personne where nom_pers='Lucas'));
INSERT INTO film VALUES (DEFAULT, 'Titanic', '200', (select id_genre from genre where nom_genre='Drame'),(select id_pers from personne where nom_pers='Cameron'));
INSERT INTO film VALUES (DEFAULT, 'Inception', '230', (select id_genre from genre where nom_genre='Science Fiction'),(select id_pers from personne where nom_pers='Di Caprio'));

INSERT INTO acteur VALUES ((select id_pers from personne where nom_pers='Di Caprio'),(select id_film from film where titre='Titanic'));
INSERT INTO acteur VALUES ((select id_pers from personne where nom_pers='Winslet'),(select id_film from film where titre='Titanic'));
INSERT INTO acteur VALUES ((select id_pers from personne where nom_pers='Ford'),(select id_film from film where titre='Star Wars IV'));
INSERT INTO acteur VALUES ((select id_pers from personne where nom_pers='Hamill'),(select id_film from film where titre='Star Wars IV'));
INSERT INTO acteur VALUES ((select id_pers from personne where nom_pers='Fisher'),(select id_film from film where titre='Star Wars IV'));

INSERT INTO dvd VALUES (DEFAULT, 'neuf', '18-01-2018',(select id_magasin from magasin where adresse like '%Le Mans'),(select id_film from film where titre='Star Wars IV'));
INSERT INTO dvd VALUES (DEFAULT, 'neuf', '18-01-2018',NULL,(select id_film from film where titre='Star Wars IV'));
INSERT INTO dvd VALUES (DEFAULT, 'neuf', '18-01-2018',NULL,(select id_film from film where titre='Star Wars IV'));
INSERT INTO dvd VALUES (DEFAULT, 'neuf', '18-01-2018',(select id_magasin from magasin where adresse like '%Le Mans'),(select id_film from film where titre='Titanic'));

INSERT INTO emprunt VALUES ('19-01-2018','20-01-2018',(select id_client from client where nom_client='T'),1);
INSERT INTO emprunt VALUES ('10-02-2018','14-02-2018',(select id_client from client where nom_client='T'),1);
INSERT INTO emprunt VALUES ('13-02-2018',NULL,(select id_client from client where nom_client='T'),2);
INSERT INTO emprunt VALUES ('22-02-2018',NULL,(select id_client from client where nom_client='X'),3);



