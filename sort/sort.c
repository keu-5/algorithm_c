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

  // 処理回数
  int count = 1;

  // NOTE: i番目の値を確定させる
  for (i = 0; i < SIZE - 1; i++) {
    // NOTE: 後ろから比較、前にずらす
    for (j = SIZE - 1; j > i; j--) {
      if (sortedArray[j - 1] > sortedArray[j]) {
        t = sortedArray[j];
        sortedArray[j] = sortedArray[j - 1];
        sortedArray[j - 1] = t;
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

  // NOTE: i番目の値を確定させる
  for (i = 0; i < SIZE - 1; i++) {
    lowest = i;
    lowkey = sortedArray[i];

    // NOTE: i番目以降の値を検証、i番目より小さい要素番号を記憶
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
    // NOTE: i番目の値を検証、j回前にずらす
    while (j >= 1 && sortedArray[j - 1] > sortedArray[j]) {
      t = sortedArray[j];
      sortedArray[j] = sortedArray[j - 1];
      sortedArray[j - 1] = t;
      j--;
      count++;
    }
  }
  printf("選択ソート：%d回\n", count);

  return sortedArray;
}

/*
    シェルソート
*/
int *shell_sort(int a[]) {
  int h, i, j, t;
  int *sortedArray = copy(a);

  int count = 1;

  // NOTE: hの初期値を決める
  // （SIZE/9より大きくするとあんまりソートに変化がなくなるので）
  for (h = 1; h < SIZE / 9; h = h * 3 + 1) {
    ;
  }
  // NOTE: hを3つずつ減らす。最終的にh=1になる
  for (; h > 0; h /= 3) {
    // NOTE: h番目を起点とし、i番目の値を検証
    for (i = h; i < SIZE; i++) {
      j = i;
      // NOTE: i番目の値を検証、jずつずらす  (挿入ソートと似てる)
      while (j >= h && sortedArray[j - h] > sortedArray[j]) {
        t = sortedArray[j];
        sortedArray[j] = sortedArray[j - h];
        sortedArray[j - h] = t;
        j -= h;
        count++;
      }
    }
  }
  printf("シェルソート：%d回\n", count);

  return sortedArray;
}

/*
 * クイックソート
 */
//NOTE: 配列を2つに分割する。枢軸の添え字を返す
int partition(int a[], int l, int r) {
  int i, j, pivot, t;

  // ポインタiとjを初期化する
  i = l - 1; //NOTE: 一番左
  j = r; //NOTE: 一番右
  //NOTE: 一番右端の要素を枢軸にする
  pivot = a[r];
  // ポインタとjがぶつかるまで繰り返す
  for (;;) {
    //NOTE: ポインタiを右へ進める (pivotより大きい値を選択する)
    while (a[++i] < pivot) {
      ;
    }
    //NOTE: ポインタjを左へ進める (pivotより小さい値を選択する)
    while (i < --j && pivot < a[j]) {
      ;
    }
    // ポインタiとjがぶつかったらループを抜ける
    if (i >= j) {
      break;
    }
    //NOTE: iの指す要素とjの指す要素を交換する (それぞれ左右に入れ替える)
    t = a[i];
    a[i] = a[j];
    a[j] = t;
  }
  //NOTE: a[i]と枢軸を交換する (分割後に枢軸を挟み込む, 左側の最大値の要素番号をiとする)
  t = a[j];
  a[i] = a[r];
  a[r] = t;

  return i;
}

// 実際にクイックソートを行う関数
void quick_sort_l(int a[], int l, int r) {
  int v;

  //NOTE: 整列する要素が１つなら、何もしないでreturnする (ソーティング終了)
  if (l >= r) {
    return;
  }

  v = partition(a, l, r);

  //NOTE: 枢軸の左側をソート
  quick_sort_l(a, l, v-1);

  //NOTE: 枢軸の右側をソート
  quick_sort_l(a, v+1, r);
}

// クイックソート
int *quick_sort(int a[]) {
  int *sortedArray = copy(a);

  printf("クイックソート\n");
  quick_sort_l(sortedArray, 0, SIZE - 1);

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

  sortedArray = shell_sort(a);
  show(sortedArray);

  //BUG: アルゴリズムは間違ってないはずなのに違う値を返す (なんか要素が減ってる)
  sortedArray = quick_sort(a);
  show(sortedArray);

  return 0;
}
