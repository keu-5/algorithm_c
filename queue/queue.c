#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define QUEUE_SIZE 5

typedef long ELEM;

//待ち行列の定義
ELEM queue[QUEUE_SIZE + 1];
//待ち行列の先頭
int front;
//待ち行列の末尾
int rear;

//次の要素の添え字を求める
#define next(a) (((a) + 1) % (QUEUE_SIZE + 1)) //関数next(a)を定義

//エラーメッセージ
void error(char *s) {
    fprintf(stderr, "%s\n", s);
}

//待ち行列の初期化
void init() {
    front = rear = 0;
}

//待ち行列にデータを入れる
void enqueue(ELEM x) {
    if (next(rear) == front) {
        error("待ち行列がフルなので要素を入れられません\n");
        return;
    }
    queue[rear] = x;
    rear = next(rear); //QUEUE_SIZEを超えたら0にもどる
}

//待ち行列からデータを取り出す
ELEM dequeue() {
    ELEM x;

    if (front == rear) {
        error("待ち行列が空なので要素を取り出すことができません\n");
        return 0;
    }
    x = queue[front];
    front = next(front);

    return x;
}

//待ち行列が空かどうか調べる
//空なら1, 空でなければ0を返す
int empty() {
    return front == rear;
}

//待ち行列を表示する関数
void display() {
    printf("現在の待ち行列:\n");
    for (int i = front; i!= rear; i = next(i)) {
        printf("%ld\n", queue[i]);
    }
}

int main(void) {
    int a;

    init();
    while (1) {
        printf("1. 要素を入れる\n");
        printf("2. 要素を取り出す\n");
        printf("3. 待ち行列を初期化\n");
        printf("4. 待ち行列が空かどうか調べる\n");
        printf("5. 終了\n");
        printf("どうしますか?:");
        scanf("%d", &a);
        
        switch (a) {
            case 1:
                printf("要素を入れる: ");
                scanf("%d", &a);
                enqueue(a);
                break;
            case 2:
                printf("要素を取り出す: %ld\n", dequeue());
                break;
            case 3:
                init();
                break;
            case 4:
                if (empty()) {
                    printf("待ち行列が空です\n");
                } else {
                    printf("待ち行列が空ではありません\n");
                }
                break;
            case 5:
                exit(0);
                break;
            default:
                printf("不正な入力です\n");
                break;
        }
        display();
        puts("--------------------------------------------------------");
    }
    
    return 0;
}