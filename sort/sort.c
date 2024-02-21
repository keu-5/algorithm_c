#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 40

// 配列をランダムに初期化
void init(int a[]) {
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        a[i] = rand() % 100;
    }
}

// 配列をコピー(破壊防止)
int *copy(int a[]) {
    int *copy = malloc(sizeof(int) * SIZE);

    if (copy == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < SIZE; i++) {
        copy[i] = a[i];
    }
    
    return copy;
}

// 配列を表示
void show(int *a) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

/*
    バブルソート：前後を比較して入れ替える
*/
int *bubble_sort(int a[]) {
    int i, j, t;
    int *sortedArray = copy(a);
    
    //処理回数
    int count = 1;
    
    //NOTE: i番目の値を確定させる
    for (i = 0; i < SIZE - 1; i++) {
        //NOTE: 後ろから比較、前にずらす
        for (j = SIZE - 1; j > i; j--) {
            if (sortedArray[j-1] > sortedArray[j]) {
                t = sortedArray[j];
                sortedArray[j] = sortedArray[j-1];
                sortedArray[j-1] =t;
            }
            count++;
        }
    }
    
    printf("バブルソート：%d回\n", count);
    return sortedArray;
}

/*
    選択ソート
*/
int *selection_sort(int a[]) {
    int i, j, t, lowest, lowkey;
    int *sortedArray = copy(a);
    
    int count = 1;

    //NOTE: i番目の値を確定させる
    for (i = 0; i < SIZE - 1; i++) {
        lowest = i;
        lowkey = sortedArray[i];

        //NOTE: i番目以降の値を検証、i番目より小さい要素番号を記憶
        for (j = i + 1; j < SIZE; j++) {
            if (sortedArray[j] < lowkey) {
                lowest = j;
                lowkey = sortedArray[j];
            }
            count++;
        }
        t = sortedArray[i];
        sortedArray[i] = sortedArray[lowest];
        sortedArray[lowest] = t;
    }
    printf("選択ソート：%d回\n", count);
    
    return sortedArray;
}

/*
    挿入ソート
    NOTE: 選択ソートと違い、入れ替えず割り込ませる
*/
int *insertion_sort(int a[]) {
    int i, j, t;
    int *sortedArray = copy(a);
    
    int count = 1;

    for (i = 1; i < SIZE; i++) {
        j = i;
        //NOTE: i番目の値を検証、j回前にずらす
        while (j >= 1 && sortedArray[j-1] > sortedArray[j]) {
            t = sortedArray[j];
            sortedArray[j] = sortedArray[j-1];
            sortedArray[j-1] = t;
            j--;
            count++;
        }
    }
    printf("選択ソート：%d回\n", count);

    return sortedArray;
}


int main(void) {
    int a[SIZE];
    int *sortedArray;
    
    init(a);
    show(a);

    sortedArray = bubble_sort(a);
    show(sortedArray);
    
    sortedArray = selection_sort(a);
    show(sortedArray);
    
    sortedArray = insertion_sort(a);
    show(sortedArray);
    
    return 0;
}