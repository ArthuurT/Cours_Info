#include "Outil.h"
#include "G1.h"
char *sMOT;
int bG1AmorceR=kF;
// Grammaire algébrique (1 règle):
            // (a) S->B+B
// Grammaire homogène (5 règles):
            // (1) S->B+K
            // (2) K->B+P
            // (3) P->p
            // (4) B->b
            // (5) A->a
int bA(int iDebut,int *piFin);
int bB(int iDebut,int *piFin);
int bK(int iDebut,int *piFin);
int bP(int iDebut,int *piFin);
int bS(int iDebut,int *piFin);

void G1AMORCER(){
    bG1AmorceR=kV;
}//G1AMORCER

void G1INITIALISER(){
    Assert1("G1INITIALISER",bG1AmorceR);
}//G1INITIALISER

void G1TESTER(int iTest){
    int bEngendre,iFin,bSucces;
    Assert1("G1TESTER0",bG1AmorceR);
    //sMOT:=mot à tester selon iTest
        switch(iTest){
            case 1: sMOT="aab";break;
            case 2: sMOT="aaba";break;
            default:Assert1("G1TESTER1",0);break;
        }
    bSucces=bS(0,&iFin);
    bEngendre=bSucces && strlen(sMOT)==iFin;
    printf("%s: %s %s engendré par la grammaire décrite dans \"G1.c\".\n",(bEngendre)? "SUCCES": "ECHEC ",sG(sMOT),sEst(bEngendre));
}//G1TESTER

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

int bK(int iDebut,int *piFin){
    //K->B+P
    int iFin;
    int bSucces=bB(iDebut,&iFin) || bP(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bK

int bP(int iDebut,int *piFin){
    //P->p
    int bSucces = sMOT[iDebut]=='p';
    *piFin = (bSucces) ? iDebut+1 : iDebut;
    return(bSucces);
}//bP

int bS(int iDebut,int *piFin){
    //S->B+K
    int iFin;
    int bSucces=bB(iDebut,&iFin) || bK(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bS

