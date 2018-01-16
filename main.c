#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "other.h"
#include "balancedTreeAPI.h"

#define LEN 500
#define size 10


int main(int argc, char* argv[])
{
   FILE *infile = NULL;
   POS items[200];
   POS invoice[100];
   POS inventory[200];
   POS tempData;
   char gameData[LEN];
   char addInv[size];
   char afterAdd[size];
   char buyItem[size];
   char next[size];
   char itemQty1[size];
   char removeItem[size];
   char editInv[size];
   char symbol[size];
   int itemQty = 0;
   int total = 0;
   int count = 0;
   int i = 0;
   int allRemove = 0;
   char searchItem[50];
   char action[3];
   bool state = true;
   bool match = true;

   Tree *theTree = NULL;
   void *findMatch;

   infile = openFile(argv[1]);

   while (fgets(gameData, LEN, infile))
   {
      //removeTrailing(gameData);
      if (count != 0)
      {
         parseFunc(gameData, &items[count-1]);
         count = count + 1;
      }
      else
      {
         count = count + 1;
      }
   }

   fclose(infile);

   printf("\n\n");

  /* for (i= 0; i < count-1; i++)
   {
      printf("%d: Quantity is %lf, product name is : %s\n",(i+1), items[i].price, items[i].prodName);
   }*/

   //I have everything in the struct
   //Add it to the binary search treee

   theTree = createBalancedBinTree(&compareFP, &destroyFP, &copyFP);

   for (i= 0; i < count-1; i++)
   {
      treeInsertNode(theTree, (void*)&items[i], 1);
   }


   while (strcmp(action, "Q") != 0)
   {
      printf("******** Welcome to the POS System ********\n\n");
      printf("Do you want to search for a product?\n");
      printf("Type Y to search\nType Q to quit the POS System\n");
      printf("\nAction: ");
      fgets(action, 3, stdin);
      removeTrailing(action);
      printf("\n");

      if (strcmp(action, "Y") == 0)
      {
         printf("---- Search Engine ----\n\n");
         printf("Enter the product name: ");
         fgets(searchItem, 50, stdin);
         removeTrailing(searchItem);
         int len = strlen(searchItem);
        // printf("len %d\n", len);
         strncpy(tempData.prodName, searchItem, len);

         state = true;
         while (state == true)
         {
            findMatch = treeFindNode(theTree, (void*)&tempData, 1);
          //  printf("check3: %s\n", ((struct info*)findMatch)->prodName);
            if (findMatch == NULL)
            {
               printf("Invalid product name.\nPlease enter exact product name or type Q to exit: ");
               fgets(searchItem, 50, stdin);
               removeTrailing(searchItem);
               int len = strlen(searchItem);
               strncpy(tempData.prodName, searchItem, len);
               state = true;
               if (strcmp(searchItem, "Q") == 0)
               {
                 for (i = 0; i < count-1; i++)
                 {
                    inventory[i] = *(struct info*)treeFindNode(theTree, (void*)&items[i], 1);
                 }
                 printInventory(inventory, count);
                 printf("\n");
                 printInvoice(invoice, total);
                  exit(1);
               }

            }
            else
            {
               state = false;
            }
         }

         printf("\nNotification: Product name is found\n");
         printf("\nDetails of the product: \n\n");
         printf("Product ID: %s\nProduct Name: %s\n", ((struct info*)findMatch)->prodID, ((struct info*)findMatch)->prodName);
         printf("Publisher: %s\nGenre: %s\nPrice: $%.2lf\nQuantity: %d\n", ((struct info*)findMatch)->publisher, ((struct info*)findMatch)->genre, ((struct info*)findMatch)->price, ((struct info*)findMatch)->quantity);



         printf("\n\n---- Add to Invoice / Remove this Item ----\n\n");
         printf("\nDo you wish to add this item to your invoice?\n");
         printf("Type Y to add to invoice\n");
         printf("Type R to remove this product\n");
         printf("Type E to edit the invoice\n");
         printf("Type N if you don't wish to do anything to the invoice\n");
         printf("\nAction: ");
         fgets(addInv, size, stdin);
         removeTrailing(addInv);

         //Not wishing to remove or add
         if (strcmp(addInv, "N") == 0)
         {
            printf("\nDo you want to search for another product?\n");
            printf("Type X to exit the POS or any other key to go back to the main menu\n");
            printf("Action: ");
            fgets(afterAdd, size, stdin);
            removeTrailing(afterAdd);
            printf("\n");
            if (strcmp(afterAdd, "X") == 0)
            {
              for (i = 0; i < count-1; i++)
              {
                 inventory[i] = *(struct info*)treeFindNode(theTree, (void*)&items[i], 1);
              }
              printInventory(inventory, count);
              printf("\n");
              printInvoice(invoice, total);
              exit(1);
            }
         }
         /*ADDING TO THE INVOICE*/
         else if (strcmp(addInv, "Y") == 0)
         {
            match = true;
            while (match == true)
            {
               printf("\nEnter product ID to add to invoice: ");
               fgets(buyItem, 20, stdin);
               removeTrailing(buyItem);

               if (strcmp(buyItem, ((struct info*)findMatch)->prodID) == 0)
               {
                  match = false;
               }
               else
               {
                  printf("Invalid product ID. Try again!\n");
               }
            }

            printf("\nHow many of this item do you want to buy?\n");
            printf("Quantity: ");
            fgets(itemQty1, size, stdin);
          //  fgets(itemQty1, size, stdin);
            removeTrailing(itemQty1);
            itemQty = atoi(itemQty1);

           if (itemQty <= ((struct info*)findMatch)->quantity)
           {
               int d = strlen(((struct info*)findMatch)->prodID);
               strncpy(invoice[total].prodID, ((struct info*)findMatch)->prodID, d);

               d = strlen(((struct info*)findMatch)->prodName);
               strncpy(invoice[total].prodName, ((struct info*)findMatch)->prodName, d);

               d = strlen(((struct info*)findMatch)->publisher);
               strncpy(invoice[total].publisher, ((struct info*)findMatch)->publisher, d);

               d = strlen(((struct info*)findMatch)->genre);
               strncpy(invoice[total].genre, ((struct info*)findMatch)->genre, d);

               invoice[total].taxable = ((struct info*)findMatch)->taxable;

               invoice[total].price = ((struct info*)findMatch)->price;

               invoice[total].quantity = itemQty;

               total = total + 1;

               if (((struct info*)findMatch)->quantity > 1)
               {
               // just reduces the quantity in the inventory
                reduceQty(theTree, findMatch, 1, itemQty);
               }
               else //remove the item from the inventory
               {
                  treeDeleteNode(theTree, findMatch, 1);
                  count = count -1;
               }

               printf("\nNotification: Product added to Invoice\n");

               printf("\nDo you want to go back to the main menu and search for another product?\n");
               printf("Type B to go back\nType E to edit the invoice\nType any letter to exit the program\n");
               printf("\nAction: ");
               fgets(next, size, stdin);
               removeTrailing(next);
               printf("\n");

               if (strcmp(next, "B") != 0 && strcmp(next, "E") != 0)
               {
                  for (i = 0; i < count-1; i++)
                  {
                     inventory[i] = *(struct info*)treeFindNode(theTree, (void*)&items[i], 1);
                  }
                  printInventory(inventory, count);
                  printf("\n");
                  printInvoice(invoice, total);
                  exit(1);
               }
               else if (strcmp(next, "E") == 0)
               {
                  printInvoice(invoice, total);
                  printf("\nDo you want to:\n");
                  printf("Type A - Add a new item\n");
                //  printf("Type R - To remove an item\n");
                  printf("Type C - To change the quantity of an item\n");
                  printf("\nAction: ");
                  fgets(editInv, size, stdin);
                  removeTrailing(editInv);

                  if(strcmp(editInv, "A") == 0)
                  {
                     printf("Enter the product name: ");
                     fgets(searchItem, 50, stdin);
                     removeTrailing(searchItem);
                     int len = strlen(searchItem);
                     strncpy(tempData.prodName, searchItem, len);

                     state = true;
                     while (state == true)
                     {
                        findMatch = treeFindNode(theTree, (void*)&tempData, 1);
                      //  printf("check3: %s\n", ((struct info*)findMatch)->prodName);
                        if (findMatch == NULL)
                        {
                           printf("Invalid product name.\nPlease enter exact product name or type Q to exit: ");
                           fgets(searchItem, 50, stdin);
                           removeTrailing(searchItem);
                           int len = strlen(searchItem);
                           strncpy(tempData.prodName, searchItem, len);
                           state = true;
                           if (strcmp(searchItem, "Q") == 0)
                           {
                             for (i = 0; i < count-1; i++)
                             {
                                inventory[i] = *(struct info*)treeFindNode(theTree, (void*)&items[i], 1);
                             }
                             printInventory(inventory, count);
                             printf("\n");
                             printInvoice(invoice, total);
                              exit(1);
                           }

                        }
                        else
                        {
                           state = false;
                        }
                     }

                     printf("\nNotification: Product name is found\n");
                     printf("\nDetails of the product: \n\n");
                     printf("Product ID: %s\nProduct Name: %s\n", ((struct info*)findMatch)->prodID, ((struct info*)findMatch)->prodName);
                     printf("Publisher: %s\nGenre: %s\nPrice: $%.2lf\nQuantity: %d\n", ((struct info*)findMatch)->publisher, ((struct info*)findMatch)->genre, ((struct info*)findMatch)->price, ((struct info*)findMatch)->quantity);

                     match = true;
                     while (match == true)
                     {
                        printf("\nEnter product ID to add to invoice: ");
                        fgets(buyItem, 20, stdin);
                        removeTrailing(buyItem);

                        if (strcmp(buyItem, ((struct info*)findMatch)->prodID) == 0)
                        {
                           match = false;
                        }
                        else
                        {
                           printf("Invalid product ID. Try again!\n");
                        }
                     }

                     printf("\nHow many of this item do you want to buy?\n");
                     printf("Quantity: ");
                     fgets(itemQty1, size, stdin);
                     removeTrailing(itemQty1);
                     itemQty = atoi(itemQty1);

                    if (itemQty <= ((struct info*)findMatch)->quantity)
                    {
                        int e = strlen(((struct info*)findMatch)->prodID);
                        strncpy(invoice[total].prodID, ((struct info*)findMatch)->prodID, e);

                        e = strlen(((struct info*)findMatch)->prodName);
                        strncpy(invoice[total].prodName, ((struct info*)findMatch)->prodName, e);

                        e = strlen(((struct info*)findMatch)->publisher);
                        strncpy(invoice[total].publisher, ((struct info*)findMatch)->publisher, e);

                        e = strlen(((struct info*)findMatch)->genre);
                        strncpy(invoice[total].genre, ((struct info*)findMatch)->genre, e);

                        invoice[total].taxable = ((struct info*)findMatch)->taxable;

                        invoice[total].price = ((struct info*)findMatch)->price;

                        invoice[total].quantity = itemQty;

                        total = total + 1;

                        if (((struct info*)findMatch)->quantity > 1)
                        {
                        // just reduces the quantity in the inventory
                         reduceQty(theTree, findMatch, 1, itemQty);
                        }
                        else //remove the item from the inventory
                        {
                           treeDeleteNode(theTree, findMatch, 1);
                           count = count -1;
                        }

                        printf("\nNotification: Product added to Invoice and going back to Main menu\n\n");
                     }
                 }
                 else if (strcmp(editInv, "C") == 0)
                 {
                     printf("\nWhich product do you want to change the quantity?\n");
                     printf("Enter product name: ");
                     fgets(searchItem, 50, stdin);
                     removeTrailing(searchItem);
                     strncpy(tempData.prodName, searchItem, len);
                     printf("\n");
                     printf("Do you want to increase or decrease the quantity?\n");
                     printf("Type + to increase\nType - to decrease\n");
                     printf("\nAction: ");
                     fgets(symbol, size, stdin);
                     removeTrailing(symbol);

                     if (strcmp(symbol, "+") == 0)
                     {
                         printf("Enter the quantity to increase with: ");
                         fgets(itemQty1, size, stdin);
                         removeTrailing(itemQty1);
                         itemQty = atoi(itemQty1);

                         for (i= 0; i < total; i++)
                         {
                            if(strcmp(searchItem, invoice[i].prodName) == 0)
                            {
                               invoice[i].quantity = invoice[i].quantity + itemQty;
                            }
                         }

                         findMatch = treeFindNode(theTree, (void*)&tempData, 1);
                         if (findMatch != NULL)
                         {
                            if (((struct info*)findMatch)->quantity > 1)
                            {
                         // just reduces the quantity in the inventory
                               reduceQty(theTree, findMatch, 1, itemQty);
                            }
                            else //remove the item from the inventory
                            {
                               treeDeleteNode(theTree, findMatch, 1);
                               count = count -1;
                            }
                         }
                         else {
                            printf("Not available in inventory\n");
                         }

                     }
                     else if (strcmp(symbol, "-") == 0)
                     {
                        printf("Enter the quantity to increase with: ");
                        fgets(itemQty1, size, stdin);
                        removeTrailing(itemQty1);
                        itemQty = atoi(itemQty1);

                        for (i= 0; i < total; i++)
                        {
                           if(strcmp(searchItem, invoice[i].prodName) == 0)
                           {
                              invoice[i].quantity = invoice[i].quantity - itemQty;
                           }
                        }

                       findMatch = treeFindNode(theTree, (void*)&tempData, 1);

                       if (findMatch == NULL)
                       {
                           tempData.quantity = tempData.quantity + itemQty;
                           treeInsertNode(theTree, (void*)&tempData, 1);
                       }
                       else
                       {
                          ((struct info*)findMatch)->quantity = ((struct info*)findMatch)->quantity +itemQty;
                       }
                     }
                     else
                     {
                        printf("Re-starting..\n");
                     }

                 }
                 else
                 {
                   printf("Wrong action! Existing POS System..\n\n");
                   for (i = 0; i < count-1; i++)
                   {
                      inventory[i] = *(struct info*)treeFindNode(theTree, (void*)&items[i], 1);
                   }
                   printInventory(inventory, count);
                   printf("\n");
                   printInvoice(invoice, total);
                    exit(1);
                 }
            }
            else
            {
               printf("Not enough available! Please try again..\n");
               printf("POS Sytem Re-starting\n\n");
              /* for (i = 0; i < count-1; i++)
               {
                  inventory[i] = *(struct info*)treeFindNode(theTree, (void*)&items[i], 1);
               }
               printInventory(inventory, count);
               printf("\n");
               printInvoice(invoice, total);*/
            }

         }
         else if (strcmp(addInv, "R") == 0)
         {
             printf("Do you want to want to remove all items of this type from the inventory\n");
             printf("Type Y to remove all\n");
             printf("Type any key to return back to main menu\n");
             printf("\nAction: ");
             fgets(removeItem, size, stdin);
             removeTrailing(removeItem);

             if(strcmp(removeItem, "Y") == 0)
             {
                allRemove = ((struct info*)findMatch)->quantity;
                printf("Qty removed: %d\n", allRemove);

                reduceQty(theTree, findMatch, 1, allRemove);
                treeDeleteNode(theTree, findMatch, 1);
                count = count -1;
                printf("Notification: This product has been removed from the inventory\n");
                printf("You will be return back to the main menu");
             }
         }
         else
         {
            printf("Invalid entry.\n--POS System terminated--");
            for (i = 0; i < count-1; i++)
            {
               inventory[i] = *(struct info*)treeFindNode(theTree, (void*)&items[i], 1);
            }
            printInventory(inventory, count);
            printf("\n");
            printInvoice(invoice, total);
         }
      }
      else if (strcmp(addInv, "E") == 0)
      {
        printInvoice(invoice, total);
        printf("\nDo you want to:\n");
        printf("Type A - Add a new item\n");
      //  printf("Type R - To remove an item\n");
        printf("Type C - To change the quantity of an item\n");
        printf("\nAction: ");
        fgets(editInv, size, stdin);
        removeTrailing(editInv);

        if(strcmp(editInv, "A") == 0)
        {
           printf("Enter the product name: ");
           fgets(searchItem, 50, stdin);
           removeTrailing(searchItem);
           int len = strlen(searchItem);
           strncpy(tempData.prodName, searchItem, len);

           state = true;
           while (state == true)
           {
              findMatch = treeFindNode(theTree, (void*)&tempData, 1);
            //  printf("check3: %s\n", ((struct info*)findMatch)->prodName);
              if (findMatch == NULL)
              {
                 printf("Invalid product name.\nPlease enter exact product name or type Q to exit: ");
                 fgets(searchItem, 50, stdin);
                 removeTrailing(searchItem);
                 int len = strlen(searchItem);
                 strncpy(tempData.prodName, searchItem, len);
                 state = true;
                 if (strcmp(searchItem, "Q") == 0)
                 {
                   for (i = 0; i < count-1; i++)
                   {
                      inventory[i] = *(struct info*)treeFindNode(theTree, (void*)&items[i], 1);
                   }
                   printInventory(inventory, count);
                   printf("\n");
                   printInvoice(invoice, total);
                    exit(1);
                 }

              }
              else
              {
                 state = false;
              }
           }

           printf("\nNotification: Product name is found\n");
           printf("\nDetails of the product: \n\n");
           printf("Product ID: %s\nProduct Name: %s\n", ((struct info*)findMatch)->prodID, ((struct info*)findMatch)->prodName);
           printf("Publisher: %s\nGenre: %s\nPrice: $%.2lf\nQuantity: %d\n", ((struct info*)findMatch)->publisher, ((struct info*)findMatch)->genre, ((struct info*)findMatch)->price, ((struct info*)findMatch)->quantity);

           match = true;
           while (match == true)
           {
              printf("\nEnter product ID to add to invoice: ");
              fgets(buyItem, 20, stdin);
              removeTrailing(buyItem);

              if (strcmp(buyItem, ((struct info*)findMatch)->prodID) == 0)
              {
                 match = false;
              }
              else
              {
                 printf("Invalid product ID. Try again!\n");
              }
           }

           printf("\nHow many of this item do you want to buy?\n");
           printf("Quantity: ");
           fgets(itemQty1, size, stdin);
           removeTrailing(itemQty1);
           itemQty = atoi(itemQty1);

          if (itemQty <= ((struct info*)findMatch)->quantity)
          {
              int e = strlen(((struct info*)findMatch)->prodID);
              strncpy(invoice[total].prodID, ((struct info*)findMatch)->prodID, e);

              e = strlen(((struct info*)findMatch)->prodName);
              strncpy(invoice[total].prodName, ((struct info*)findMatch)->prodName, e);

              e = strlen(((struct info*)findMatch)->publisher);
              strncpy(invoice[total].publisher, ((struct info*)findMatch)->publisher, e);

              e = strlen(((struct info*)findMatch)->genre);
              strncpy(invoice[total].genre, ((struct info*)findMatch)->genre, e);

              invoice[total].taxable = ((struct info*)findMatch)->taxable;

              invoice[total].price = ((struct info*)findMatch)->price;

              invoice[total].quantity = itemQty;

              total = total + 1;

              if (((struct info*)findMatch)->quantity > 1)
              {
              // just reduces the quantity in the inventory
               reduceQty(theTree, findMatch, 1, itemQty);
              }
              else //remove the item from the inventory
              {
                 treeDeleteNode(theTree, findMatch, 1);
                 count = count -1;
              }

              printf("\nNotification: Product added to Invoice and going back to Main menu\n\n");
           }
       }
       else if (strcmp(editInv, "C") == 0)
       {
           printf("\nWhich product do you want to change the quantity?\n");
           printf("Enter product name: ");
           fgets(searchItem, 50, stdin);
           removeTrailing(searchItem);
           strncpy(tempData.prodName, searchItem, len);
           printf("\n");
           printf("Do you want to increase or decrease the quantity?\n");
           printf("Type + to increase\nType - to decrease\n");
           printf("\nAction: ");
           fgets(symbol, size, stdin);
           removeTrailing(symbol);

           if (strcmp(symbol, "+") == 0)
           {
               printf("Enter the quantity to increase with: ");
               fgets(itemQty1, size, stdin);
               removeTrailing(itemQty1);
               itemQty = atoi(itemQty1);

               for (i= 0; i < total; i++)
               {
                  if(strcmp(searchItem, invoice[i].prodName) == 0)
                  {
                     invoice[i].quantity = invoice[i].quantity + itemQty;
                  }
               }

               findMatch = treeFindNode(theTree, (void*)&tempData, 1);
               if (findMatch != NULL)
               {
                  if (((struct info*)findMatch)->quantity > 1)
                  {
               // just reduces the quantity in the inventory
                     reduceQty(theTree, findMatch, 1, itemQty);
                  }
                  else //remove the item from the inventory
                  {
                     treeDeleteNode(theTree, findMatch, 1);
                     count = count -1;
                  }
               }
               else {
                  printf("Not available in inventory\n");
               }

           }
           else if (strcmp(symbol, "-") == 0)
           {
              printf("Enter the quantity to increase with: ");
              fgets(itemQty1, size, stdin);
              removeTrailing(itemQty1);
              itemQty = atoi(itemQty1);

              for (i= 0; i < total; i++)
              {
                 if(strcmp(searchItem, invoice[i].prodName) == 0)
                 {
                    invoice[i].quantity = invoice[i].quantity - itemQty;
                 }
              }

             findMatch = treeFindNode(theTree, (void*)&tempData, 1);

             if (findMatch == NULL)
             {
                 tempData.quantity = tempData.quantity + itemQty;
                 treeInsertNode(theTree, (void*)&tempData, 1);
             }
             else
             {
                ((struct info*)findMatch)->quantity = ((struct info*)findMatch)->quantity +itemQty;
             }
           }
           else
           {
              printf("Re-starting..\n");
           }

       }
       else
       {
         printf("Wrong action! Existing POS System..\n\n");
         for (i = 0; i < count-1; i++)
         {
            inventory[i] = *(struct info*)treeFindNode(theTree, (void*)&items[i], 1);
         }
         printInventory(inventory, count);
         printf("\n");
         printInvoice(invoice, total);
          exit(1);
       }
      }

     }
      else if (strcmp(action, "Y") != 0 && strcmp(action, "Q") != 0)
      {
         printf("Sorry! Invalid action. Please try again!\n\n");

      }
      else if (strcmp(action, "Q") == 0)
      {
        for (i = 0; i < count-1; i++)
        {
           inventory[i] = *(struct info*)treeFindNode(theTree, (void*)&items[i], 1);
        }
        printInventory(inventory, count);
        printf("\n");
        printInvoice(invoice, total);
        exit(1);
      }
   }

   return 0;
}
