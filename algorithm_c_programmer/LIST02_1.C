/* Page 12 */

/* List 2.1　線形探索法による探索 */

struct {
    int	 key;
    int	 data;
} table[100];

int	n;	/* tableに登録されているデータの個数 */

int  search(int key)
{
    int	 i;

    i = 0;
    while (i < n) {
	if (table[i].key == key)
	    return (table[i].data);	/* 見つかった */
	i++;
    }
    return -1;				/* 見つからなかった */
}
