#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
} head;

int size() {
    int i = 0;
    struct Node *temp = head.next;
    while (temp!= NULL) {
        i++;
        temp = temp->next;
    }
    return i;
}

void insert(int data, int num) {
    struct Node *newNode;
    newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    struct Node *temp = &head;

    if (num < 0 || num > size()) {
        printf("Invalid input\n");
        return;
    } else if (num == 0) {
        newNode->next = &head;
        head = *newNode;
        return;
    } else {
        for (int i = 0; i < num; i++) {
            temp = temp->next;
        }
        newNode->data = data;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

//NULLが認識されていない?
void show() {
    struct Node *temp = &head;
    while (temp->next != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(void) {
    head.data = 0;
    head.next = NULL;

    insert(1, 0);
    insert(2, 1);
    printf("%d\n", head.data);
    head = *head.next;
    printf("%d\n", head.data);
    return 0;
}