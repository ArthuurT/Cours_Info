#include "Outil.h"
#include "Grammaire.h"
char *sMOT;
int bGrammaireAmorceR=kF;
// Grammaire algébrique (1 règle):
            // (a) S->A.S.B+A.B
// Grammaire homogène (5 règles):
            // (1) S->P+Q
            // (2) P->A.S.B
            // (3) Q->A.B
            // (4) A->a
            // (5) B->b
int bA(int iDebut,int *piFin);
int bB(int iDebut,int *piFin);
int bP(int iDebut,int *piFin);
int bQ(int iDebut,int *piFin);
int bS(int iDebut,int *piFin);

void GrammaireAMORCER(){
    bGrammaireAmorceR=kV;
}//GrammaireAMORCER

void GrammaireINITIALISER(){
    Assert1("GrammaireINITIALISER",bGrammaireAmorceR);
}//GrammaireINITIALISER

void GrammaireTESTER(int iTest){
    int bEngendre,iFin,bSucces;
    Assert1("GrammaireTESTER0",bGrammaireAmorceR);
    //sMOT:=mot à tester selon iTest
        switch(iTest){
            case 1: sMOT="aab";break;
            case 2: sMOT="aaba";break;
            default:Assert1("GrammaireTESTER1",0);break;
        }
    bSucces=bS(0,&iFin);
    bEngendre=bSucces && nChaineLg(sMOT)==iFin;
    printf("%s: %s %s engendré par la grammaire décrite dans \"Grammaire.c\".\n",(bEngendre)? "SUCCES": "ECHEC ",sG(sMOT),sEst(bEngendre));
}//GrammaireTESTER

int bA(int iDebut,int *piFin){
    //A->a
    int bSucces = sMOT[iDebut]=='a';
    *piFin = (bSucces) ? iDebut+1 : iDebut;
    return(bSucces);
}//bA

int bB(int iDebut,int *piFin){
    //B->b
    int bSucces = sMOT[iDebut]=='b';
    *piFin = (bSucces) ? iDebut+1 : iDebut;
    return(bSucces);
}//bB

int bP(int iDebut,int *piFin){
    //P->A.S.B
    int iA=iDebut,iB,iC,iD;
    int bSucces=bA(iA,&iB) && bS(iB,&iC) && bB(iC,&iD);
    *piFin=(bSucces)?iD:iDebut;
    return(bSucces);
}//bP

int bQ(int iDebut,int *piFin){
    //Q->A.B
    int iA=iDebut,iB,iC;
    int bSucces=bA(iA,&iB) && bB(iB,&iC);
    *piFin=(bSucces)?iC:iDebut;
    return(bSucces);
}//bQ

int bS(int iDebut,int *piFin){
    //S->P+Q
    int iFin;
    int bSucces=bP(iDebut,&iFin) || bQ(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bS

