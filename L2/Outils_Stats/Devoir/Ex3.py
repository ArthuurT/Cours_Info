from math import *

#1) Lorsque l'on multiplie un grand nombre de valeurs proches de 0 à l'aide d'un
#   ordinateur, celui-ci nous l'exprime en écriture scientifique c'est à dire un
#   nombre entre 1 et 10 (avec beaucoup de chiffres après la virgule) multiplié
#   par une puissance de 10 (ici négative). Avec l'ordinateur actuel on monte
#   jusqu'à la puissance -322 (exemple ci-dessous). Sinon la valeur retourné est 0 (out of memory).
#
#2) Pour se simplifier, il est possible de travailler uniquement avec les puissances
#   et ainsi conserver uniquement l'ordre de grandeur.
#   Ex : 0.0002 = 2 * 10^-4 -> on conserve uniquement 10^-4
#        0.0024 = 2.4 * 10^-3 -> on conserve uniquement 10^-3
#   Le calcul de puissance étant très simple: 0.0002 * 0.0024 environ égal à (10^-4)*(10^-3) = 10^-7 (ordre de grandeur)

n = 0.002 ** 119
print(n)

n = 0.002 ** 120
print(n)



