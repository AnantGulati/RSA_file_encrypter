#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "header.h"

int main(int argc, char const *argv[]) 
{ 
    char line[100], junk[100];
    int count = 0; //to compare usn
    int c2 = 0; //to compare pwd
    int ch = -1; //to enter user's choice
    int s = 0; // login success: s -> 1
    char name[100], pwd[100], user_inbox[100];

    printf("Press 1 to create a new account.\nPress 2 to login to an existing account.\n");
    scanf("%d",&ch);
    if (ch==1)
    {
        register_user(name, pwd, user_inbox);
    }
    else if(ch == 2)
    {
        printf("Enter your name: ");
        scanf("%s",&name);
        printf("Enter your password: ");
        scanf("%s",&pwd);
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
            //printf("count = %d line = %s\n",count,line);
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
                    printf("Invalid Password\n");
            }
            fscanf(file,"%[ \n\t\r]s",junk); //Remove any 'white space' characters
            
        }
        fclose(file);
        if (count != 1)
            printf("Invalid Username and Password\n");
        
    }
    else
        printf("Invalid Input\n");

    if (s==1) //login successful
    {
        inbox(name,pwd,user_inbox);
    }
    return 0; 
} 