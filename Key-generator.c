#include <stdio.h>
#include <stdlib.h>

unsigned long long gcd(unsigned long long a, unsigned long long b) 
{
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

//Extended Euclidean Algorithm to find modular inverse
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
        if (r > 1) return -1; //No inverse
        if (t < 0) t += phi;
        return t; 
}

int main()
{
    //assigning two prime numbers
    unsigned long long p = 61;
    unsigned long long d = 53;

    //calculating the keys
    unsigned long long n = p * d;

    //eulers totient function
    unsigned long long phi = (p -1) * (d - 1);

    //assigning e
    unsigned long long e = 17;


    //error handling
    if(gcd(e, phi) != 1)
    {
        printf("e and phi are no coprime. \n");
        return 1;
    }

    unsigned long long q = mod_inverse(e, phi);

    if(q == -1)
    {
        printf("Failed to compute modulare invers. \n");
        return 1;
    }

    //print the public and private keys
    printf("Public Key:  (n = %llu, e = %llu)\n", n, e);
    printf("Private Key: (n = %llu, d = %llu)\n", n, d);

    return 0;
}


void string_to_ascii(const char *input, int *ascii_array, int *length)
{
    int i;
    for (i = 0; input[i] != '\0'; i++) {
        ascii_array[i] = (int)input[i];
    }
    *length = i;
}

int u_input()
{
    char word[100];
    int ascii_values[100];
    int length, i;

    printf("Enter a word: \n");
    scanf("%s", word);

   string_to_ascii(word, ascii_values, &length);

   printf("ASCII values:\n");
   for (i = 0; i < length; i++) {
       printf("%d ", ascii_values[i]);
   }
   printf("\n");

   return 0;
}