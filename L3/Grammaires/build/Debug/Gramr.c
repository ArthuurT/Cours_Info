#include "Outil.h"
#include "Gramr.h"
#define kuCaractereMaX 64
char *sMOT[1+kuCaractereMaX];
int bGramrAmorceR;
int bA(int iDebut,int *piFin);
int bB(int iDebut,int *piFin);
int bS(int iDebut,int *piFin);
int bT(int iDebut,int *piFin);
int bU(int iDebut,int *piFin);

GramrAMORCER(){
}//GramrAMORCER

GramrINITIALISER(){
}//GramrINITIALISER

GramrTESTER(int iTest){
    int bEngendre,iFin,bSucces;
    //sMOT:=mot à tester selon iTest
        switch(iTest){
            case 1: sMOT="abcd";break;
            default:Assert1("GramrTESTER",0);break;
        }
    bSucces=bS(0,&iFin);
    bEngendre=bSucces && strlen(sMOT)==iFin;
    printf("%s %s engendré par la grammaire.\n",sG(sMOT),sEst(bEngendre));
}//GramrTESTER

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

int bS(int iDebut,int *piFin){
    //S->T+U+B
    int iFin;
    int bSucces=bT(iDebut,&iFin) || bU(iDebut,&iFin) || bB(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bS

int bT(int iDebut,int *piFin){
    //T->A.U.B
    int iA=iDebut,iB,iC,iD;
    int bSucces=bA(iA,&iB) && bU(iB,&iC) && bB(iC,&iD);
    *piFin=(bSucces)?iD:iDebut;
    return(bSucces);
}//bT

int bU(int iDebut,int *piFin){
    //U->A+B
    int iFin;
    int bSucces=bA(iDebut,&iFin) || bB(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bU

