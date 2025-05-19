#include <stdio.h>
#include <stdlib.h>

// --- Function Prototypes ---
unsigned long long gcd(unsigned long long a, unsigned long long b);
long long mod_inverse(long long e, long long phi);
void string_to_ascii(const char *input, int *ascii_array, int *length);
void u_input(unsigned long long n, unsigned long long e);
void decrypt_message(unsigned long long n, unsigned long long d);
unsigned long long mod_pow(unsigned long long base, unsigned long long exp, unsigned long long mod);

// --- GCD Function ---
unsigned long long gcd(unsigned long long a, unsigned long long b) 
{
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// --- Modular Inverse ---
long long mod_inverse(long long e, long long phi)
{
    long long t = 0, newt = 1;
    long long r = phi, newr = e;

    while (newr != 0) {
        long long quotient = r / newr;
        long long temp = newt;
        newt = t - quotient * newt;
        t = temp;

        temp = newr;
        newr = r - quotient * newr;
        r = temp;
    }

    if (r > 1) return -1;
    if (t < 0) t += phi;
    return t; 
}

// --- Modular Exponentiation ---
unsigned long long mod_pow(unsigned long long base, unsigned long long exp, unsigned long long mod)
{
    unsigned long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }

    return result;
}

// --- Convert string to ASCII array ---
void string_to_ascii(const char *input, int *ascii_array, int *length)
{
    int i;
    for (i = 0; input[i] != '\0'; i++) {
        ascii_array[i] = (int)input[i];
    }
    *length = i;
}

// --- User input and encryption ---
void u_input(unsigned long long n, unsigned long long e)
{
    char word[100];
    int ascii_values[100];
    int length, i;

    printf("Enter a word: \n");
    scanf("%s", word);

    // --- Save unencrypted word to file ---
    FILE *f_plain = fopen("unencrypted.txt", "w");
    if (f_plain == NULL) {
        printf("Error opening unencrypted.txt for writing.\n");
        return;
    }
    fprintf(f_plain, "%s\n", word);
    fclose(f_plain);

    string_to_ascii(word, ascii_values, &length);

    printf("Original ASCII values:\n");
    for (i = 0; i < length; i++) {
        printf("%d ", ascii_values[i]);
    }
    printf("\n");

    // --- Open file to store encrypted output ---
    FILE *f_enc = fopen("encrypted.txt", "w");
    if (f_enc == NULL) {
        printf("Error opening encrypted.txt for writing.\n");
        return;
    }

    printf("Encrypted values:\n");
    for (i = 0; i < length; i++) {
        unsigned long long encrypted = mod_pow(ascii_values[i], e, n);
        printf("%llu ", encrypted);               // --- Print to console ---
        fprintf(f_enc, "%llu ", encrypted);       // --- Write to file ---
    }
    printf("\n");

    fclose(f_enc);
}

// --- Decryption function ---
void decrypt_message(unsigned long long n, unsigned long long d)
{
    FILE *f_enc = fopen("encrypted.txt", "r");
    if (f_enc == NULL) {
        printf("Error opening encrypted.txt for reading.\n");
        return;
    }

    FILE *f_dec = fopen("decrypted.txt", "w");
    if (f_dec == NULL) {
        printf("Error opening decrypted.txt for writing.\n");
        fclose(f_enc);
        return;
    }

    printf("Decrypted word:\n");

    unsigned long long encrypted;
    while (fscanf(f_enc, "%llu", &encrypted) == 1) {
        unsigned long long decrypted = mod_pow(encrypted, d, n);
        char character = (char)decrypted;
        printf("%c", character);         // --- Print to console ---
        fprintf(f_dec, "%c", character); // --- Write to file ---
    }

    printf("\n");

    fclose(f_enc);
    fclose(f_dec);
}

// --- Main ---
int main()
{
    // Assign two prime numbers
    unsigned long long p = 61;
    unsigned long long q = 53;

    // Calculate the RSA modulus
    unsigned long long n = p * q;

    // Euler's totient
    unsigned long long phi = (p - 1) * (q - 1);

    // Public exponent
    unsigned long long e = 17;

    // Check coprimality
    if (gcd(e, phi) != 1) {
        printf("e and phi are not coprime.\n");
        return 1;
    }

    // Private exponent
    long long d = mod_inverse(e, phi);
    if (d == -1) {
        printf("Failed to compute modular inverse.\n");
        return 1;
    }

    // Display keys
    printf("Public Key:  (n = %llu, e = %llu)\n", n, e);
    printf("Private Key: (n = %llu, d = %llu)\n", n, d);

    // Perform input and encryption
    u_input(n, e);

    // Perform decryption
    decrypt_message(n, d);

    return 0;
}
