## SEANCE 1 - Plateforme de jeu en ligne
#### TROTTIER Arthur - L3 SPI

## Implémentation

1. Création de la base
```sql
CREATE DATABASE bd_l3info031 WITH OWNER = u_l3info031;
```

2. Création des schémas
```sql
CREATE SCHEMA u_l3info031;
CREATE SCHEMA "TP1_jeu";
```

3. Modification du search path
```sql
SET search_path TO "TP1_jeu", "u_l3info031";
```

4. Suppression du schéma public
```sql
DROP SCHEMA public;
```

5. Creation des tables

```sql
---- Création d'une énumération de type de jeu

CREATE TYPE mode AS ENUM ('role', 'plateau', 'tower defense', 'MMORPG', 'autre');

---- Emplacement de la création de table JEU

CREATE TABLE jeu(
	id_jeu serial PRIMARY KEY,
	nom_jeu varchar(20) NOT NULL,
	type mode,
	nb_joueur integer
);

---- Emplacement de la création de table PARTIE

CREATE TABLE partie(
	id_avatar serial REFERENCES avatar,
	id_jeu serial REFERENCES jeu,
	role varchar(50),
	highscore bigint,
	PRIMARY KEY(id_avatar,id_jeu)
);

---- Emplacement de la création de table SAVE

CREATE TABLE save(
	id_avatar bigint REFERENCES avatar,
	id_jeu bigint REFERENCES jeu,
	date_s date,
	nb_pv integer,
	fichier varchar(50) NOT NULL UNIQUE,
	PRIMARY KEY(id_avatar,id_jeu,date_s)
);

---- Emplacement de la création de la table VILLE

CREATE TABLE ville(
	id_ville serial PRIMARY KEY,
	nom_ville varchar(50) UNIQUE,
	code_postal integer
);

INSERT INTO ville VALUES (DEFAULT,'Aix en Provence',13100);
INSERT INTO ville VALUES (DEFAULT,'Brette les Pins',72250);
INSERT INTO ville VALUES (DEFAULT,'Foix',09000);
INSERT INTO ville VALUES (DEFAULT,'Dunkerque',59640);
INSERT INTO ville VALUES (DEFAULT,'Grenoble',38000);
INSERT INTO ville VALUES (DEFAULT,'Annecy',74000);

ALTER TABLE visiteur ADD id_ville bigint REFERENCES ville;
UPDATE visiteur SET id_ville = (SELECT id_ville FROM ville WHERE ville.nom_ville = visiteur.ville);
ALTER TABLE visiteur DROP COLUMN ville;
UPDATE visiteur set id_ville = (SELECT id_ville FROM ville WHERE ville.nom_ville = 'Aix en Provence') WHERE login = 'Ian';
UPDATE visiteur set id_ville = (SELECT id_ville FROM ville WHERE ville.nom_ville = 'Brette les Pins') WHERE login = 'Sean';
ALTER TABLE jeu rename column nb_joueur TO nb_joueur_max;
```

## Commandes SQL

1. Combien y-a-t-il de visiteur ?

```sql
SELECT COUNT(*) FROM visiteur;
```

2. Quel avatar joue actuellement une partie de League of Angels

```sql
SELECT id_avatar FROM jeu NATURAL JOIN partie WHERE nom_jeu = 'League of Angels';
```







## Exam

1. Ajout du parrain

```sql
ALTER TABLE visiteur add parrain bigint REFERENCES id_visiteur;
UPDATE visiteur SET parrain = (SELECT id_visiteur FROM visiteur WHERE login = 'Elijah') WHERE login = 'Sean';
UPDATE visiteur SET parrain = (SELECT id_visiteur FROM visiteur WHERE login = 'Elijah') WHERE login = 'Billy';
UPDATE visiteur SET parrain = (SELECT id_visiteur FROM visiteur WHERE login = 'Elijah') WHERE login = 'Dominic';
UPDATE visiteur SET parrain = (SELECT id_visiteur FROM visiteur WHERE login = 'Ian') WHERE login = 'Viggo';
```

2. Commandes

b)
```sql
INSERT INTO stock VALUES ((SELECT id_objet FROM objet WHERE nom_objet = 'Gant de venin'),
													(SELECT id_visiteur FROM visiteur WHERE login = 'Elijah'),
													10,10);
```
c)
```sql
select count(parrain)*10 AS cadeau FROM visiteur GROUP BY parrain
```
