#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "sha256.h"

void print_hash(unsigned char hash[])
{
   int idx;
   for (idx=0; idx < 32; idx++)
      printf("%02x",hash[idx]);
   printf("\n");
}

int main()
{
	unsigned char text1[]={"01234567879"},
                  text2[]={"0123456787901234567879012345678790123456787901234567879"},
                  hash[32];
                 
	SHA256_CTX ctx;                 

   	// Hash one
	sha256_init(&ctx);
	sha256_compute(&ctx,text1,strlen(text1));
	sha256_convert(&ctx,hash);
   	print_hash(hash);

   	// Hash two
	sha256_init(&ctx);
	sha256_compute(&ctx,text2,strlen(text2));
	sha256_convert(&ctx,hash);   	
   	print_hash(hash);

   	return 0;
}
