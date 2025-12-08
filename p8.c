// #include <stdio.h>
// #include <string.h>
// #include <openssl/aes.h>

// int main() {
//     unsigned char key[16] = "1234567890abcdef";
//     unsigned char iv[AES_BLOCK_SIZE] = "abcdef1234567890";
//     unsigned char text[] = "welcome to ISE";
//     unsigned char enc[128], dec[128];

//     AES_KEY enc_key, dec_key;
//     AES_set_encrypt_key(key, 128, &enc_key);
//     AES_cbc_encrypt(text, enc, sizeof(text), &enc_key, iv, AES_ENCRYPT);

//     printf("Encrypted: ");
//     for(int i=0;i<sizeof(text);i++) printf("%02x", enc[i]);
//     printf("\n");

//     unsigned char iv2[AES_BLOCK_SIZE] = "abcdef1234567890";
//     AES_set_decrypt_key(key, 128, &dec_key);
//     AES_cbc_encrypt(enc, dec, sizeof(text), &dec_key, iv2, AES_DECRYPT);
//     printf("Decrypted: %s\n", dec);
//     return 0;
// }
#include <stdio.h>
#include <string.h> 
#include <openssl/aes.h>

int main() {
    AES_KEY enc_key, dec_key;
    unsigned char key[] = "1234567890ABCDEF";  // 16 bytes = 128-bit key 
    unsigned char input[] = "welcome to ISE";   // plaintext
    unsigned char enc_out[128], dec_out[128];

    AES_set_encrypt_key(key, 128, &enc_key);
    AES_encrypt(input, enc_out, &enc_key);

    printf("Original text: %s\n", input);
    printf("Encrypted text (hex): ");
    for (int i = 0; i < 16; i++)
      
        printf("%02x ", enc_out[i]);
    printf("\n");

    AES_set_decrypt_key(key, 128, &dec_key);
    AES_decrypt(enc_out, dec_out, &dec_key);

    printf("Decrypted text: %s\n", dec_out);
    printf("\n");
    return 0;
    //gcc p8.c -o p8 -lcrypto

}
