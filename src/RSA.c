#include<stdio.h>

long int gcd(long int a, long int b)
{
    int temp;
    while (1)
    {
        temp = a%b;
        if (temp == 0)
          return b;
        a = b;
        b = temp;
    }
}

void CreateKeyPair(long int p,long int q)
{
    //p and q are large prime numbers
    long long int n=p*q;
    long int e=2; //totient
    long long int publicKey = (p-1)*(q-1);

    // e must be co-prime to and less than publicKey
    while (e < publicKey)
    {
        if (gcd(e, publicKey)==1)
            break;
        else
            e++;
    }


    const int k = 2; 
    long long int pvtKey = (1 + (k*publicKey))/e;
}

int encrypt(int seed,long long int n,long int e)
{
    //e and n are created in the createKeyPair function and must be passed to the encrypt function

    //Encrypted text = (orignal value ^ e) % n

    int encryptedText=pow(seed,e);
    encryptedText=encryptedText%n;

    return(encryptedText);
}

int decrypt(int seed, int encryptedText, long long int pvtKey, long long int n )
{
    int decryptedText=pow(encryptedText,pvtKey);
    decryptedText=decryptedText%n;
    return(decryptedText);
}