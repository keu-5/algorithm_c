/* Page 249 */

/* List 16.3   関数upheapとinsert */

#include <stdio.h>				/* @@@@ */
#define MAX_HEAP	1000			/* @@@@ */
int a[MAX_HEAP+1];				/* @@@@ */
int n;						/* @@@@ */


/* ヒープ中のx番目の要素を必要な場所まで浮かび上がらせる */
void upheap(int x)
{
    int	 val;

    /* 浮かび上がらせる要素の値をvalに入れておく */
    val = a[x];

    /* 要素が根まで浮かび上がっていない、かつ
       「親が子より大きい」間繰り返す */
    while (x > 1 && a[x/2] > val) {

	/* 親の値を子に移す */
	a[x] = a[x/2];

	/* 注目点を親に移す */
	x /= 2;
    }

    /* 最終的な落ち着き先が決まった */
    a[x] = val;
}

/* ヒープに要素elemを登録する */
void insert(int elem)
{
    /* ヒープに登録できる余裕があるか確認する */
    if (n >= MAX_HEAP) {
	fprintf(stderr, "これ以上ヒープに要素を登録できません\n");
	exit(1);
    }

    /* 要素をとりあえずヒープの最後に入れる */
    a[++n] = elem;

    /* 追加した要素を浮かび上がらせる */
    upheap(n);
}
