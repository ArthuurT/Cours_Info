/* TP 4 - Mise en oeuvre de listes de doublets */

typedef struct {int nb_occ; int valeur;} t_doublet;

void init_liste(void);
int liste_vide(void);
int hors_liste(void);
void en_tete(void);
void en_queue(void);
void precedent(void);
void suivant(void);
void valeur_elt(t_doublet* d);
void modif_elt(t_doublet d);
void oter_elt(void);
void ajout_droit(t_doublet d);
void ajout_gauche(t_doublet d);
