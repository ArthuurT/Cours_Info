include Makefile.compilation

#
# Objets
#

fich_obj_test_commun=test_commun.o commun.o
fich_obj_test_individu=test_individu.o individu.o commun.o
fich_obj_test_fraction=test_fraction.o fraction.o commun.o
fich_obj_test_mystring=test_mystring.o mystring.o commun.o
fich_obj_test_liste_individus=test_liste_individus.o liste.o individu.o commun.o
fich_obj_test_liste_fractions=test_liste_fractions.o liste.o fraction.o commun.o
fich_obj_test_liste_mystrings=test_liste_mystrings.o liste.o mystring.o commun.o
fich_obj_test_liste=test_liste.o liste.o individu.o fraction.o mystring.o commun.o
fich_obj_test_noeud=test_noeud.o noeud.o individu.o commun.o
fich_obj_test_abr_individus=test_abr_individus.o abr.o noeud.o abr_fonctions.o liste.o individu.o commun.o 
fich_obj_test_abr_fractions=test_abr_fractions.o abr.o noeud.o abr_fonctions.o liste.o fraction.o commun.o
fich_obj_test_abr_mystrings=test_abr_mystrings.o abr.o noeud.o abr_fonctions.o liste.o mystring.o commun.o
fich_obj_test_abr_fonctions=test_abr_fonctions.o abr.o abr_fonctions.o noeud.o liste.o individu.o commun.o

fich_obj_dico_liste=dico_liste.o liste.o mystring.o commun.o
fich_obj_dico_abr=dico_abr.o abr.o noeud.o abr_fonctions.o liste.o mystring.o commun.o
fich_obj_dico_avl=dico_avl.o avl.o abr.o noeud.o abr_fonctions.o liste.o mystring.o commun.o


#
# Tests (executables+objets)
#

BIN = test_commun test_individu test_fraction test_mystring \
	test_liste_individus test_liste_fractions test_liste_mystrings test_liste \
	test_noeud \
	test_abr_individus test_abr_fractions test_abr_mystrings test_abr_fonctions \
	dico_liste dico_abr dico_avl

test_commun : $(fich_obj_test_commun) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_commun) -o test_commun 

test_commun.o : test_commun.c commun.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_commun.c -o test_commun.o -I./ 

test_individu : $(fich_obj_test_individu) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_individu) -o test_individu 

test_individu.o : test_individu.c individu.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_individu.c -o test_individu.o -I./ 

test_fraction : $(fich_obj_test_fraction) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_fraction) -o test_fraction 

test_fraction.o : test_fraction.c fraction.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_fraction.c -o test_fraction.o -I./ 

test_mystring : $(fich_obj_test_mystring) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_mystring) -o test_mystring 

test_mystring.o : test_mystring.c mystring.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_mystring.c -o test_mystring.o -I./ 

test_liste_individus : $(fich_obj_test_liste_individus) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_liste_individus) -o test_liste_individus 

test_liste_individus.o : test_liste_individus.c liste.h individu.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_liste_individus.c -o test_liste_individus.o -I./ 

test_liste_fractions : $(fich_obj_test_liste_fractions) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_liste_fractions) -o test_liste_fractions 

test_liste_fractions.o : test_liste_fractions.c liste.h fraction.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_liste_fractions.c -o test_liste_fractions.o -I./ 

test_liste_mystrings : $(fich_obj_test_liste_mystrings) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_liste_mystrings) -o test_liste_mystrings 

test_liste_mystrings.o : test_liste_mystrings.c liste.h mystring.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_liste_mystrings.c -o test_liste_mystrings.o -I./ 

test_liste : $(fich_obj_test_liste) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_liste) -o test_liste 

test_liste.o : test_liste.c liste.h individu.h fraction.h mystring.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_liste.c -o test_liste.o -I./ 

test_noeud : $(fich_obj_test_noeud) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_noeud) -o test_noeud 

test_noeud.o : test_noeud.c noeud.h individu.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_noeud.c -o test_noeud.o -I./ 

