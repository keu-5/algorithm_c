/* Page 146 */

/* List 9.5  ρͺTυΨΜSvfπΈΙ\¦·ιΦinorder */


/*  inorder  -- ρͺTυΨΜSvfπ¬¨εΜΕ\¦·ι */

#include <stdlib.h>				/* @@@@ */
typedef	int	KEY;				/* @@@@ */
typedef struct node {				/* @@@@ */
    KEY data;					/* @@@@ */
    struct node *left, *right;			/* @@@@ */
} NODE;						/* @@@@ */
NODE *root;					/* @@@@ */


inorder(NODE *p)
{
    if (p == NULL)
	return;
    else {
	inorder(p->left);
	printf("%d ", p->data);
	inorder(p->right);
    }
}
