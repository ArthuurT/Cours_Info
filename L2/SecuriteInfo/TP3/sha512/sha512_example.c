#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "sha512.h"

void print_hash(unsigned char hash[])
{
   int idx;
   for (idx=0; idx < 64; idx++)
      printf("%02x",hash[idx]);
   printf("\n");
}

int main()
{
	unsigned char text1[]={"01234567879"},
                  text2[]={"0123456787901234567879012345678790123456787901234567879"},
                  hash[64];
                 
	SHA512_CTX ctx;                 

   	// Hash one
	sha512_init(&ctx);
	sha512_compute(&ctx,text1,strlen(text1));
	sha512_convert(&ctx,hash);
   	print_hash(hash);

   	// Hash two
	sha512_init(&ctx);
	sha512_compute(&ctx,text2,strlen(text2));
	sha512_convert(&ctx,hash);   	
   	print_hash(hash);

   	return 0;
}
