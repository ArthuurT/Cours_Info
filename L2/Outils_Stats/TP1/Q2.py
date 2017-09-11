import numpy as np
import matplotlib.pyplot as plt

#definition de la loi normale
mu = 0
sigma = 2
s = np.random.normal(mu, sigma, 1000)

#100 sous intervalles
count, bins, ignored = plt.hist(s, 100, normed=True)

#créer le graphique
plt.plot(bins, 1/(sigma * np.sqrt(2 * np.pi)) *
        np.exp( - (bins - mu)**2 / (2 * sigma**2) ),
        linewidth=2, color='r')

#affiche le graphique
plt.show()
