#include <stdio.h>

//変数のアドレスによってパラメータを受け渡すことを参照渡し(変数の値を渡す方法を値渡し)
void foo(int a, int b, int *sum, int *prod) {
    *sum = a + b;
    *prod = a * b;
}

int main(void) {
    int a = 10;
    int b = 20;
    int sum = 0;
    int prod = 0;
    foo(a, b, &sum, &prod);
    printf("%d + %d = %d\n", a, b, sum);
    printf("%d * %d = %d\n", a, b, prod);
    return 0;
}