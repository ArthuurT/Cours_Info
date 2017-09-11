#include <stdlib.h>
#include "RC4.h"
#define N 255



void swap(BYTE * a, BYTE * b){
  BYTE  tempo;
  tempo = *a;
  *a = *b;
  *b = tempo;
}


void rc4_init(RC4_CTX * ctx, const BYTE key[], int keylen){

  int i, j;

  BYTE T[N];  //tableau t temporaire (suite pseudo-aléatoire)

  //Initialisation de s et T
  for(i = 0; i < N+1; i++){
    ctx->s[i] = i;
    T[i] = key[i%keylen];
  }

  //Permutation
  j = 0;
  for(i = 0; i < N+1; i++){
    j = (j + ctx->s[i] + T[i])%(N+1);
    swap(&(ctx->s[i]),&(ctx->s[j]));
  }
}

void rc4_crypt(RC4_CTX * ctx, const BYTE m[], int mlen, BYTE c[], int clen){

  int i = 0; int j = 0; int k = 0;
  BYTE t;

  for(k = 0; k < mlen; k++){
    i = (i+1)%(N+1);
    j = (j+(ctx->s[i]))%(N+1);
    swap(&(ctx->s[i]),&(ctx->s[j]));
    t = ((ctx->s[i])+(ctx->s[j]))%(N+1);
    c[k] = (m[k]) ^ (ctx->s[t]);
  }
}

void rc4_decrypt(RC4_CTX * ctx, BYTE m[], int mlen, BYTE c[], int clen){
  int i = 0; int j = 0; int k = 0;
  BYTE t;

  for(k = 0; k < clen; k++){
    i = (i+1)%(N+1);
    j = (j+(ctx->s[i]))%(N+1);
    swap(&(ctx->s[i]),&(ctx->s[j]));
    t = ((ctx->s[i])+(ctx->s[j]))%(N+1);
    m[k] = (c[k]) ^ (ctx->s[t]);
  }
}
