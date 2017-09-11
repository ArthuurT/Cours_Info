int taille ;						/*!< Nombre de noeuds dans l'arbre */
noeud_t * racine ;					/*!< Noeud racine de l'arbre */
err_t (*affecter)( void * e1 , void * e2 ) ;		/*!< Fonction d'affectation d'un element */
err_t (*detruire)( void * e) ;				/*!< Fonction de destruction d'un element */

