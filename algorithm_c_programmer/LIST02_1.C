/* Page 12 */

/* List 2.1@üŒ`’Tõ–@‚É‚æ‚é’Tõ */

struct {
    int	 key;
    int	 data;
} table[100];

int	n;	/* table‚É“o˜^‚³‚ê‚Ä‚¢‚éƒf[ƒ^‚ÌŒÂ” */

int  search(int key)
{
    int	 i;

    i = 0;
    while (i < n) {
	if (table[i].key == key)
	    return (table[i].data);	/* Œ©‚Â‚©‚Á‚½ */
	i++;
    }
    return -1;				/* Œ©‚Â‚©‚ç‚È‚©‚Á‚½ */
}
