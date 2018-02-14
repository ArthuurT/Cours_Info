## SEANCE 2 - Plateforme de jeux et pl/pgsql
#### TROTTIER Arthur - L3 SPI

## Connexion à la DATABASE

```
psql --username=u_l3info031 --dbname=bd_l3info031
```

# FIN SQL NON PROCEDURAL

## ROLE

1.
```sql
ALTER USER u_l3info031 WITH PASSWORD 'WarenAT';
```
2.
```sql
CREATE GROUP l3info028_031;
ALTER GROUP l3info028_031 ADD USER u_l3info031;
ALTER GROUP l3info028_031 ADD USER u_l3info028;
SET ROLE l3info028_031;
SELECT SESSION_USER,CURRENT_USER;
RESET ROLE;
```

## SCHEMA
```sql
CREATE SCHEMA IF NOT EXISTS AUTHORIZATION l3info028_031;
CREATE SCHEMA l3info028 AUTHORIZATION l3info028_031;
CREATE SCHEMA l3info031 AUTHORIZATION l3info028_031;
```

## PRIVILEGES

```sql
REVOKE CREATE ON SCHEMA public TO public;
```

# SQL PROCEDURAL

## PREMIERS PAS

1.
```sql
CREATE OR REPLACE FUNCTION bonjour()
RETURNS void
AS $$
DECLARE
BEGIN
RAISE NOTICE 'Bonjour %, quelle belle journée n est-ce pas',USER;
END;
$$ LANGUAGE plpgsql;
```
2.
```sql
CREATE OR REPLACE FUNCTION compar(x int, y int)
RETURNS RECORD
AS $$
DECLARE
  min int;
  max int;
  res RECORD;
BEGIN
  RAISE NOTICE 'a: %',x;
  RAISE NOTICE 'b: %',y;
  IF x < y THEN
    min := x;
    max := y;
    SELECT min, max INTO res;
  ELSIF x > y THEN
    min := y;
    max := x;
    SELECT 'min = '||min, 'max = '||max INTO res;
  ELSE
    SELECT 'equal = '||x INTO res;
  END IF;
  RETURN res;
END;
$$ LANGUAGE plpgsql;
```

# PLATEFORME DE JEU EN LIGNE

## MODIFICIATION DE LA BASE

1.
```SQL
ALTER TABLE visiteur ADD COLUMN nom varchar(20);
ALTER TABLE visiteur ADD COLUMN  prenom varchar(20);
```

2.
```SQL
CREATE FUNCTION maj_nom_prenom(varchar(20),varchar(20),varchar(20))
RETURNS void
AS
'UPDATE visiteur SET nom = $2, prenom = $3 WHERE login = $1;'
LANGUAGE SQL;
```

3.
```SQL
CREATE OR REPLACE FUNCTION listing(nomjeu varchar(20), unlogin varchar(20))
RETURNS setof record
AS $$
DECLARE
BEGIN
return query(
  SELECT nom_avatar, nom_race, highscore
    FROM visiteur natural join avatar natural join race natural join partie
      WHERE id_jeu = (SELECT id_jeu FROM jeu WHERE jeu.nom_jeu = nomjeu)
      AND login = unlogin
      ORDER BY highscore DESC
);
END;
$$ LANGUAGE plpgsql;

SELECT * FROM listing('Elijah','Forge of Empire')
  AS t(nom_avatar varchar(20), nom_race varchar(20), highscore bigint);
```

# Exam

1.
```sql
SELECT login FROM visiteur
  WHERE id_visiteur = (
    SELECT id_visiteur
      FROM stock
        GROUP BY id_visiteur,nb_dispo
          HAVING MAX(nb_dispo) = COUNT(nb_dispo)
  );
```

2.
```SQL
CREATE FUNCTION prix(varchar(20))
RETURNS integer
AS
'SELECT prix FROM objet WHERE nom_objet = $1'
LANGUAGE SQL;
```

2bis.
```sql
SELECT prix('Gant de venin');
```

3.
```sql
CREATE OR REPLACE FUNCTION plus_avatar(login1 varchar(20),login2 varchar(20))
RETURNS void
AS $$
DECLARE
BEGIN
  IF (SELECT COUNT(id_avatar) FROM avatar WHERE id_visiteur = (SELECT id_visiteur FROM visiteur WHERE login = login1)) > (SELECT COUNT(id_avatar) FROM avatar WHERE id_visiteur = (SELECT id_visiteur FROM visiteur WHERE login = login2)) THEN
    RAISE NOTICE 'Login avec le plus d avatar: %',login1;
  ELSE IF (SELECT COUNT(id_avatar) FROM avatar WHERE id_visiteur = (SELECT id_visiteur FROM visiteur WHERE login = login1)) < (SELECT COUNT(id_avatar) FROM avatar WHERE id_visiteur = (SELECT id_visiteur FROM visiteur WHERE login = login2)) THEN
    RAISE NOTICE 'Login avec le plus d avatar: %',login2;
  ELSE
    RAISE NOTICE 'Login avec le plus d avatar: idem';
  END IF;
END;
$$ LANGUAGE plpgsql;
```

3bis.
```SQL
select plus_avatar('Elijah','Ian');
```
