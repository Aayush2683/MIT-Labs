#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node * left;
    struct node * right;
} Node;

Node * createNode(int x) {
    Node * new = (Node *) malloc(sizeof(Node));
    new->val = x;
    new->left = NULL;
    new->right = NULL;
    return new;
}

Node * constructTree() {
    int val;
    printf("Enter the value of the root node: ");
    scanf("%d", &val);
    Node * root = createNode(val);

    char choice;
    printf("Do you want to add a left child to %d? (y/n): ", val);
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        root->left = constructTree();
    }

    printf("Do you want to add a right child to %d? (y/n): ", val);
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        root->right = constructTree();
    }

    return root;
}

void postOrder(Node *tree, int * count) {
    if (tree != NULL) {
        *count = *count + 1;
        postOrder(tree->left, count);
        postOrder(tree->right, count);
    }
}

int main() {
    Node * root = constructTree();
    int count = 0;
    postOrder(root, &count);
    printf("Number of nodes in the graph: %d\n", count);
    return 0;
}



