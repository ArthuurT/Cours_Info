#ifndef SHA512_H
#define SHA512_H

/**************************** DATA TYPES ****************************/
typedef unsigned char BYTE; // 8-bit byte
typedef unsigned long long WORD; // 64-bit word, change to "long" for 16-bit machines

typedef struct {
	BYTE data[128];
	WORD datalen;
	unsigned long long bitlen;
	WORD state[8];
} SHA512_CTX;

/*********************** FUNCTION DECLARATIONS **********************/
void sha512_compress(SHA512_CTX *ctx);
void sha512_init(SHA512_CTX *ctx);
void sha512_compute(SHA512_CTX *ctx, const BYTE data[], size_t len);
void sha512_convert(SHA512_CTX *ctx, BYTE hash[]);

#endif   // SHA512_H
