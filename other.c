#include "other.h"

FILE *openFile(char *filename)
{
   FILE *tempFile;
   char bufFile[20];

   tempFile = fopen(filename, "r");

   if (tempFile == NULL)
   {
      while (tempFile == NULL)
      {
         printf("File can't be open. Please try again!\n");
         printf("Enter file's name: ");
         scanf("%s", bufFile);
             tempFile = fopen(bufFile, "r");
      }
   }
   return tempFile;
}

void parseFunc(char *line, POS *toLoad)
{
   char *token ;
   int length = 0;


/*   length = strlen(line);

   while (line[i] != '\0')
   {
       if (count == 1)
       {
          while(line[i] != ',')
          {
             i++;
          }
          count = 2;
          strncpy(toLoad->prodID, line, i-1);
       }
       if (count = 2)
       {
          while(line[i+1] != ',')
          {
             i++;
          }
          count = 3;
          strncpy(toLoad->prodName, line, )
       }



   }*/

   /*token = strtok(line, ",");
   length = strlen(token);
   printf("prodid :%s\n", token);
   strncpy(toLoad->prodID, token, length);

   token = strtok(NULL, ",");
   length = strlen(token);
   strncpy(toLoad->prodName, token, length);

   token = strtok(NULL, ",");
   length = strlen(token);
   strncpy(toLoad->publisher, token, length);

   token = strtok(NULL, ",");
   length = strlen(token);
   strncpy(toLoad->genre, token, length);

   token = strtok(NULL, ",");
   toLoad->taxable = atoi(token);

   token = strtok(NULL, ",");
   toLoad->price = atof(token);

   token = strtok(NULL, ",");
   toLoad->quantity = atoi(token);*/

   token = strsep(&line, ",");
   length = strlen(token);
   strncpy(toLoad->prodID, token, length);

   token = strsep(&line, ",");
   length = strlen(token);
   strncpy(toLoad->prodName, token, length);

   token = strsep(&line, ",");
   length = strlen(token);
   strncpy(toLoad->publisher, token, length);

   token = strsep(&line, ",");
   length = strlen(token);
   strncpy(toLoad->genre, token, length);

   token = strsep(&line, ",");
   toLoad->taxable = atoi(token);

   token = strsep(&line, ",");
  // length = strlen(token);
//   strncpy(tempToken, &token[1], length);
//   printf("  tempToken is %s", tempToken);
   token += 1;
   toLoad->price = atof(token);;

   token = strsep(&line, ",");
   toLoad->quantity = atoi(token);

}

void removeTrailing(char *line)
{
   if (line[strlen(line) -1] == '\n')
   {
      line[strlen(line) - 1] = '\0';
   }
}

void printInventory(POS *data, int count)
{
   int i = 0;

   printf("****** Welcome to the Inventory *******\n\n");
   for(i= 0; i < count-1; i++)
   {
      printf("%d. Product Name: %s, Quantity: %d\n", i+1, data[i].prodName, data[i].quantity);
   }
}

void printInvoice(POS *data, int count)
{
   int sum1 = 0;
   int sum2 = 0;
   int i = 0;

   printf("\n****** Invoice ******\n\n");
   printf("List of all taxable items:\n");
   for(i = 0; i < count; i++)
   {
      if(data[i].taxable == 1)
      {
         printf("%d. Product Name: %s, Product ID: %s, Publisher: %s,",sum1+1, data[i].prodName, data[i].prodID, data[i].publisher);
         printf(" Genre: %s, Price: %.2lf, Quantity Ordered: %d\n", data[i].genre, data[i].price, data[i].quantity);
         printf("\n");
         sum1++;
      }
   }
   if (sum1 == 0)
   {
      printf("No taxable items present\n");
   }

   printf("\nList of all non-taxable items:\n");
   for(i = 0; i < count; i++)
   {
      if(data[i].taxable == 0)
      {
         printf("%d. Product Name: %s, Product ID: %s, Publisher: %s,",sum2+1, data[i].prodName, data[i].prodID, data[i].publisher);
         printf(" Genre: %s, Price: %.2lf, Quantity Ordered: %d\n", data[i].genre, data[i].price, data[i].quantity);
         printf("\n");
         sum2++;
      }
   }
   if (sum2 == 0)
   {
      printf("No non-taxable items present\n");
   }
}
