/* Page 213 */

/* List 14.2  非再帰版クイックソート(List 14.1をそのまま書き換えたもの) */


/* 配列aをクイックソートする */
void quick_sort_2(int a[], int n)
{
    int	 l, r, v;
    int	 low[30], high[30];
    int	 sp;

    /* スタックを初期化する */
    low[0]  = 0;
    high[0] = n - 1;
    sp = 1;

    /* スタックが空になるまで繰り返す */
    while (sp > 0) {

	/* スタックから、整列する範囲を取り出す */
	sp--;
	l = low[sp];
	r = high[sp];

	/* 整列する要素が１つなら、何もしない
	   （再びwhile文を実行する） */
	if (l >= r)
	    ;
	else {
	    /* 枢軸vを基準に分割する */
	    v = partition(a, l, r);

	    /* 左、右の順番で部分配列を整列する
	      （スタックなので『右左』の順に積むことに注意） */
	    low[sp]    = v + 1;
	    high[sp++] = r;
	    low[sp]    = l;
	    high[sp++] = v - 1;
	}
    }
}
