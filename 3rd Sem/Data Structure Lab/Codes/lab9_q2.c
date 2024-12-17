// UNION and INTERSECTION set operations on singly linked lists with and without header node.

// With Header Node

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insert(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void printList(struct Node* head) {
    struct Node* temp = head->next; 
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

struct Node* unionSet(struct Node* list1, struct Node* list2) {
    struct Node* result = createNode(-1); 
    struct Node* temp = result;

    struct Node* temp1 = list1->next; 
    while (temp1 != NULL) {
        insert(result, temp1->data);
        temp1 = temp1->next;
    }

    struct Node* temp2 = list2->next; 
    while (temp2 != NULL) {
        struct Node* temp3 = result->next;
        int found = 0;
        while (temp3 != NULL) {
            if (temp3->data == temp2->data) {
                found = 1;
                break;
            }
            temp3 = temp3->next;
        }
        if (!found) {
            insert(result, temp2->data);
        }
        temp2 = temp2->next;
    }

    return result;
}

struct Node* intersectionSet(struct Node* list1, struct Node* list2) {
    struct Node* result = createNode(-1); 
    struct Node* temp1 = list1->next;

    while (temp1 != NULL) {
        struct Node* temp2 = list2->next;
        while (temp2 != NULL) {
            if (temp1->data == temp2->data) {
                insert(result, temp1->data);
                break;
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }

    return result;
}

int main() {
    struct Node* list1 = createNode(-1); 
    struct Node* list2 = createNode(-1);

    int n1, n2, data;

    printf("Enter the number of elements in List 1: ");
    scanf("%d", &n1);
    printf("Enter elements of List 1:\n");
    for (int i = 0; i < n1; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &data);
        insert(list1, data);
    }

    printf("Enter the number of elements in List 2: ");
    scanf("%d", &n2);
    printf("Enter elements of List 2:\n");
    for (int i = 0; i < n2; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &data);
        insert(list2, data);
    }

    printf("\nList 1: ");
    printList(list1);
    printf("List 2: ");
    printList(list2);

    struct Node* unionResult = unionSet(list1, list2);
    printf("Union of List 1 and List 2: ");
    printList(unionResult);

    struct Node* intersectionResult = intersectionSet(list1, list2);
    printf("Intersection of List 1 and List 2: ");
    printList(intersectionResult);

    return 0;
}

// Without Header Node

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insert(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

struct Node* unionSet(struct Node* list1, struct Node* list2) {
    struct Node* result = NULL;

    struct Node* temp1 = list1;
    while (temp1 != NULL) {
        insert(&result, temp1->data);
        temp1 = temp1->next;
    }

    struct Node* temp2 = list2;
    while (temp2 != NULL) {
        struct Node* temp3 = result;
        int found = 0;
        while (temp3 != NULL) {
            if (temp3->data == temp2->data) {
                found = 1;
                break;
            }
            temp3 = temp3->next;
        }
        if (!found) {
            insert(&result, temp2->data);
        }
        temp2 = temp2->next;
    }

    return result;
}

struct Node* intersectionSet(struct Node* list1, struct Node* list2) {
    struct Node* result = NULL;

    struct Node* temp1 = list1;
    while (temp1 != NULL) {
        struct Node* temp2 = list2;
        while (temp2 != NULL) {
            if (temp1->data == temp2->data) {
                insert(&result, temp1->data);
                break;
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }

    return result;
}

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;

    int n1, n2, data;

    printf("Enter the number of elements in List 1: ");
    scanf("%d", &n1);
    printf("Enter elements of List 1:\n");
    for (int i = 0; i < n1; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &data);
        insert(&list1, data);
    }

    printf("Enter the number of elements in List 2: ");
    scanf("%d", &n2);
    printf("Enter elements of List 2:\n");
    for (int i = 0; i < n2; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &data);
        insert(&list2, data);
    }

    printf("\nList 1: ");
    printList(list1);
    printf("List 2: ");
    printList(list2);

    struct Node* unionResult = unionSet(list1, list2);
    printf("Union of List 1 and List 2: ");
    printList(unionResult);

    struct Node* intersectionResult = intersectionSet(list1, list2);
    printf("Intersection of List 1 and List 2: ");
    printList(intersectionResult);

    return 0;
}

