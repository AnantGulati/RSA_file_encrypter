#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "rsal-final-2.h"

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

int main()
{
    char line[100], junk[100];
    int count = 0; //to compare usn
    int c2 = 0; //to compare pwd
    int ch = -1; //to enter user's choice
    int s = 0; // login success: s -> 1
    char name[100], pwd[100], user_inbox[100];

    FILE *inp, *out, *cipher;

    printf("Press 1 to create a new account.\nPress 2 to login to an existing account.\n");
    scanf("%d",&ch);
    if (ch==1)
    {
        register_user(name, pwd, user_inbox);
    }
    else if(ch == 2)
    {
        while(s==0)
        {
            fflush(stdin);
            printf("Enter your name: ");
            scanf("%s",name);
            fflush(stdin);
            printf("Enter your password: ");
            printf("pass : %s\n",pwd);
            FILE *file = fopen("accounts.txt", "r");
            if(!file) 
            {
                printf("Could not open file. Exiting application. Bye");
                return 1;
            }

            while(!feof(file))
            {
                fscanf(file,"%[^ \n\t\r]s",line); //Get text
                if (!strcmp(line,name))
                {
                    count += 1;
                }
                if (count == 1)
                    c2 += 1;
                if((count == 1) && (c2 == 4))
                {
                    if (!strcmp(line,pwd))
                    {
                        printf("Valid Username and Password\n");
                        s = 1;
                    }
                    else
                    {
                        printf("Invalid Password\n");
                        printf("Try again\n");
                    }        
                }
                fscanf(file,"%[ \n\t\r]s",junk); //Remove any 'white space' characters
                    
            }
            fclose(file);
            if (count != 1)
            {
                printf("Invalid Username and Password\n");
                printf("Try again\n");
            }
        }
    }
    else
        printf("Invalid Input\n");
        
    ch = -1;
    while(ch!=3)
    {
        fflush(stdin);
        printf("--------------------------------------------------------------------------------\n");
        printf("Press 1 to send a cipher message.\nPress 2 to view your inbox.\nPress 3 to exit.\n");
        scanf("%d",&ch);
        if(ch == 1)
        {
            char tofile[100];  //To file name
            char tousn[100];  //To username
            printf("Enter reciever's username:\n");
            scanf("%s",&tofile);
            strcpy(tousn,tofile);

            cipher = fopen("cipher.txt", "w+");
            fclose(cipher);

            KeyGeneration();

            inp = fopen("input.txt", "w+");
            fclose(inp); //destroy previous content

            inp = fopen("input.txt", "w");  //to write input msg
            strcat(tofile,".txt");

            out = fopen(tofile, "w+");  //username.txt  
            if (out == NULL)
            {
                printf("Error opening Destination File.\n");
                exit(1);
            }

            //Writing to input file
            char msg[500];
            
            fprintf(out,"%s","From: ");
            fprintf(out,"%s",name);
            fprintf(out,"%c",'\n');
            fclose(out);

            fflush(stdin);
            printf("Enter message: ");
            scanf("%[^\n]%*c",&msg);
            fprintf(inp,"%s",msg);
            fprintf(inp,"%c",'\n');
            fclose(inp);

            inp = fopen("input.txt", "r+");  //opening in read mode
            if (inp == NULL)
            {
                printf("Error opening Source File.\n");
                exit(1);
            }

            out = fopen(tofile, "a");
            if (out == NULL)
            {
                printf("Error opening Destination File.\n");
                exit(1);
            }

            cipher = fopen("cipher.txt", "w+");
            if (out == NULL)
            {
                printf("Error opening Cipher File.\n");
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
                Encryption(value, cipher);
            }
        
            fclose(inp);
            fclose(out);
            fclose(cipher);

            // decryption starts
            inp = fopen("cipher.txt", "r");
            if (inp == NULL)
            {
                printf("Error opening Cipher Text.\n");
                exit(1);
            }
        
            out = fopen(tofile, "a");  
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
        }
        else if(ch == 2)
        {
            inbox(name,pwd,user_inbox);
        }
    }
}
