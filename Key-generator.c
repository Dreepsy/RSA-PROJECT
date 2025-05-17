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