test_abr_individus : $(fich_obj_test_abr_individus) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_abr_individus) -o test_abr_individus 

test_abr_individus.o : test_abr_individus.c abr.h individu.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_abr_individus.c -o test_abr_individus.o -I./ 

test_abr_fractions : $(fich_obj_test_abr_fractions) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_abr_fractions) -o test_abr_fractions 

test_abr_fractions.o : test_abr_fractions.c abr.h fraction.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_abr_fractions.c -o test_abr_fractions.o -I./ 

test_abr_mystrings : $(fich_obj_test_abr_mystrings) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_abr_mystrings) -o test_abr_mystrings 

test_abr_mystrings.o : test_abr_mystrings.c abr.h mystring.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_abr_mystrings.c -o test_abr_mystrings.o -I./ 

test_abr_fonctions : $(fich_obj_test_abr_fonctions) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_abr_fonctions) -o test_abr_fonctions 

test_abr_fonctions.o : test_abr_fonctions.c abr.h individu.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_abr_fonctions.c -o test_abr_fonctions.o -I./ 


dico_liste : $(fich_obj_dico_liste) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_dico_liste) -o dico_liste 

dico_liste.o : dico_liste.c liste.h mystring.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) dico_liste.c -o dico_liste.o -I./ 

dico_abr : $(fich_obj_dico_abr) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_dico_abr) -o dico_abr 

dico_abr.o : dico_abr.c liste.h mystring.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) dico_abr.c -o dico_abr.o -I./ 

dico_avl : $(fich_obj_dico_avl) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_dico_avl) -o dico_avl 

dico_avl.o : dico_avl.c liste.h mystring.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) dico_avl.c -o dico_avl.o -I./ 


#
# Modules
#

OBJ= commun.o individu.o fraction.o mystring.o liste.o noeud.o abr.o abr_fonctions.o avl.o

commun.o : commun.c commun.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) commun.c -o commun.o -I./

individu.o : individu.c individu.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) individu.c -o individu.o -I./

fraction.o : fraction.c fraction.h 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) fraction.c -o fraction.o -I./

mystring.o : mystring.c mystring.h 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) mystring.c -o mystring.o -I./

liste.o : liste.c liste.h 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) liste.c -o liste.o -I./

noeud.o : noeud.c noeud.h 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) noeud.c -o noeud.o -I./

abr.o : abr.c abr.h 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) abr.c -o abr.o -I./

abr_fonctions.o : abr_fonctions.c abr_fonctions.h 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) abr_fonctions.c -o abr_fonctions.o -I./

avl.o : avl.c avl.h 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) avl.c -o avl.o -I./

#
# Headers 
#

liste.h : commun.h
	touch liste.h

noeud.h : commun.h
	touch noeud.h

abr.h : noeud.h
	touch abr.h

abr_fonctions.h : abr.h liste.h
	touch abr_fonctions.h

avl.h : abr.h
	touch avl.h

#
#
#

all : $(BIN) $(OBJ)

clean :
	- rm  *~ Fichiers/*~
	- rm  *.o
	- rm test_individu
	- rm test_fraction
	- rm test_mystring
	- rm test_liste_individus
	- rm test_liste_fractions
	- rm test_liste_mystrings
	- rm test_liste
	- rm test_noeud
	- rm test_abr_individus
	- rm test_abr_fractions
	- rm test_abr_mystrings
	- rm test_abr_fonctions
	- rm dico_liste
	- rm dico_abr
	- rm dico_avl

tests : 
	./test_individu
	./test_fraction
	./test_mystring < Fichiers/test_mystring.stdin
	./test_liste_individus 5
	./test_liste_fractions 5
	./test_liste_mystrings 5
	./test_liste 5
	- ./test_noeud
	- ./test_abr_individus 2
	- ./test_abr_fractions 2
	- ./test_abr_mystrings 2
	- ./test_abr_fonctions 2

tags : 
	etags --language=c  *.[ch] --output=ABR.TAGS
