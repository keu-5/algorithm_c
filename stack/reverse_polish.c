#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> //文字変換に関するライブラリ

#define STACK_SIZE 100

typedef long ELEM;
ELEM stack[STACK_SIZE];
int n; //スタックポインタ (プログラムカウンタと同じ役割)

//エラーメッセージをプリント、プログラムを終了する
void error(char *s) {
    fprintf(stderr, "%s\n", s); //エラーメッセージをstderrに出力
    exit(1); //プログラムを終了する
}

//スタックを初期化する
void init() {
    n = 0;
}

//スタックにデータを積む
void push(ELEM x) {
    if (n >= STACK_SIZE) {
        error("Stack overflow\n");
    }
    stack[n++] = x; //代入してから足す
}

//スタックからデータを降ろす
ELEM pop() {
    if (n <= 0) {
        error("Stack underflow\n");
    }
    return stack[--n]; //引いてから代入
}

//スタックが空かどうかを調べる。 空なら1, 空でなければ0を返す。
int empty() {
    return n == 0;
}

int main(void) {
    int c;
    long x, a, b;

    printf("逆ポーランド法で計算します\n数値または演算子の間はtabで区切られます\nやめる場合はQ\n");
    printf("入力:\n");

    init();
    while ((c = getchar()) != EOF) { //getchar関数: 文字を一処理ごとに1文字ずつバッファから取り出す。くり返し呼び出すとその都度次の文字を読み込む。
        if (isdigit(c)) { //数値だったらtrue, それ以外ならfalseを返す
            ungetc(c, stdin); //scanfを使いたいのでバッファ(データを一時的にためるメモリ)に一度cをもどす(バッファもFIFO形式)(ちなみに今回の逆ポーランド計算機はLIFO形式)
            scanf("%ld", &x); //バッファの値を読み取る、取り出す
            push(x); //ここでcはバッファから消される
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