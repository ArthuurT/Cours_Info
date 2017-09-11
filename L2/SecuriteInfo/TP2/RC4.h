  #ifndef RC4_H
#define RC4_H

/****************** DATA TYPES ********************************/

typedef unsigned char BYTE; // 8-bits byte

typedef struct {
    BYTE s[256];
} RC4_CTX;

/****************** FUNCTION DECLARATIONS *********************/

void print_hexa(BYTE c[], int len);
void rc4_init(RC4_CTX * ctx, const BYTE key[], int keylen);
void rc4_crypt(RC4_CTX * ctx, const BYTE m[], int mlen, BYTE c[], int clen);
void rc4_decrypt(RC4_CTX * ctx, BYTE m[], int mlen, BYTE c[], int clen);
#endif
