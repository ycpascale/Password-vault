#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "balancedTreeAPI.h"
#include "tree.h"
#include "other.h"

Tree *createBalancedBinTree(int (*compareFP) (void *data1, void *data2, size_t mode), void (*destroyFP) (void *toBeDeleted),void *(*copyFP)(void *toBeCopy))
{
   Tree *newTree;

   newTree = malloc(sizeof(Tree));
   newTree->root = NULL;
   newTree->compareFP = compareFP;
   newTree->destroyFP = destroyFP;
   newTree->copyFP = copyFP;

   return newTree;
}

TreeNode *createBalancedBinNode(void *data)
{
   TreeNode *newNode;

   newNode = malloc(sizeof(TreeNode));
   newNode->data = data;
   newNode->left = NULL;
   newNode->right = NULL;
   newNode->height = 1;
   newNode->count = 0;

   return newNode;
}

void destroyBalancedBinTree(Tree *toBeDeleted)
{
   if (toBeDeleted->root != NULL)
   {
      free(toBeDeleted->root);
   }
   free(toBeDeleted);

}

void treeInsertNode(Tree *theTree, void *toBeInserted, size_t mode1)
{
   theTree->root = insert(theTree->root, toBeInserted, theTree->compareFP, mode1);

   return;

}

TreeNode *insert(TreeNode *root, void *data, int (*compareFP) (void *data1, void *data2, size_t mode), size_t mode1)
{
   TreeNode * tempNode;

   if (root == NULL)
   {
      tempNode = createBalancedBinNode(data);
      return tempNode;
   }

   /*met koT droit de root la*/
   if (compareFP(root->data, data, mode1) < 0)
   {
      root->right = insert(root->right, data, compareFP, mode1);

   }
   /*meT kkot gauche de root la*/
   else if (compareFP(root->data, data, mode1) >= 0)
   {
      root->left = insert(root->left, data, compareFP, mode1);
   }
   else
   {
      return root;
   }


   root->height = 1 + max(height(root->left), height(root->right));

   int balance = checkBalanceFactor(root);

   if (balance > 1)
   {
      if (compareFP(data, root->left->data, mode1) < 0)
      {
         //RR
         return RRotation(root);
      }
      else
      {
         root->left = LRotation(root->left);
         return RRotation(root);
      }
   }
   else if (balance < -1)
   {
      if (compareFP(data, root->right->data, mode1) > 0)
      {
         return LRotation(root);
      }
      else
      {
         root->right = RRotation(root->right);
         return LRotation(root);
      }

   }

   return root;
}

TreeNode *RRotation(TreeNode *root)
{
   TreeNode* firstNode;
   TreeNode *secondNode;

   firstNode = root->left;
   secondNode = firstNode->right;

   firstNode->right = root;
   root->left = secondNode;

   root->height = max(height(root->left), height(root->right)) + 1;
   firstNode->height = max(height(firstNode->left), height(firstNode->right)) +1;

   return firstNode;
}

TreeNode *LRotation(TreeNode *root)
{
   TreeNode* firstNode;
   TreeNode *secondNode;

   firstNode = root->right;
   secondNode = firstNode->left;

   firstNode->left = root;
   root->right = secondNode;

   root->height = max(height(root->left), height(root->right)) + 1;
   firstNode->height = max(height(firstNode->left), height(firstNode->right)) +1;

   return firstNode;
}



int height(TreeNode *root)
{
   if (root == NULL)
   {
      return 0;
   }
   else{
      return root->height;
   }
}

int max (int first, int second)
{
   if (first > second)
   {
      return first;
   }
   else{
      return second;
   }
}

int checkBalanceFactor(TreeNode *root)
{

   if (root == NULL)
   {
      return 0;
   }
   else
   {
       return (height(root->left) - height(root->right));

   }
}



int treeIsEmpty(Tree *theTree)
{
   if (theTree->root == NULL)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}


void *treeFindNode(Tree *theTree, void *data, size_t mode2)
{
   TreeNode *tempNode;

   if (theTree == NULL || data == NULL)
   {
     return NULL;
   }

   tempNode = find(theTree->root, data, theTree->compareFP, mode2);
   if (tempNode == NULL)
   {
       return NULL;
   }
   else
   {
       return tempNode->data;
   }
}

TreeNode *find(TreeNode *root, void *data, int (*compareFP) (void *data1, void *data2, size_t mode), size_t mode2)
{
   if (root == NULL)
   {
      return NULL;
   }
   else if (compareFP(root->data, data, mode2) == 0)
   {
      return root;
   }
   else if (compareFP(root->data, data, mode2) > 0)
   {
      return find (root->left, data, compareFP, mode2);
   }
   else
   {
      return find(root->right, data, compareFP, mode2);
   }
}

