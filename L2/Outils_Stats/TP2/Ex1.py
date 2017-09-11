#! usr/bin/python
# -*- coding: ISO-8859-1 -*-

import re
a = {}

def add_dico(dico,key,value):
    if key in dico:
        print "Cle <",key,"> deja existante"
        print "Ajout impossible"
    else:
        dico[key] = value


def valeur_dico(dico):
    print "Valeur du dico:"
    for valeur in dico.values():
        print(valeur)

def supp_dico(dico,car):
    if car in dico:
        del(dico[car])
    else:
        print "Cle <",car,"> inexistante"
        print "Suppression impossible"



add_dico(a,"bonjour","hello")
add_dico(a,"merci","tank you")
add_dico(a,"merci","gracias")
supp_dico(a,"hey")
valeur_dico(a)
