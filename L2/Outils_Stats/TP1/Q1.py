#! usr/bin/python 
# -*- coding: ISO-8859-1 -*- 

import numpy as np

def nb_perso():
    n = input("Entrez le nombre de personnages a creer : ")
    nb = int(n)
    milieu = 70
    ecart = 10
    poids = np.random.normal(milieu,ecart,nb)
    poids = poids // 1
    milieu = 170
    ecart = 10
    taille = np.random.normal(milieu,ecart,nb)
    taille = taille // 1

    for i in range (nb):
            print("Perso numero ",i,":")
            print("Poids:",poids[i],"kg")
            print("Taille:",taille[i],"cm")
            print("\n")
    

nb_perso()

