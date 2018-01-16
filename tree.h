#ifndef STUDENT_TREE_API_
#define STUDENT_TREE_API_
#include "balancedTreeAPI.h"

/*You may add anything to this .h file that you need to add to your tree ADT*/

//YOU MUST LEAVE THESE TYPEDEFS AS IS.
/**typedef for struct name*/
typedef struct BalancedBinTreeNode TreeNode;

/**typedef for struct name*/
typedef struct BalancedBinTree Tree;


/*complete the struct definitions.  You can change the existing parts if you wish.
*/
struct BalancedBinTree {
  //define your tree here.  You can change these if you need to but your tree must be abstract.
    TreeNode *root; ///< pointer to generic data that is to be stored in the tree
    int (*compareFP) (void *data1, void *data2, size_t mode); ///< function pointer to a comparison function for the purpose of inserting and deleting elements
    void (*destroyFP) (void *data); ///< function pointer to a function to free a single pointer that is deleted from the tree
    void *(*copyFP)(void *toBeCopy); ///< function pointer to a function that copies pointer data

  };



struct BalancedBinTreeNode{
    void *data; ///< pointer to generic data that is to be stored in the heap
    TreeNode *left; ///< pointer to left tree node of current node. Null if empty.
    TreeNode *right; ///< pointer to right tree node of current node. Null if empty.

    //Add additional structure elements here
    int height;
    int count;
};

//add function prototypes as necessary

TreeNode *insert(TreeNode *root, void *data, int (*compareFP) (void *data1, void *data2, size_t mode), size_t mode1);
void preOrderPrint(TreeNode *tempNode, void (*printNodeFP) (void *data));
void inOrderPrint(TreeNode *tempNode, void (*printNodeFP) (void *data));
void postOrderPrint(TreeNode *tempNode, void (*printNodeFP) (void *data));
TreeNode *find(TreeNode *root, void *data, int (*compareFP) (void *data1, void *data2, size_t mode), size_t mode2);
TreeNode *RRotation(TreeNode *root);
TreeNode *LRotation(TreeNode *root);
int height(TreeNode *root);
int max (int first, int second);
int checkBalanceFactor(TreeNode *root);
void printNodeFP (void *data);
int compareFP (void *first, void *second, size_t type);
void destroyFP(void *data);
void *copyFP(void *data);
void reduceQty(Tree *tree, void *data, size_t mode3, int num);



#endif
