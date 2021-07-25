#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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