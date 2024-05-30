#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode* buildTree() {
    int data;
    TreeNode* root;

    printf("Enter the data for the root node (Enter -1 for NULL): ");
    scanf("%d", &data);
    if (data == -1)
        return NULL;

    root = createNode(data);

    printf("Enter the left child of %d:\n", data);
    root->left = buildTree();

    printf("Enter the right child of %d:\n", data);
    root->right = buildTree();

    return root;
}

TreeNode* findCCA(TreeNode* root, int n1, int n2) {
    if (root == NULL)
        return NULL;

    // If either n1 or n2 matches with root's key, return root
    if (root->data == n1 || root->data == n2)
        return root;

    // Search for n1 and n2 in left and right subtrees
    TreeNode* leftCCA = findCCA(root->left, n1, n2);
    TreeNode* rightCCA = findCCA(root->right, n1, n2);

    // If both n1 and n2 are found in left and right subtrees, then root is the CCA
    if (leftCCA != NULL && rightCCA != NULL)
        return root;

    // Otherwise, return the non-null node found in either left or right subtree
    return (leftCCA != NULL) ? leftCCA : rightCCA;
}

int main() {
    TreeNode* root = NULL;
    int n1, n2;

    printf("Building the binary tree:\n");
    root = buildTree();

    printf("\nEnter two nodes to find their closest common ancestor: ");
    scanf("%d %d", &n1, &n2);

    TreeNode* cca = findCCA(root, n1, n2);

    if (cca)
        printf("Closest Common Ancestor of %d and %d is %d\n", n1, n2, cca->data);
    else
        printf("No common ancestor found for %d and %d\n", n1, n2);

    return 0;
}