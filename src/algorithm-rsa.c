#include<stdio.h>
#include<math.h>
#include<stdlib.h>

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

void encrypt(int seed,long long int n,long int e,char fileName[]) //pass the name of the file to the function
{
    //e and n are created in the createKeyPair function and must be passed to the encrypt function

    //Encrypted text = (orignal value ^ e) % n

    FILE *fp1=fopen(fileName,"r+w");
    FILE *fp2=fopen("tempfile1.txt","a");

    char c;

    while ((c = fgetc(fp1)) != EOF)
    {
        int encryptedText=(int)pow(c,e);
        encryptedText=encryptedText%n;
        fputc(encryptedText,fp2);
    }

    int delFlag=remove(fileName);
    int i=rename("tempfile1.txt",fileName);

    fclose(fp1);
    fclose(fp2);
}

void decrypt(long long int pvtKey, long long int n, char fileName[])
{
    FILE *fp1=fopen(fileName,"r+w");
    FILE *fp2=fopen("tempfile2.txt","a");
    char c;

    while ((c = fgetc(fp1)) != EOF)
    {
        double trial = pow(c,pvtKey);
        int decryptedText=pow(c,pvtKey);
        decryptedText=decryptedText%n;
        fputc(decryptedText,fp2);
    }

    int delFlag=remove(fileName);
    int i=rename("tempfile2.txt",fileName);


    fclose(fp1);
    fclose(fp2);
}

void CreateKeyPair(long int p,long int q, char fileName[])
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

    encrypt(0,n,e,fileName);

    const int k = 2; 
    long long int pvtKey = (1 + (k*publicKey))/e;

    decrypt(pvtKey,n,fileName);
}

int main()
{
    long int p = 7433;
    long int q = 6997;
    char fileName[100] = "inputfile.txt";
    CreateKeyPair(7433, 6997, fileName);
}