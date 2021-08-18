#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int gcd(int a, int b)
{
    int q, r1, r2, r;
 
    if (a > b)
    {
        r1 = a;
        r2 = b;
    }
    else {
        r1 = b;
        r2 = a;
    }
 
    while (r2 > 0)
    {
        q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2;
        r2 = r;
    }
 
    return r1;
}

int FastExponention(int bit, int n, int* y, int* a)
{
    if (bit == 1) {
        *y = (*y * (*a)) % n;
    }
 
    *a = (*a) * (*a) % n;
}


int FindT(int a, int m, int n)
{
    int r;
    int y = 1;
 
    while (m > 0)
    {
        r = m % 2;
        FastExponention(r, n, &y, &a);
        m = m / 2;
    }
    return y;
}
 
 
int PrimarityTest(int a, int i)
{
    int n = i - 1;
    int k = 0;
    int j, m, T;
 
    while (n % 2 == 0)
    {
        k++;
        n = n / 2;
    }
 
    m = n;
    T = FindT(a, m, i);
 
    if (T == 1 || T == i - 1) {
        return 1;
    }
 
    for (j = 0; j < k; j++)
    {
        T = FindT(T, 2, i);
        if (T == 1) {
            return 0;
        }
        if (T == i - 1) {
            return 1;
        }
    }
    return 0;
}
 
int inverse(int a, int b)
{
    int inv;
    int q, r, r1 = a, r2 = b, t, t1 = 0, t2 = 1;
 
    while (r2 > 0)
    {
        q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2;
        r2 = r;
 
        t = t1 - q * t2;
        t1 = t2;
        t2 = t;
    }
 
    if (r1 == 1) {
        inv = t1;
    }
 
    if (inv < 0) {
        inv = inv + a;
    }
 
    return inv;
}
 
int register_user(char* n, char* p, char* ui)
{
    FILE *fp;
    FILE *fp2;
    fp = fopen("accounts.txt", "a");
    if(fp == NULL)
   {
      printf("Error!");   
      exit(1);             
   }

   printf("Enter username: ");
   scanf("%s",n);
   printf("Enter password: ");
   scanf("%s",p);

   fprintf(fp,"USN: %s ; PWD: %s\n",n,p);

   fclose(fp);
   printf("Account successfully created!\n");
   strcpy(ui,n);
   strcat(ui,".txt");
   fp2 = fopen(ui,"w");
   fclose(fp2);
   return 0;

}


int read_file()
{
    char c[1000];
    FILE *fp;
    fp = fopen("accounts.txt", "r");
    if(fp == NULL)
   {
      printf("Error!");   
      exit(1);             
   }

    fscanf(fp, "%[^\n]", c);
    printf("Data from the file:\n%s", c);
    fclose(fp);
}

int inbox(char* n, char* p, char* ui)
{
   char line[100];
   FILE *fp;
   strcpy(ui,n);
   strcat(ui,".txt");
   fp = fopen(ui, "r");
   if(fp == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
   char ch;
   while((ch = fgetc(fp)) != EOF)
   {
      fputc(ch, stdout);
   }

   fclose(fp);
   printf("End of messages.\n");   

   return 0;
}