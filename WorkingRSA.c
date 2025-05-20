#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---Function Prototypes---
unsigned long long gcd(unsigned long long a, unsigned long long b);
long long mod_inverse(long long e, long long phi);
void string_to_ascii(const char *input, int *ascii_array, int *length);
void u_input(unsigned long long n, unsigned long long e);
unsigned long long mod_pow(unsigned long long base, unsigned long long exp, unsigned long long mod);
void generate_keys(unsigned long long p, unsigned long long q, unsigned long long *n, unsigned long long *e, unsigned long long *d);

// ---GCD Function---
unsigned long long gcd(unsigned long long a, unsigned long long b) 
{
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// ---Modular Inverse---
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

// ---Modular Exponentiation---
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

// ---Convert string to ASCII array---
void string_to_ascii(const char *input, int *ascii_array, int *length)
{
    int i;
    for (i = 0; input[i] != '\0'; i++) {
        ascii_array[i] = (int)input[i];
    }
    *length = i;
}

// ---RSA Key Generation---
void generate_keys(unsigned long long p, unsigned long long q, unsigned long long *n, unsigned long long *e, unsigned long long *d)
{
    *n = p * q;
    unsigned long long phi = (p - 1) * (q - 1);
    *e = 17;

    if (gcd(*e, phi) != 1) {
        printf("e and phi are not coprime.\n");
        exit(1);
    }

    *d = mod_inverse(*e, phi);
    if (*d == -1) {
        printf("Failed to compute modular inverse.\n");
        exit(1);
    }
}

// ---User input and encryption---
void u_input(unsigned long long n, unsigned long long e)
{
    char word[100];
    int ascii_values[100];
    int length, i;

    printf("Enter a word: \n");
    scanf("%s", word);

    string_to_ascii(word, ascii_values, &length);

    printf("Original ASCII values:\n");
    for (i = 0; i < length; i++) {
        printf("%d ", ascii_values[i]);
    }
    printf("\n");

    printf("Encrypted values:\n");
    for (i = 0; i < length; i++) {
        unsigned long long encrypted = mod_pow(ascii_values[i], e, n);
        printf("%llu ", encrypted);
    }
    printf("\n");
}

// ---Main---
int main()
{
    // ---Generate Keys for User A---
    unsigned long long p1 = 61, q1 = 53;
    unsigned long long n1, e1, d1;
    generate_keys(p1, q1, &n1, &e1, &d1);

    printf("User A Public Key:  (n = %llu, e = %llu)\n", n1, e1);
    printf("User A Private Key: (n = %llu, d = %llu)\n\n", n1, d1);

    // ---Generate Keys for User B---
    unsigned long long p2 = 73, q2 = 67;
    unsigned long long n2, e2, d2;
    generate_keys(p2, q2, &n2, &e2, &d2);

    printf("User B Public Key:  (n = %llu, e = %llu)\n", n2, e2);
    printf("User B Private Key: (n = %llu, d = %llu)\n\n", n2, d2);

    // ---Perform input and encryption using User B's public key---
    u_input(n2, e2);

    return 0;
}