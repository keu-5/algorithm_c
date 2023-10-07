/* Page 237 */

/* List 16.1  探索木を利用した整列アルゴリズムのスケッチ */
sort(int a[], int n)
{
    int	 i;

    /* すべての要素を探索木に挿入する */
    for (i = 0; i < n; i++)
	insert(a[i]);

    /* 要素をキーが小さい順に取り出す */
    for (i = 0; i < n; i++)
	a[i] = delete_min();
}
