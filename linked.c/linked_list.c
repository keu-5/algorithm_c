#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *createNode(int data) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertNode(struct Node **head, int data, int position) {
    if (position < 0) {
        printf("無効な位置です。\n");
        return;
    }

    struct Node *newNode = createNode(data);

    if (position == 0) {
        newNode->next = *head;
        *head = newNode;
    } else {
        struct Node *current = *head;
        int currentPos = 0;

        while (current != NULL && currentPos < position - 1) {
            current = current->next;
            currentPos++;
        }

        if (current == NULL) {
            printf("指定された一はリストの長さを超えています。\n");
            free(newNode);
            return;
        }

        newNode->next = current->next;
        current->next = newNode;
    }
}

void deleteNode(struct Node **head, int target) {
    struct Node *current = *head;
    struct Node *prev = NULL;

    if (current != NULL && current->data == target) {
        *head = current->next;
        free(current);
        return;
    }

    while (current != NULL && current->data != target) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        prev->next = current->next;
        free(current);
    }
}

void printList(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = createNode(1);
    struct Node* second = createNode(3);
    struct Node* third = createNode(4);

    head->next = second;
    second->next = third;

    printf("連結リストの要素: ");
    printList(head);

    int dataToInsert = 2;
    int insertPosition = 1;
    insertNode(&head, dataToInsert, insertPosition);

    printf("値 %d を持つノードを位置 %d に挿入後の連結リスト: ", dataToInsert, insertPosition);
    printList(head);

    int target = 2;
    deleteNode(&head, target);

    printf("値 %d を持つノードを削除後の連結リスト: ", target);
    printList(head);

    // メモリの解放
    struct Node* current = head;
    while (current != NULL) {
        struct Node* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}