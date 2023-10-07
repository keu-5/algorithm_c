/* Page 18 */

/* List 2.3  üŒ`’Tõ–@‚É‚¨‚¯‚éƒf[ƒ^‚Ì“o˜^ */

struct {						/* @@@@ */
    int	 key;						/* @@@@ */
    int	 data;						/* @@@@ */
} table[100];						/* @@@@ */

int	n;	/* table‚É“o˜^‚³‚ê‚Ä‚¢‚éƒf[ƒ^‚ÌŒÂ” */	/* @@@@ */

add(int key, int data)
{
    if (n >= 100)
	error("—v‘f”‚ª‘½‚·‚¬‚é");
    table[n].key  = key;
    table[n].data = data;
    n++;
}
