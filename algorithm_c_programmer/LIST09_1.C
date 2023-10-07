/* Page 134 */

/* List 9.1  二分探索木を探索する関数search */


/*     search  -- 二分探索木を探索する
		節へのポインタを返す
		見つからなければ，NULLを返す
		   key : 探索するキー 
*/

#include <stdlib.h>				/* @@@@ */
typedef int	KEY;				/* @@@@ */
typedef struct node {				/* @@@@ */
    KEY data;					/* @@@@ */
    struct node *left, *right;			/* @@@@ */
} NODE;						/* @@@@ */
NODE *root;					/* @@@@ */


NODE  *search(KEY key)
{
    NODE    *p;				    /* 現在注目している節 */

    p = root;				    /* まず根に注目する */
    while (p != NULL) {
	if (keyequal(key, p->data))	    /* 見つかった */
	    return  p;
	else if (keylt(key, p->data))	    /* キーのほうが小さければ  */
	    p = p->left;		    /* 左部分木に進む　	       */
	else				    /* キーのほうが大きければ　*/
	    p = p->right;		    /* 右部分木に進む	     　*/
    }
    return  NULL;			    /* 探索に失敗した */
}
