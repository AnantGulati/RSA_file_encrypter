#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "RSA_trial2.h"

int e, d, n;

int KeyGeneration()
{
    int p, q;
    int phi_n;
 
    do {
        do
            p = rand();
        while (p % 2 == 0);
 
    } while (!PrimarityTest(2, p));
 
    do {
        do
            q = rand();
        while (q % 2 == 0);
    } while (!PrimarityTest(2, q));
 
    n = p * q;
    phi_n = (p - 1) * (q - 1);
 
    do
        e = rand() % (phi_n - 2) + 2; // 1 < e < phi_n
    while (gcd(e, phi_n) != 1);
 
    d = inverse(phi_n, e);
}
 
int Encryption(int value, FILE* out)
{
    int cipher;
    cipher = FindT(value, e, n);
    fprintf(out, "%d ", cipher);
}
 
int Decryption(int value, FILE* out)
{
    int decipher;
    decipher = FindT(value, d, n);
    fprintf(out, "%c", decipher);
}
 
int main(void)
{
    FILE *inp, *out;
 
    // destroy contents of these files (from previous runs, if any)
    out = fopen("cipher.txt", "w+");
    fclose(out);
    out = fopen("decipher.txt", "w+");
    fclose(out);
 
    KeyGeneration();
 
    inp = fopen("input.txt", "r+");
    if (inp == NULL)
    {
        printf("Error opening Source File.\n");
        exit(1);
    }
 
    out = fopen("cipher.txt", "w+");
    if (out == NULL)
    {
        printf("Error opening Destination File.\n");
        exit(1);
    }
 
    // encryption starts
    while (1)
    {
        char ch = getc(inp);
        if (ch == -1) {
            break;
        }
        int value = toascii(ch);
        Encryption(value, out);
    }
 
    fclose(inp);
    fclose(out);
 
    // decryption starts
    inp = fopen("cipher.txt", "r");
    if (inp == NULL)
    {
        printf("Error opening Cipher Text.\n");
        exit(1);
    }
 
    out = fopen("decipher.txt", "w+");
    if (out == NULL)
    {
        printf("Error opening File.\n");
        exit(1);
    }
 
    while (1)
    {
        int cip;
        if (fscanf(inp, "%d", &cip) == -1) {
            break;
        }
        Decryption(cip, out);
    }
    fclose(out);
 
    return 0;
}