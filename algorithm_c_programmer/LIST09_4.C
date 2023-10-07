/* Page 144 */

/* List 9.4  二分探索木から最小の要素を削除する関数deletemin */


/*    deletemin	 -- 二分探索木から最小の要素を削除する
		  削除した節へのポインタを返す
		    p : 二分探索木へのポインタへのポインタ
			（つまり，*pが木へのポインタとなる）
*/

#include <stdlib.h>				/* @@@@ */
typedef	int	KEY;				/* @@@@ */
typedef struct node {				/* @@@@ */
    KEY data;					/* @@@@ */
    struct node *left, *right;			/* @@@@ */
} NODE;						/* @@@@ */
NODE *root;					/* @@@@ */


NODE  *deletemin(NODE **p)
{
    NODE    *x;

    while ((*p)->left != NULL)
	p = &(*p)->left;
    x = *p;
    *p = (*p)->right;
    return  x;
}
