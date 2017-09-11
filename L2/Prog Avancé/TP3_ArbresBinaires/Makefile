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
fich_obj_test_ab_individus=test_ab_individus.o ab.o noeud.o individu.o commun.o
fich_obj_test_ab_fractions=test_ab_fractions.o ab.o noeud.o fraction.o commun.o
fich_obj_test_ab_mystrings=test_ab_mystrings.o ab.o noeud.o mystring.o commun.o
fich_obj_animaux=animaux.o ab_animaux.o ab.o noeud.o mystring.o commun.o
fich_obj_test_ab_fonctions=test_ab_fonctions.o ab.o ab_fonctions.o noeud.o individu.o commun.o

#
# Tests (executables+objets)
#

BIN = test_commun test_individu test_fraction test_mystring test_liste_individus test_liste_fractions test_liste_mystrings test_liste test_noeud test_ab_individus test_ab_fractions test_ab_mystrings animaux test_ab_fonctions

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

test_ab_individus : $(fich_obj_test_ab_individus) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_ab_individus) -o test_ab_individus 

test_ab_individus.o : test_ab_individus.c ab.h individu.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_ab_individus.c -o test_ab_individus.o -I./ 

test_ab_fractions : $(fich_obj_test_ab_fractions) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_ab_fractions) -o test_ab_fractions 

test_ab_fractions.o : test_ab_fractions.c ab.h fraction.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_ab_fractions.c -o test_ab_fractions.o -I./ 

test_ab_mystrings : $(fich_obj_test_ab_mystrings) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_ab_mystrings) -o test_ab_mystrings 

test_ab_mystrings.o : test_ab_mystrings.c ab.h mystring.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_ab_mystrings.c -o test_ab_mystrings.o -I./ 

animaux : $(fich_obj_animaux) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_animaux) -o animaux 

animaux.o : animaux.c ab_animaux.h 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) animaux.c -o animaux.o -I./ 


test_ab_fonctions : $(fich_obj_test_ab_fonctions) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_ab_fonctions) -o test_ab_fonctions 

test_ab_fonctions.o : test_ab_fonctions.c ab.h individu.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_ab_fonctions.c -o test_ab_fonctions.o -I./ 

#
# Modules
#

OBJ= commun.o individu.o fraction.o mystring.o liste.o noeud.o ab.o ab_fonctions.o ab_animaux.o

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

ab.o : ab.c ab.h 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) ab.c -o ab.o -I./

ab_fonctions.o : ab_fonctions.c ab_fonctions.h 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) ab_fonctions.c -o ab_fonctions.o -I./

ab_animaux.o : ab_animaux.c ab_animaux.h 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) ab_animaux.c -o ab_animaux.o -I./


#
# Headers 
#

liste.h : commun.h
	touch liste.h

noeud.h : commun.h
	touch noeud.h

ab.h : noeud.h
	touch ab.h

ab_fonctions.h : ab.h
	touch ab_fonctions.h

ab_animaux.h : ab.h mystring.h
	touch ab_animaux.h

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
	- rm test_ab_individus
	- rm test_ab_fractions
	- rm test_ab_mystrings
	- rm animaux
	- rm test_ab_fonctions

tests : 
	@ echo "********************\nTest type individu_t\n****************************************"		                ; ./test_individu	                         ; echo "\n"
	@ echo "****************************************\nTest type fraction_t\n****************************************"	; ./test_fraction                                ; echo "\n"
	@ echo "****************************************\nTest type string_t\n****************************************"		; ./test_mystring < Fichiers/test_mystring.stdin ; echo "\n"
	@ echo "****************************************\nTest liste d'individus \n****************************************"	; ./test_liste_individus 5	                 ; echo "\n"
	@ echo "****************************************\nTest liste de fractions \n****************************************"	; ./test_liste_fractions 5	                 ; echo "\n"
	@ echo "****************************************\nTest liste de strings \n****************************************"	; ./test_liste_mystrings 5	                 ; echo "\n"
	@ echo "****************************************\nTest global de liste_t  \n****************************************"	; ./test_liste 5	                         ; echo "\n"
	@ echo "****************************************\nTest de noeud_t  \n****************************************"	        ; ./test_noeud	                                 ; echo "\n"

tags : 
	etags --language=c  *.[ch] --output=AB.TAGS

dist : 
	- make clean 
	- mkdir TP_AB
	- cp *.[ch] Makefile* TP_AB/.
	- cp -R Fichiers TP_AB/.
	- rm TP_AB.tar.gz
	- tar cvf TP_AB.tar TP_AB
	- gzip TP_AB.tar 
	- rm -R TP_AB 
