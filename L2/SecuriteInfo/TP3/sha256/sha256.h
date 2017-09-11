#ifndef SHA256_H
#define SHA256_H

/**************************** DATA TYPES ****************************/
typedef unsigned char BYTE; // 8-bit byte
typedef unsigned int  WORD; // 32-bit word, change to "long" for 16-bit machines

typedef struct {
	BYTE data[64];
	WORD datalen;
	unsigned long long bitlen;
	WORD state[8];
} SHA256_CTX;

/*********************** FUNCTION DECLARATIONS **********************/
void sha256_compress(SHA256_CTX *ctx);
void sha256_init(SHA256_CTX *ctx);
void sha256_compute(SHA256_CTX *ctx, const BYTE data[], size_t len);
void sha256_convert(SHA256_CTX *ctx, BYTE hash[]);

#endif   // SHA256_H
