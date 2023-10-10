#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> //文字変換に関するライブラリ

#define STACK_SIZE 100

typedef long ELEM;
ELEM stack[STACK_SIZE];
int n; //スタックポインタ

//エラーメッセージをプリント、プログラムを終了する
void error(char *s) {
    fprintf(stderr, "%s\n", s); //エラーメッセージをstderrに出力
    exit(1); //プログラムを終了する
}

//スタックを初期化する
void init() {
    n = 1;
}

//スタックにデータを積む
void push(ELEM x) {
    if (n >= STACK_SIZE) {
        error("Stack overflow\n");
    }
    stack[n++] = x;
}

//スタックからデータを降ろす
ELEM pop() {
    if (n <= 0) {
        error("Stack underflow\n");
    }
    return stack[--n];
}

//スタックが空かどうかを調べる。 空なら1, 空でなければ0を返す。
int empty() {
    return n == 0;
}

int main(void) { //NOTE:ひとつずれてる？
    int c;
    long x, a, b;

    init();
    while ((c = getchar())!= EOF) { //文字の末端まで(EOF)まで
        if (isdigit(c)) { //数値だったらtrue, それ以外ならfalseを返す
            ungetc(c, stdin);
            scanf("%ld", &x);
            push(x);
        } else {
            switch (c) {
                case '+':
                    b = pop();
                    a = pop();
                    push(a + b);
                    break;
                case '-':
                    b = pop();
                    a = pop();
                    push(a - b);
                    break;
                case '*':
                    b = pop();
                    a = pop();
                    push(a * b);
                    break;
                case '/':
                    b = pop();
                    a = pop();
                    if (b == 0) {
                        error("Division by zero\n");
                    }
                    push(a / b);
                    break;
                case '\n':
                    if (!empty()) {
                        printf("答えは%ldです。\n", pop());
                    }
                    init();
                    break;
                case '\t':
                    break;
                case 'q':
                    exit(1);
                default:
                    printf("不正な文字がありました。\n");
                    printf("入力してください。\n");
                    while ((c = getchar()) != EOF && c != '\n') {
                        ;
                    }
                    break;
            }
        }
    }
} 