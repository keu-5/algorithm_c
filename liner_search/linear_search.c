#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

// データの数
#define NUM 100000
// 名前の最大文字数
#define NAME_MAX 8

// 構造体
typedef struct {
    int number;
    char name[NAME_MAX];
} DATA_T; //構造体をもつ型を宣言

/*線形探索を行う関数
* data[] : サーチを行うデータの集合
* num : サーチする番号
* num_data : data[]のデータ数
*/
int linearSearchByNumber(DATA_T data[], int number, int num_data) {
    int i;
    for (i = 0; i < num_data; i++) {
        //先頭から1つずつ比較
        if (data[i].number == number) {
            //見つかった場合終了
            return i;
        }
    }
    //見つからなかった場合
    return -1;
}

//配列を初期化する関数
void initArray(DATA_T a[], int data_num) {
    int i;
    int c;
    int num_name;
    int num_alphabet;

    //numberを乱数で初期化
    for (i = 0; i < data_num; i++) {
        a[i].number = rand() % data_num;
    }

    //アルファベットの数を計算
    num_alphabet = 'Z' - 'A' + 1;

    //nameをランダムな文字列で初期化
    for (i = 0; i < data_num; i++) {
        //名前の文字数を決定(1からNAME_MAX -１まで)
        num_name = (rand() % (NAME_MAX - 1)) + 1;
        //文字数分の文字を格納(A to Z)
        for (c = 0; c < num_name; c++) {
            a[i].name[c] = rand() % num_alphabet + 'A';
        }
        //最後に塗る文字を格納
        a[i].name[c] = '\0';
    }
}

int main(void) {
    DATA_T data[NUM];
    int number;
    char name[NAME_MAX];
    int num_data;
    int ret;

    clock_t start, end;

    //現在時刻の情報で初期化
    srand((unsigned int)time(NULL));
    //データ数を設定
    num_data = NUM;
    //探索する数字を設定
    number = NUM -1;

    //配列を初期化
    initArray(data, num_data);

    printf("find%d\n", number);
    start = clock();

    //線形探索
    ret = linearSearchByNumber(data, number, num_data);
    end = clock();

    //処理結果表示
    if (ret == -1) {
        printf("data not found\n");
    } else {
        printf("data[%d].number = %d\n", ret, data[ret].number);
    }
    printf("processing time : %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}