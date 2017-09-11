# SEANCE 3 - L'ECOLE

##### Trottier Arthur - L2 SPI

## 1) Implémenation des tables

```
CREATE TABLE eleve (
  id_eleve int PRIMARY KEY,
  nom varchar,
  prenom varchar,
  date_arr date
  );
```

```
CREATE TABLE scolarite (
  id_classe int,
  annee int,
  id_eleve int,
  moy float,
  PRIMARY KEY (annee,id_eleve),
  FOREIGN KEY (id_classe) REFERENCES classe (id_classe),
  FOREIGN KEY (id_eleve) REFERENCES eleve (id_eleve)
  );
```

```
CREATE TABLE classe (
  id_classe int PRIMARY KEY,
  nom_classe varchar,
  nom_batiment varchar
  );
```

```
CREATE TABLE prof (
  id_prof int PRIMARY KEY,
  nom varchar,
  prenom varchar,
  date_arr date
  );
```

```
CREATE TABLE matiere(
  id_matiere int PRIMARY KEY,
  nom_mat varchar,
  descr text
  );
```

```
CREATE TABLE enseignement(
  id_classe int,
  id_prof int,
  annee int,
  id_matiere int,
  PRIMARY KEY (id_classe,id_prof,annee),
  FOREIGN KEY (id_classe) REFERENCES classe (id_classe),
  FOREIGN KEY (id_prof) REFERENCES prof (id_prof),
  FOREIGN KEY (id_matiere) REFERENCES matiere (id_matiere)
  );
```
## 2) Insertion de données dans la table

#### 3 matières sont enseignées: le C, la BDD et la fouille de données.

```
INSERT INTO matiere VALUES (01,'C', 'Apprentissage du language C');
INSERT INTO matiere VALUES (02,'BDD', 'Decouverte de la base de données');
INSERT INTO matiere VALUES (03,'FDD', 'Apprentissage de la fouille de données');
```
#### 2 prof sont connus: Loïc Barrault, arrivé en septembre 2009 et Nathalie Camelin, arrivée en septembre 2011.

```
INSERT INTO prof VALUES (01,'Barrault','Loïc','September 1, 2009');
INSERT INTO prof VALUES (02,'Camelin','Nathalie','September 1, 2011');
```
#### Dans le batiment IC2, on trouve les classes L2 et M2.

```
INSERT INTO classe VALUES (01,'L2','IC2');
INSERT INTO classe VALUES (02,'M2','IC2');
```
#### Depuis 2011, Nathalie Camelin a enseigné aux L2 la base de données et depuis 2012 la fouille de données aux M2. Loïc Barrault a enseigné le C aux L2 depuis 2010.

```
INSERT INTO enseignement VALUES (01,02,2011,02);
INSERT INTO enseignement VALUES (02,02,2012,03);
INSERT INTO enseignement VALUES (01,01,2010,01);
```
#### Saisir 3 de vos camarades en L2 et 4 en M2.

```
INSERT INTO eleve VALUES (01,'Trottier','Arthur','September 14, 2015');
INSERT INTO eleve VALUES (02,'Pelloin','Valentin','September 14, 2015');
INSERT INTO eleve VALUES (03,'Sebille','Florian','September 14, 2015');
INSERT INTO eleve VALUES (04,'Hollande','François','September 14, 2012');
INSERT INTO eleve VALUES (05,'Ribéry','Franck','September 14, 2012');
INSERT INTO eleve VALUES (06,'Stephen','Curry','September 14, 2012');
INSERT INTO eleve VALUES (07,'Dupont','Jean-Marcel','September 14, 2012');
```
#### Ajout de détails concernant la scolarité.

Élèves en L2 en 2016:

```
INSERT INTO scolarite VALUES (01,2016,01,15);
INSERT INTO scolarite VALUES (01,2016,02,20);
INSERT INTO scolarite VALUES (01,2016,03,16);
```
Élèves en L2 en 2013:

```
INSERT INTO scolarite VALUES (01,2013,04,11);
INSERT INTO scolarite VALUES (01,2013,05,09);
INSERT INTO scolarite VALUES (01,2013,06,14);
```

Élèves en M2 en 2016:

```
INSERT INTO scolarite VALUES (02,2016,04,10);
INSERT INTO scolarite VALUES (02,2016,05,07);
INSERT INTO scolarite VALUES (02,2016,06,12);
```

## 3) Requêtes

#### a) En quelle classe est "nom 1" en 2016 ?

```
SELECT nom_classe FROM classe WHERE id_classe = any(SELECT id_classe FROM scolarite WHERE id_eleve = 1 AND annee = 2016);
```

#### b) Quelle est la moyenne générale de la classe L2 de 2016 ?

```
SELECT AVG(moy) AS Moyenne FROM scolarite WHERE id_classe = 1;
```

#### c) Combien de matières ont été enseignées en 2016 ?

```
SELECT COUNT(*) AS NombreMatiere FROM matiere WHERE id_matiere = ALL(SELECT id_matiere FROM enseignement WHERE id_classe = ALL(SELECT id_classe FROM scolarite WHERE annee = 2016));
```

#### d) Combien de matières ont été enseignées par Nathalie Camelin en 2016 ?

```
SELECT COUNT(*) AS NombreMatiere FROM matiere WHERE id_matiere = ANY(SELECT id_matiere FROM enseignement WHERE id_prof = 2 AND id_classe = ANY(SELECT id_classe FROM scolarite WHERE annee = 2016));
```

#### e) À combien de classes Loïc Barrault a-t-il enseigné le C ?

```
SELECT
  COUNT DISTINCT(id_classe, annee) AS NbClasse
FROM
  classe
WHERE
  id_prof = ANY(SELECT id_prof FROM prof WHERE nom = 'Barrault' AND id_matiere = ANY(SELECT id_matiere FROM matiere WHERE nom_mat = 'C');
```
#### f) À quelle classe appartient l’élève qui a eu la meilleure moyenne générale en 2016 ?

```
SELECT
  nom_classe
FROM
  classe
WHERE
  id_classe = ANY(SELECT id_classe FROM scolarite
WHERE
  moy = ANY(SELECT MAX(moy) FROM scolarite)
AND
  annee = 2016);
```

#### g) Quelle heure est-il ?

```
SELECT current_time;
```

#### h) Donner la liste des personnes dont le nom est alphabétiquement compris entre ‘C’ et ‘H’.

```
SELECT nom,prenom FROM prof
UNION
SELECT nom,prenom FROM eleve
WHERE nom =
```
