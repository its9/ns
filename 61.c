#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

#define MAX_LEN 1024

int main() {
    RSA *rsa_A = NULL, *rsa_B = NULL;
    unsigned char *plaintext = (unsigned char *)"Hello, User B!";
    unsigned char ciphertext[MAX_LEN] = {0};
    unsigned char decryptedtext[MAX_LEN] = {0};

    // Key Generation for User A
    rsa_A = RSA_generate_key(2048, RSA_F4, NULL, NULL);
    if (rsa_A == NULL) {
        fprintf(stderr, "Error generating RSA key for User A\n");
        return 1;
    }

    // Key Generation for User B
    rsa_B = RSA_generate_key(2048, RSA_F4, NULL, NULL);
    if (rsa_B == NULL) {
        fprintf(stderr, "Error generating RSA key for User B\n");
        RSA_free(rsa_A);
        return 1;
    }

    // Encryption by User A (using User B's public key)
    int encrypted_len = RSA_public_encrypt(strlen((char *)plaintext), plaintext, ciphertext, rsa_B, RSA_PKCS1_PADDING);
    if (encrypted_len == -1) {
        fprintf(stderr, "Error encrypting message\n");
        RSA_free(rsa_A);
        RSA_free(rsa_B);
        return 1;
    }

    // Decryption by User B (using User B's private key)
    int decrypted_len = RSA_private_decrypt(encrypted_len, ciphertext, decryptedtext, rsa_B, RSA_PKCS1_PADDING);
    if (decrypted_len == -1) {
        fprintf(stderr, "Error decrypting message\n");
        RSA_free(rsa_A);
        RSA_free(rsa_B);
        return 1;
    }

    printf("Encrypted message by User A: ");
    for (int i = 0; i < encrypted_len; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    printf("Decrypted message by User B: %s\n", decryptedtext);

    RSA_free(rsa_A);
    RSA_free(rsa_B);

    return 0;
}

