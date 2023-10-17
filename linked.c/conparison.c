#include <stdio.h>
#include <stdlib.h>

// 連結リストのノードを表す構造体
typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *head = NULL;  // リストの先頭

// リストに要素を追加する関数
void insert(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("メモリが足りません\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = head;
    head = newNode;
    printf("要素 %d をリストに追加しました\n", data);
}

// リストから要素を削除する関数
void delete(int data) {
    if (head == NULL) {
        printf("リストは空です\n");
        return;
    }

    Node *current = head;
    Node *prev = NULL;
    while (current != NULL) {
        if (current->data == data) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("要素 %d を削除しました\n", data);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("要素 %d はリストに見つかりませんでした\n", data);
}

// リストの内容を表示する関数
void display() {
    Node *current = head;
    printf("リストの内容: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    int choice, data;

    while (1) {
        printf("\n連結リスト操作メニュー:\n");
        printf("1. 要素を追加\n");
        printf("2. 要素を削除\n");
        printf("3. リストを表示\n");
        printf("4. 終了\n");
        printf("選択: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("追加する要素を入力してください: ");
                scanf("%d", &data);
                insert(data);
                break;
            case 2:
                printf("削除する要素を入力してください: ");
                scanf("%d", &data);
                delete(data);
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
            default:
                printf("無効な選択です\n");
        }
    }

    return 0;
}