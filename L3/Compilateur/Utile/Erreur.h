enum eErreur {eLimite0,
	eAlex0,eAlexReel,eAlex1,
	eSynt0,eSyntInstruction,eSyntLivre,eSyntNom,eSyntProgramme,eSyntSeparateur,eSyntSuite,eSynt1,
	eSem0,eSemDate,eSemDoublon,eSemHoraire,eSemInscrit,eSemLivreDispo,eSemLivreInconnu,eSemLivrePris,eSemNonInscrit,eSemPrix,eSem1,
	eLimite1};
void ErreurAfficher(int uLigne);
void ErreurAfficherTout();
void ErreurAMORCER();
void ErreurEmpiler(int nErreurNumero, int nLexeme);
int bErreurEmpiler(int nErreurNumero, int nLexeme);
int nErreurEnTout();
void ErreurINITIALISER();
void ErreurTESTER(int iTest);