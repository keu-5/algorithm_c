/* Page 110 */

/* List 8.1  文字列のためのハッシュ関数 */

int hash(char *s)
{
    int i = 0;

    while (*s)
	i += *s++;
    return i % 100;
}
