# Seance 4 - SW7

Trottier Arthur - L2 SPI

## Implementation

1)
```
psql -d etu_sw7
```

2)
```
CREATE TABLE chauffeur (
  id_chauffeur BIGINT,
  nom varchar,
  prenom varchar,
  adr text,
  id_station_c BIGINT,
  PRIMARY KEY (id_chauffeur),
  FOREIGN KEY (id_station_c) REFERENCES station (id_station)
  );
```

```
CREATE TABLE permis(
  id_chauffeur BIGINT,
  cat_perm_c varchar,
  PRIMARY KEY (id_chauffeur,cat_perm_c),
  FOREIGN KEY (id_chauffeur) REFERENCES chauffeur (id_chauffeur)
  );
```

3)
```
ALTER TABLE station add nom_zone varchar;
ALTER TABLE position add nom_zone varchar;
UPDATE station set nom_zone = (SELECT nom_zone FROM zone WHERE zone.id_zone = station.id_zone);
UPDATE position set nom_zone = (SELECT nom_zone FROM zone WHERE zone.id_zone = position.id_zone);
DROP TABLE zone;
ALTER TABLE station DROP id_zone;
ALTER TABLE position DROP id_zone;
```

4)
```
ALTER TABLE plein add type_carbu varchar;
UPDATE plein set type_carbu = (SELECT type_carbu FROM modele natural join vehicule WHERE id_vehicule = plein.id_vehicule);
```

## Exploitation

5)
```
SELECT COUNT (*) FROM entretien WHERE date_e BETWEEN '2014-01-01' AND '2014-12-31';
```

6)
```
SELECT id_chauffeur,nom,prenom FROM chauffeur WHERE id_station_c = ANY(SELECT id_station FROM station WHERE nom_station = 'Geonosis');
```

7)
```
SELECT DISTINCT * FROM vehicule WHERE id_vehicule = ANY(SELECT id_vehicule FROM plein WHERE date_p BETWEEN '2015-08-11' AND '2015-12-11') AND id_modele = ANY(SELECT id_modele FROM modele WHERE nom_modele = 'cargo YT-1300');
```

8)
```
SELECT ((SUM(qte_carbu)*100)/SUM(nb_km)) FROM plein AS ConsoMoyenne WHERE id_vehicule = ANY(SELECT id_vehicule FROM vehicule WHERE id_modele = ANY(SELECT id_modele FROM modele WHERE nom_modele = 'voilier solaire geonosien'));
```

10)
```
SELECT nom_zone2 FROM distance WHERE nom_zone1 = ANY(SELECT nom_zone FROM station WHERE nom_station = 'Coruscant') AND parsec <= 10 AND nom_zone2 <> nom_zone1;
```

11)
```
SELECT nom_vehicule, nom AS nom_chauffeur, nom_zone, nb_pers AS capacite FROM position NATURAL JOIN chauffeur NATURAL JOIN vehicule NATURAL JOIN modele WHERE nom_zone IS NOT NULL;
```

12)
```
SELECT * FROM chauffeur WHERE id_chauffeur = ANY(SELECT id_chauffeur FROM position WHERE date = '2015-12-11' AND th = 2 AND nom_zone IS NULL) AND id_chauffeur = ANY(SELECT id_chauffeur FROM permis WHERE cat_perm_c = ANY(SELECT cat_perm_c FROM modele WHERE nom_modele = 'cargo YT-300'));
```

13)
  a)
```
UPDATE position set nom_zone = NULL WHERE nom_zone = ANY(SELECT nom_zone FROM station WHERE nom_station = 'Geonosis');
```
  b)
```
UPDATE position set nom_zone = 'Arkanis' WHERE id_chauffeur = ANY(SELECT id_chauffeur FROM chauffeur WHERE nom = 'Skywalker' AND prenom = 'Luke') AND date = '2015-12-11' AND th = 2;
```
  c)
```
INSERT INTO position VALUES ((SELECT id_vehicule FROM vehicule WHERE nom_vehicule = 'Starship troopers'),'2015-12-11',2,(SELECT id_chauffeur FROM chauffeur WHERE nom = 'Windu' AND prenom = 'Mace'),'Cadavine');
```

14)
  a)
```
SELECT nom, nom_modele, nom_zone FROM position NATURAL JOIN vehicule NATURAL JOIN modele NATURAL JOIN chauffeur WHERE nom_zone IS NOT NULL AND date = '2015-12-11' AND th = 2 AND (nom_zone = 'Cadavine' OR nom_zone = ANY(SELECT nom_zone2 FROM distance WHERE nom_zone1 = 'Cadavine' AND parsec < 6 )) and nb_pers >= 18;
```
  b)
```
UPDATE position SET nom_zone = NULL WHERE id_chauffeur = ANY(SELECT id_chauffeur FROM chauffeur WHERE nom = 'Organa') AND date = '2015-12-11' AND th=2;
```
