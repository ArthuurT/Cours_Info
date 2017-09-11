#include <stdio.h>
#include <string.h>
#include "RC4.h"

void print_hexa(BYTE c[], int len) {
    for (int i=0; i < len; i++)
        printf("%02X", c[i]);
    printf("\n");
}

int main() {

    //Initialisation
    BYTE key1[] = {"Key"};
    BYTE key2[] = {"Wiki"};
    BYTE key3[] = {"Secret"};

    BYTE text1[] = {"Plaintext"};
    BYTE text2[] = {"pedia"};
    BYTE text3[] = {"Attack at dawn"};

    BYTE chiffre[200];
    BYTE message[200];

    RC4_CTX ctx;


    // Test1
    rc4_init(&ctx, key1, strlen((const char*)key1));
    rc4_crypt(&ctx, text1, strlen((const char*)text1), chiffre, 200);
    print_hexa(chiffre, strlen((const char*)text1));

    // Test2
    rc4_init(&ctx, key2, strlen((const char*)key2));
    rc4_crypt(&ctx, text2, strlen((const char*)text2), chiffre, 200);
    print_hexa(chiffre, strlen((const char*)text2));

    // Test3
    rc4_init(&ctx, key3, strlen((const char*)key3));
    rc4_crypt(&ctx, text3, strlen((const char*)text3), chiffre, 200);
    print_hexa(chiffre, strlen((const char*)text3));

    //TestDecryptage1
    rc4_init(&ctx, key1, strlen((const char*)key1));
    rc4_crypt(&ctx, text1, strlen((const char*)text1), chiffre, 200);
    rc4_decrypt(&ctx, key1, strlen((const char*)key1), chiffre, 200);
    printf("\n");

    return 0;
}
