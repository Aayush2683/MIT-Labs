#include <stdio.h>
#include <stdlib.h>

struct AVLNode {
    int key;
    struct AVLNode *left, *right;
    int height;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct AVLNode *node) {
    return (node == NULL) ? 0 : node->height;
}

struct AVLNode *newNode(int key) {
    struct AVLNode *node = (struct AVLNode *)malloc(sizeof(struct AVLNode));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

struct AVLNode *rightRotate(struct AVLNode *y) {
    struct AVLNode *x = y->left, *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

struct AVLNode *leftRotate(struct AVLNode *x) {
    struct AVLNode *y = x->right, *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int getBalance(struct AVLNode *N) {
    return (N == NULL) ? 0 : height(N->left) - height(N->right);
}

struct AVLNode *insert(struct AVLNode *node, int key) {
    if (node == NULL) return newNode(key);
    if (key < node->key) node->left = insert(node->left, key);
    else if (key > node->key) node->right = insert(node->right, key);
    else return node;
    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key) return rightRotate(node);
    if (balance < -1 && key > node->right->key) return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void inorder(struct AVLNode *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

struct AVLNode *successor(struct AVLNode *root, int key) {
    struct AVLNode *current = root, *succ = NULL;
    while (current != NULL) {
        if (current->key > key) { succ = current; current = current->left; }
        else if (current->key < key) current = current->right;
        else { if (current->right != NULL) return current->right; break; }
    }
    return succ;
}

struct AVLNode *predecessor(struct AVLNode *root, int key) {
    struct AVLNode *current = root, *pred = NULL;
    while (current != NULL) {
        if (current->key < key) { pred = current; current = current->right; }
        else if (current->key > key) current = current->left;
        else { if (current->left != NULL) return current->left; break; }
    }
    return pred;
}

int main() {
    struct AVLNode *root = NULL;
    int n, key;
    printf("Enter the number of keys: ");
    scanf("%d", &n);
    printf("Enter the keys:\n");
    for (int i = 0; i < n; i++) { scanf("%d", &key); root = insert(root, key); }
    printf("Inorder traversal of the constructed AVL tree is: "); inorder(root); printf("\n");
    printf("Enter the key for which you want to find successor and predecessor: ");
    scanf("%d", &key);
    struct AVLNode *succ = successor(root, key);
    if (succ != NULL) printf("Successor of %d is %d\n", key, succ->key);
    else printf("No successor found for %d\n", key);
    struct AVLNode *pred = predecessor(root, key);
    if (pred != NULL) printf("Predecessor of %d is %d\n", key, pred->key);
    else printf("No predecessor found for %d\n", key);
    return 0;
}