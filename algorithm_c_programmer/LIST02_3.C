/* Page 18 */

/* List 2.3  線形探索法におけるデータの登録 */

struct {						/* @@@@ */
    int	 key;						/* @@@@ */
    int	 data;						/* @@@@ */
} table[100];						/* @@@@ */

int	n;	/* tableに登録されているデータの個数 */	/* @@@@ */

add(int key, int data)
{
    if (n >= 100)
	error("要素数が多すぎる");
    table[n].key  = key;
    table[n].data = data;
    n++;
}
