/* Page 146 */

/* List 9.5  二分探索木の全要素を昇順に表示する関数inorder */


/*  inorder  -- 二分探索木の全要素を小→大の順で表示する */

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
