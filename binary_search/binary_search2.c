#include <stdio.h>

struct {
    int key;
    int data;
} table[100]; //構造体を含む配列の設定

int n;

int binary_search(int key) {
    int low, high, middle;

    low = 0;
    high = n - 1;

    while (low <= high) {
        middle = (low + high) / 2;

        if (key == table[middle].key) {
            return table[middle].data;
        } else if (key < table[middle].key) {
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }
    
    return -1; // キーが見つからなかった場合は-1を返す
}

void add_binary(int key, int data) {
    int low, high, middle;
    int pos;

    low = 0;
    high = n - 1; //NOTE:ここどうする?
    
}

int main(void) {
    // テーブルの初期化
    n = 5; // テーブルの要素数を設定
    table[0].key = 1;
    table[0].data = 10;
    table[1].key = 3;
    table[1].data = 20;
    table[2].key = 5;
    table[2].data = 30;
    table[3].key = 7;
    table[3].data = 40;
    table[4].key = 9;
    table[4].data = 50;

    int search_key = 5;
    int result = binary_search(search_key);

    if (result != -1) {
        printf("キー %d はデータ %d に対応しています。\n", search_key, result);
    } else {
        printf("キー %d は見つかりませんでした。\n", search_key);
    }

    return 0;
}

