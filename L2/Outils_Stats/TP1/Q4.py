#! usr/bin/python 
# -*- coding: ISO-8859-1 -*- 

import numpy as np
import matplotlib.pyplot as plt

fichier = open("données.txt", "r")
t = fichier.readlines()
i = 0
somme = 0

#Conversion du tableau + addition de toutes les valeurs

while i < len(t):
        t[i] = t[i].strip('\n')
        t[i] = float(t[i])
        somme = somme + t[i]
        i = i + 1

#Fonction qui calcule la moyenne

def moyenne():
    moyenne = (somme / len(t))
    moyenne = int(moyenne)
    return moyenne
    

moyenne()   
fichier.close()

n, bins, patches = plt.hist(t, 50, normed = 1, facecolor='r', alpha=0.9)

plt.xlabel('Impots à payer')
plt.ylabel('Proportion')
plt.axis([0, 30, 0, 0.15])
plt.grid(True)
plt.show()
