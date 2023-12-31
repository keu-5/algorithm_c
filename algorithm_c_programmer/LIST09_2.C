/* Page 136 */

/* List 9.2  二分探索木に要素を挿入する関数insert */


/*    insert  -- 二分探索木に要素を挿入する
	       挿入した要素が置かれる節へのポインタを返す
	       すでに要素が登録されているのなら，何もしないでNULLを返す
		  key : 挿入するデータ 
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
    while (*p != NULL) {    /* 挿入すべき場所が見つかるまで繰り返す */
	if (keyequal(key, (*p)->data))
	    return  NULL;		    /* すでに登録されている */
	else if (keylt(key, (*p)->data))
	    p = &(*p)->left;		    /* 左部分木に進む */
	else
	    p = &(*p)->right;		    /* 右部分木に進む */
    }
					    /* 挿入される節を作る */
    if ((new = malloc(sizeof(NODE))) == NULL)
	error("out of memory!!");
    new->left  = NULL;
    new->right = NULL;
    new->data  = key;
    *p = new;				    /* 正しい場所に挿入する */
    return  new;
}
