/* Page 136 */

/* List 9.2  “ñ•ª’Tõ–Ø‚É—v‘f‚ğ‘}“ü‚·‚éŠÖ”insert */


/*    insert  -- “ñ•ª’Tõ–Ø‚É—v‘f‚ğ‘}“ü‚·‚é
	       ‘}“ü‚µ‚½—v‘f‚ª’u‚©‚ê‚éß‚Ö‚Ìƒ|ƒCƒ“ƒ^‚ğ•Ô‚·
	       ‚·‚Å‚É—v‘f‚ª“o˜^‚³‚ê‚Ä‚¢‚é‚Ì‚È‚çC‰½‚à‚µ‚È‚¢‚ÅNULL‚ğ•Ô‚·
		  key : ‘}“ü‚·‚éƒf[ƒ^ 
*/

#include <stdlib.h>				/* @@@@ */
typedef	int	KEY;				/* @@@@ */
typedef struct node {				/* @@@@ */
    KEY data;					/* @@@@ */
    struct node *left, *right;			/* @@@@ */
} NODE;						/* @@@@ */
NODE *root;					/* @@@@ */


NODE   *insert(KEY key)
{
    NODE    **p, *new;

    p = &root;
    while (*p != NULL) {    /* ‘}“ü‚·‚×‚«êŠ‚ªŒ©‚Â‚©‚é‚Ü‚ÅŒJ‚è•Ô‚· */
	if (keyequal(key, (*p)->data))
	    return  NULL;		    /* ‚·‚Å‚É“o˜^‚³‚ê‚Ä‚¢‚é */
	else if (keylt(key, (*p)->data))
	    p = &(*p)->left;		    /* ¶•”•ª–Ø‚Éi‚Ş */
	else
	    p = &(*p)->right;		    /* ‰E•”•ª–Ø‚Éi‚Ş */
    }
					    /* ‘}“ü‚³‚ê‚éß‚ğì‚é */
    if ((new = malloc(sizeof(NODE))) == NULL)
	error("out of memory!!");
    new->left  = NULL;
    new->right = NULL;
    new->data  = key;
    *p = new;				    /* ³‚µ‚¢êŠ‚É‘}“ü‚·‚é */
    return  new;
}
