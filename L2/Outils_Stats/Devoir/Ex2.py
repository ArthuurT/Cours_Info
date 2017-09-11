#! usr/bin/python
# -*- coding: ISO-8859-1 -*- 

import numpy as np
import matplotlib.pyplot as plt
from math import *

t1 = 0
t2 = 0
t3 = 0
i = 0
x = np.array([6,8,8,10,15,16,17,20,21,21,32,36,41,53,58])
x.sort()
y = np.array([48,43,77,89,50,40,56,62,100,47,71,58,102,35,60])
y.sort()
Y = [None]*len(x)
plt.plot(x,y,"r--")
plt.title("Age du vehicule en fonction de son cout annuel")
plt.xlabel("age du vehicule exprime ee mois")
plt.ylabel("cout de maintenance annuel exprime en centaines d'euros")

def moyenne(n):
    i = 0
    somme = 0
    while i < len(n):
        somme = somme + n[i]
        i = i + 1
        
    moyenne = (somme / len(n))
    moyenne = int(moyenne)
    return moyenne


while i < len(x):
    t1 = t1 + (x[i] - moyenne(x)) * (y[i] - moyenne(y))
    i = i + 1

i = 0

while i < len(x):
    t2 = t2 + (x[i] - moyenne(x)) * (x[i] - moyenne(x))
    i = i + 1


B1 = (t1 / t2)

B0 = (moyenne(y) - B1 * moyenne(x))

r = t1 / ((sqrt(t2))*(sqrt(t3)))

print("B0 = ",B0)
print("B1 = ",B1)

i = 0

while i < len(x):
    Y[i] = B0 + B1*x[i]
    i = i + 1

i = 0

while i < len(Y):
    t3 = t3 + (Y[i] - moyenne(Y)) * (Y[i] - moyenne(Y))
    i = i + 1

r = t1 / ((sqrt(t2))*(sqrt(t3))) 

print("Coeff de correlation de Pearson: ",r)

plt.plot(x,Y)

plt.show()
