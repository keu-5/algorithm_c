/* Page 16 */

/* List 2.2@“ñ•ª’Tõ–@‚É‚æ‚é’Tõ */

struct {
    int	 key;
    int	 data;
} table[100];

int	n;	/* table‚É“o˜^‚³‚ê‚Ä‚¢‚éƒf[ƒ^‚ÌŒÂ” */

int  binary_search(int key)
{
    int	 low, high, middle;

    low = 0;
    high = n - 1;

    while (low <= high) {
	middle = (low + high) / 2;
	if (key == table[middle].key)
	    return (table[middle].data);      /* Œ©‚Â‚©‚Á‚½ */
	else if (key < table[middle].key)
	    high = middle - 1;
	else /* key > table[middle].key ‚Å‚ ‚é */
	    low = middle + 1;
    }
    return (-1);			      /* Œ©‚Â‚©‚ç‚È‚©‚Á‚½ */
}
