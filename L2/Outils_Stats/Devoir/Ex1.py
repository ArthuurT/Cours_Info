#! usr/bin/python
# -*- coding: ISO-8859-1 -*-

import numpy as np
import matplotlib.pyplot as plt

i = 0
EffHomme = np.array([3386,3466,3663,3753,3971,3934,3915,4158,4763,4558,4573,4693,4655,4564,4496])
EffFemme = np.array([3506,3484,3628,3753,3813,3811,3911,4276,4972,4866,4834,4863,4699,4174,4241])



plt.hist(EffHomme, 30, facecolor = 'b', alpha = 0.9, label = "Hommes")
plt.hist(EffFemme, 30, facecolor = 'r', alpha = 0.9,label = "Femmes")

plt.title("Effectif etudiants masculins et feminins entre 2001 et 2015")
plt.xlabel("Annees de 2001 à 2015")
plt.ylabel("Proportion")

def moyenne(n):
    return sum(n,0.0) / len(n)

def variance(n):
    m = moyenne(n)
    return moyenne([(x-m)**2 for x in n])

def ecartype(n):
    return variance(n)**0.5

print("Moyenne effectif des femmes entre 2001 et 2015: ",(moyenne(EffFemme)//1))
print("Ecart-type: ",(ecartype(EffFemme)//1))

plt.legend()
plt.show()

mu = moyenne(EffFemme)
sigma = ecartype(EffFemme)

s = np.random.normal(mu,sigma,1000)

count, bins, ignored = plt.hist(s, 100, normed=True)

plt.plot(bins, 1/(sigma * np.sqrt(2 * np.pi)) *
        np.exp( - (bins - mu)**2 / (2 * sigma**2) ),
        linewidth=2, color='r')
plt.title("Loi normale correspondant à l'effectif des femmes entre 2001 et 2015")
plt.xlabel("Nombre de femmes en moyenne entre 2001 et 2015 après 1000 répétitions")
plt.ylabel("Proportion")

plt.show()

