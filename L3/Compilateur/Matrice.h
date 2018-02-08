enum eMatrice {maAlpha,maFormuler0,maFormuler1,maInferieur,maPremier0,maPremier1,maSuperieur,maTout,maOmega};
#define knLigneLiM 128
typedef struct{
	int nColonne;
	int nLigne;
	int nSecante;
	long Mat[knLigneLiM][knLigneLiM];
}iMatrice,*piMatrice;
typedef struct{
	int nColonne;
	int nLigne;
	ri Mat[knLigneLiM][knLigneLiM];
}riMatrice;
void MatriceAdditionner(iMatrice *pmA,iMatrice *pmB,iMatrice **ppmC);
void MatriceAllouer(iMatrice **ppmA);
void MatriceAllouer1(iMatrice **ppmCarreh,int nDimension);
void MatriceAllouer2(iMatrice **ppmA,int nLigneEnTout,int nColonneEnTout);
void MatRIceAllouer(riMatrice **ppmK);
void MatRIceAllouer1(riMatrice **ppmKarreh,int nDimension);
void MatRIceAllouer2(riMatrice **ppmK,int nLigneEnTout,int nColonneEnTout);
void MatriceAMORCER();
void MatriceAntisymetriser(iMatrice **ppmC);
void MatRIceAntisymetriser(riMatrice **ppmK);
void MatriceBander(int iBande,iMatrice **ppmC);
void MatriceCanoniser(int maOu,iMatrice **ppmC);
void MatriceCartesier(iMatrice *pmA,iMatrice *pmB,int uH,iMatrice **ppmC);
void MatriceCircuiter(int iBande,iMatrice **ppmC);//diagonale iBande :=1, prolongé circulRt;iBande=0:diagonale principale
int bMatriceContient(iMatrice *pmA,int iValeur);
void MatriceCoupler(iMatrice *pmA,int *pbParfait,int *pbOptimal);
long yMatriceDeterminant(iMatrice *pmA);
void MatriceDecaler(int bLigne,int nDecalageVersLeHautSiPositifEtVersLeBasSinon,int nIndexMin,int nIndexMax,iMatrice **ppmA);//rotations de lignes ou de colonnes
void MatriceDepermuter(iMatrice *pmA);
void MatriceDepuisGraphe(graf *pgG,int bIncidenceSinonCouleur,iMatrice **ppmMatriceDuGraphe);//décrit pgG dans la matrice sommet-sommet supposée allouée
void MatRIceDepuisGraphe(graf *pgG,int bIncidenceSinonCouleur,riMatrice **ppmMatriceDuGraphe);//décrit pgG dans la matrice sommet-sommet supposée allouée
void MatriceDupliquer(iMatrice *pmA,iMatrice *pmB);
int bMatriceEchangerPaire(int bLigne,int uA,int uB,int bVoir,iMatrice **ppmC);
void MatriceEchangerSingleton(int bLigne,int uA,int uB,int bVoir,iMatrice **ppmC);
void MatriceFibonaccier(int nCoteh,iMatrice **ppmC);
void MatriceFoisColonne(iMatrice *pmA,iMatrice *pmB,int uColonneDansB,iMatrice **ppmC);
void MatriceFoisser(int iFois,iMatrice **ppmC);
void MatriceGrapher(iMatrice *pmA,graf *pgA);//convertit la matrice sommet-sommet en graphe
void MatriceHasarder(iMatrice *pmC,int iEmpan);
void MatriceIdentiter(iMatrice **ppmC);
void MatriceLosanger(int nOffsetDepuisDiagonalePrincipale,int nMarqueInitiale,iMatrice **ppmC);
void MatriceMarner(iMatrice *pmA,int *piValeurMin,int *piValeurMax);
void MatriceMultiplier(iMatrice *pmA,iMatrice *pmB,iMatrice **ppmC);
int bMatricePositive(iMatrice *pmA);
void MatricePositiver(iMatrice *pmA);
void MatricePuissancer(iMatrice *pmA,int nPuissance,iMatrice **ppmC);//O(nPuissance*N3)
void MatriceQuadripoler(int nTest,int bBoucler,iMatrice **ppmQ);
void MatriceRazer(iMatrice **ppmA);
int bMatriceSingulariser(graf *pgG);
int nMatriceSignature(graf *pgG,int emMode);
int bMatriceSingulierh(graf *pgG,int emMode);
void MatriceSymetriser(iMatrice **ppmA);
void MatRIceSymetriser(riMatrice **ppmK);
void MatriceINITIALISER();
int bMatryceSinguliere(graf *pgG);
void MatriceTESTER(int iTest);
void MatriceTransposer(iMatrice *pmA);
void MatriceUnifier(iMatrice *pmA);
void MatRIceUnifier(riMatrice *pmK);
void MatriceUniter(iMatrice *pmA);
void MatriceVoir(char *sMessage,iMatrice *pmA);//matrice d'entiers
void MatRIceVoir(char *sMessage,riMatrice *pmA);//matrice de nombres complexes
void MatriceVoirLitteral(int bLitteral);//spécifie le mode d'affichage de MatriceVoir: affichage d'un B si la valeur à afficher est 2. 
void MatriceZeroter(iMatrice *pmA,int uHauteur,iMatrice *pmAh);
