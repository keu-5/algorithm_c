/* List 5.3  ŠÖ”insert */

#include <stdlib.h>		/* @@@@ */


struct CELL {
    struct CELL *next;
    int		value;
} header;


insert(int a)
{
    struct CELL *p, *q, *new;

/* ‘}“ü‚·‚×‚«êŠ‚ğ’T‚· */
    p = header.next;
    q = &header;
    while (p != NULL && a > p->value) {
	q = p;
	p = p->next;
    }

/* ƒZƒ‹‚ğ‘}“ü‚·‚é */
    if ((new = malloc(sizeof(struct CELL))) == NULL)
	fatal_error("ƒƒ‚ƒŠ‚ª‘«‚è‚Ü‚¹‚ñ");
    new->next = p;
    new->value = a;
    q->next = new;
}
