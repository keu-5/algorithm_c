/* Page 247 */

/* List 16.2   関数downheapとdelete_min */

#include <stdio.h>				/* @@@@ */
#define MAX_HEAP	1000			/* @@@@ */
int a[MAX_HEAP+1];				/* @@@@ */
int n;						/* @@@@ */


/* ヒープの先頭の要素a[1]を必要なところまで沈める */
void downheap()
{
    int i, j;
    int val;

    /* 沈められる要素の値をvalにセットしておく */
    val = a[1];

    /* 根から始めて、節iが子を持っている限り繰り返す */
    i = 1;
    while (i <= n/2) {

	/* 節iの子のうち小さいほうを節jとする */
	j = i * 2;
	if (j+1 <= n && a[j] > a[j+1])
	    j++;

	/* もし、親が子より大きくないという関係が成り立てば、
	   これ以上沈める必要はない */
	if (val <= a[j])
	    break;

	/* 節iに節jの値を入れて、節jに注目する */
	a[i] = a[j];
	i = j;
    }

    /* 先頭にあった要素を節iに入れる */
    a[i] = val;
}

/* ヒープから最小の要素を削除する。要素の値を返す */
int delete_min()
{
    int	 val;

    /* ヒープが空でないことを確認する */
    if (n < 1) {
	fprintf(stderr, "ヒープが空です\n");
	exit(1);
    }

    /* 根の要素をリターン値にする
       (ヒープの先頭が根に当たる) */
    val = a[1];

    /* ヒープの最後の要素を先頭に移動する */
    a[1] = a[n--];

    /* 先頭に移動した要素を適切な場所まで沈める */
    downheap();

    return val;
}
