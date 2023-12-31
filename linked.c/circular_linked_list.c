#include <stdio.h>
#include <stdlib.h>

// 循環リストのノードを表す構造体
typedef struct Node {
    int data;
    struct Node *next;
} Node; //struct Node → Nodeとして利用できるようにする

Node *head = NULL;  // リストの先頭

// リストに要素を追加する関数
void insert(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) { //メモリ確保に失敗した場合、newNodeはNULLになる
        printf("メモリが足りません\n");
        exit(1);
    }
    newNode->data = data;

    if (head == NULL) {
        newNode->next = newNode;  // リストが空の場合、自己参照に設定
        head = newNode; //循環リストなので、head->next = newNode
    } else {
        Node *temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;  // 新しいノードが先頭ノードを指す
    }

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
    do {
        if (current->data == data) {
            if (current == head) {
                // 先頭ノードの削除の場合、headを更新
                Node *temp = head;
                while (temp->next != head) {
                    temp = temp->next;
                }
                head = current->next;
                temp->next = head;
            } else {
                prev->next = current->next;
            }

            free(current);
            printf("要素 %d を削除しました\n", data);
            return;
        }

        prev = current;
        current = current->next;
    } while (current != head);

    printf("要素 %d はリストに見つかりませんでした\n", data);
}

// リストの内容を表示する関数
void display() {
    if (head == NULL) {
        printf("リストは空です\n");
        return;
    }

    Node *current = head;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != head);

    printf("\n");
}

int main() {
    int choice, data;

    while (1) {
        printf("\n循環リスト操作メニュー:\n");
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
