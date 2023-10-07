/* Page 141 */

/* List 9.3  二分探索木から要素を削除する関数delete */


/*    delete  -- 二分探索木から要素を削除する
	       削除に成功すれば1, 要素が存在しなければ0を返す
		    key : 削除するデータ 
*/

#include <stdlib.h>				/* @@@@ */
typedef	int	KEY;				/* @@@@ */
typedef struct node {				/* @@@@ */
    KEY data;					/* @@@@ */
    struct node *left, *right;			/* @@@@ */
} NODE;						/* @@@@ */
NODE *root;					/* @@@@ */
NODE *deletemin(NODE **p);			/* @@@@ */


int delete(KEY key)
{
    NODE    **p, *x;

    p = &root;
    while (*p != NULL) {			    /* 削除対象を探す */
	if (keyequal(key, (*p)->data)) {	    /* 見つかった */
	    x = *p;
	    if (x->left == NULL && x->right == NULL) /* 葉である */
		*p = NULL;
	    else if (x->left == NULL)		    /* 右の子のみをもつ */
		*p = x->right;
	    else if (x->right == NULL)		    /* 左の子のみをもつ */
		*p = x->left;
	    else {				    /* 左右２つの子をもつ */
		*p = deletemin(&x->right);	    /* ……(1) */
		(*p)->right = x->right;		    /* ……(2) */
		(*p)->left = x->left;		    /* ……(3) */
	    }
	    free(x);
	    return  1;
	} else if (keylt(key, (*p)->data))	    /* 左部分木へ進む */
	    p = &(*p)->left;
	else					    /* 右部分木へ進む */
	    p = &(*p)->right;
    }
    return  0;			    /* 削除対象が見つからなかった */
}
