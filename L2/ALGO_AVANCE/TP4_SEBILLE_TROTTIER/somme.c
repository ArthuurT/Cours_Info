#include <stdio.h>

int add(int a,int b ){
	return a+b;
}

int main (){

					
int n1=-1;
int n2=-2;
					
int resultat = add(n1,n2);
					
if (resultat!=-3)
printf(" le test a raté\n");
else printf(" la somme de %d et %d est %d \n: ",n1, n2,resultat);

n1=1;
n2=-2;
resultat = add(n1,n2);
if (resultat!=-1)
printf(" le test a raté\n");
else printf(" la somme de %d et %d est %d \n: ",n1, n2,resultat);

n1=0;
n2=2;
resultat = add(n1,n2);
if (resultat!=2)
printf(" le test a raté\n");
else printf(" la somme de %d et %d est %d \n: ",n1, n2,resultat);

n1=6;
n2=3;
resultat = add(n1,n2);
if (resultat!=9)
printf(" le test a raté\n");
else printf(" la somme de %d et %d est %d \n: ",n1, n2,resultat);

} 
