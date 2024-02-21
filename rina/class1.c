#include <stdio.h>

// これはmain関数です
int main(void) {
    int old, year;
    printf("梨奈は何歳ですか:");
    scanf("%d", &old);

    year = 2024 - old;

    printf("梨奈は%d歳です。%d年生まれです。\n", old, year);
    return 0;
}