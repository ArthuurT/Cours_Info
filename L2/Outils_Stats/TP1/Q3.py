import numpy as np
import matplotlib.pyplot as plt

#definition de la loi normale
n = 100 #Nombre de lancers
p = 0.1 #Proba du succès
s = np.random.binomial(n, p, 10000) #Epreuve répété 10.000 fois

#100 sous intervalles
count, bins, ignored = plt.hist(s, 100, normed=True)

#créer le graphique
plt.plot(bins, 1/(p * np.sqrt(2 * np.pi)) *
        np.exp( - (bins - n)**2 / (2 * p**2) ),
        linewidth=2, color='r')

#affiche le graphique
plt.show()
