/* List 5.3  関数insert */

#include <stdlib.h>		/* @@@@ */


struct CELL {
    struct CELL *next;
    int		value;
} header;


insert(int a)
{
    struct CELL *p, *q, *new;

/* 挿入すべき場所を探す */
    p = header.next;
    q = &header;
    while (p != NULL && a > p->value) {
	q = p;
	p = p->next;
    }

/* セルを挿入する */
    if ((new = malloc(sizeof(struct CELL))) == NULL)
	fatal_error("メモリが足りません");
    new->next = p;
    new->value = a;
    q->next = new;
}
