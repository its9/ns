#include <stdio.h>

// Function to calculate (base^exp) % modulus
long long int power(long long int base, long long int exp, long long int modulus) {
    long long int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exp /= 2;
    }
    return result;
}

// Function to perform RSA encryption
long long int encrypt(long long int plaintext, long long int e, long long int n) {
    return power(plaintext, e, n);
}

// Function to perform RSA decryption
long long int decrypt(long long int ciphertext, long long int d, long long int n) {
    return power(ciphertext, d, n);
}

int main() {
    // Public and private keys
    long long int p = 61;
    long long int q = 53;
    long long int n = p * q;
    long long int phi = (p - 1) * (q - 1);
    long long int e = 17; // Public exponent
    long long int d = 413; // Private exponent

    // Message to be encrypted
    long long int plaintext = 123;

    // Encryption
    long long int ciphertext = encrypt(plaintext, e, n);
    printf("Encrypted message: %lld\n", ciphertext);

    // Decryption
    long long int decryptedtext = decrypt(ciphertext, d, n);
    printf("Decrypted message: %lld\n", decryptedtext);

    return 0;
}
