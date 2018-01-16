#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct info
{
   char prodID[25];
   char prodName[100];
   char publisher[100];
   char genre[100];
   int taxable;
   double price;
   int quantity;
}POS;

/**Function to open the file and read it
*@return a file pointer if the file to be read is present
*@param filename pointer to the name of the file to be opened and read
**/
FILE *openFile(char *filename);

/**Function to parse through each line read
*@param line which contains the data
*@param toLoad pointer to a struct in which the data is loaded.
**/
void parseFunc(char *line, POS *toLoad);

/**Function to remove the null terminated
*@param string that may contains  the null terminated
**/
void removeTrailing(char *line);

/**Function to print the data in the struct which is for the invoice
*@param data is an array of struct which contains all game Details present in the invoice
*@param count indicates the number of games in the invoice
**/
void printInvoice(POS *data, int count);

/**Function to print the data in the struct which is for the inventory
*@param data is an array of struct which contains all game Details in the inventory
*@param count indicates the number of games in the inventory
**/
void printInventory(POS *data, int count);