void *treeFindMin(Tree *theTree)
{
   TreeNode *tempNode;

   tempNode = theTree->root;

   if (theTree->root == NULL)
   {
      return NULL;
   }

   while (tempNode->left != NULL)
   {
      tempNode = tempNode->left;
   }

   return (tempNode->data);

}

void *treeFindMax(Tree *theTree)
{
   TreeNode *tempNode;

   tempNode = theTree->root;

   if (theTree->root == NULL)
   {
      return NULL;
   }

   while (tempNode->right != NULL)
   {
      tempNode = tempNode->right;
   }

   return (tempNode->data);

}


void treePreOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
   preOrderPrint(theTree->root, printNodeFP);
}

void preOrderPrint(TreeNode *tempNode, void (*printNodeFP) (void *data))
{
   if (tempNode != NULL)
   {
      printNodeFP(tempNode->data);
      preOrderPrint(tempNode->left, printNodeFP);
      preOrderPrint(tempNode->right, printNodeFP);
   }
}

void treeInOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
  inOrderPrint(theTree->root, printNodeFP);
}

void inOrderPrint(TreeNode *tempNode, void (*printNodeFP) (void *data))
{
   if (tempNode != NULL)
   {
      inOrderPrint(tempNode->left, printNodeFP);
      printNodeFP(tempNode->data);
      inOrderPrint(tempNode->right, printNodeFP);
   }
}

void treePostOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
  postOrderPrint(theTree->root, printNodeFP);

}

void postOrderPrint(TreeNode *tempNode, void (*printNodeFP) (void *data))
{
   if (tempNode != NULL)
   {
      postOrderPrint(tempNode->left, printNodeFP);
      postOrderPrint(tempNode->right, printNodeFP);
      printNodeFP(tempNode->data);
   }
}


void treeDeleteNode(Tree *theTree, void *toBeDeleted, size_t mode3)
{
   TreeNode *tempNode;

   tempNode = find(theTree->root, toBeDeleted, theTree->compareFP, mode3);
   if (tempNode != NULL)
   {
      tempNode->data = NULL;
      tempNode->height = 0;
   }

}

void printNodeFP (void *data)
{
   if (data != NULL)
   {
      printf("%d-> ", *(int*)data);
   }
}

void destroyFP(void *data)
{
   return;
}

void *copyFP(void *data)
{
  return data;
}

int compareFP (void *first, void *second, size_t type)
{
   if (first == NULL)
   {
      return 1;
   }
   struct info *ia = (struct info*)first;  //root
   struct info *ib = (struct info*)second;  //data sent

  // char one[100];
  // char two[100];
//   int length1 = 0;
//   int length2 = 0;

   if (type == 1)
   {
  // length1 = strlen(ia->prodName);
//   strncpy(one, ia->prodName, length1);
//   printf("  one: %s\n", one);

  // length2 = strlen(ib->prodName);
//   strncpy(two, ib->prodName, length2);
//   printf("  two: %s\n", two);



   if (strcmp(ia->prodName, ib->prodName) > 0)
   {
      return 1;
   }
   else if (strcmp(ia->prodName, ib->prodName) < 0)
   {
      return -1;
   }
   else {
     return 0;
   }
 }

 return 0;

/*   if (length1 > length2)
   {
      for(i = 0; i < length2; i++)
      {
         if (ia->prodName[i] == ib->prodName[i])
         {
            i++;
         }
         else if (ia->prodName[i] > ib->prodName[i])
         {
            return (1);
         }
         else if (ia->prodName[i] < ib->prodName[i])
         {
            return (-1);
         }
      }
      return 0; //sa kan ena duplicate which is impossible
   }

   if (length1 <= length2)
   {
      for(i = 0; i < length1; i++)
      {
         if (ia->prodName[i] == ib->prodName[i])
         {
            i++;
         }
         else if (ia->prodName[i] > ib->prodName[i])
         {
            return (1);
         }
         else if (ia->prodName[i] < ib->prodName[i])
         {
            return (-1);
         }
      }
      return 0; //sa kan ena duplicate which is impossible
   }
   return 0;*/
}


void reduceQty(Tree *tree, void *data, size_t mode3, int num)
{
   void *tempData;

    tempData = treeFindNode(tree, data, mode3);
    if (tempData == NULL)
    {
        return;
    }
    else
    {
        ((struct info*)tempData)->quantity = ((struct info*)tempData)->quantity - num;
    }

}
