//BUG: 値が認識されない
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//5分木
#define MAX_CHILD 5
#define HALF_CHILD ((MAX_CHILD + 1) / 2)

typedef int KEY;
typedef int DATA;

typedef struct node {
    //節の種類
    int nodekind;
    //共用体 (同じメモリを違う型同士で共有する)
    union {
        //内部節の場合
        struct {
            //この節がもっている子の数
            int _nchilds;
            //部分木
            struct node *_child[MAX_CHILD];
            //各部分木の最小の要素
            KEY _low[MAX_CHILD];
        } _internal;
        //葉の場合
        struct {
            //葉が持っているキーの値
            KEY _leaf_key;
            //葉に格納するデータ
            DATA _your_data;
        } _leaf;
    } _u;
} NODE;

//葉の種類を表す定数 (メンバnodekindにセットする)
#define INTERNAL 1
#define LEAF 2

//内部節のメンバを参照するためのマクロ定義
#define nchilds _u._internal._nchilds
#define child _u._internal._child
#define low _u._internal._low

//葉のメンバを参照するためのマクロ定義
#define leaf_key _u._leaf._leaf_key
#define your_data _u._leaf._your_data

NODE *root = NULL;

void error(char *s) {
    fprintf(stderr, "%s\n", s);
    exit(1);
}

//構造体NODE型をメモリに確保する関数
NODE *alloc_node(void) {
    NODE *p;

    if ((p = malloc(sizeof(NODE))) == NULL) {
        error("out of memory");
    }
    return p;
}

int keyequal(KEY a, KEY b) {
    return a == b;
}

int keylt(KEY a, KEY b) {
    return a < b;
}

//節pにおいて、キーkeyをもつデータは何番目の部分木に入るかを返す
int locate_subtree(NODE *p, KEY key) {
    int i;

    for (i = p->nodekind - 1; i > 0; i--) {
        if (key >= p->low[i]) {
            return i;
        }
    }
    return 0;
}

//BUG ここがバグってる？
NODE *search(KEY key) {
    NODE *p;
    int i;

    if (root == NULL) {
        return NULL;
    } else {
        p = root;
        while (p->nodekind == INTERNAL) {
            i = locate_subtree(p, key);
            p = p->child[i];
        }
        if (key == p->leaf_key) {
            return p;
        } else {
            return NULL;
        }
    }
}

NODE *insert_aux(NODE **pnode, KEY key, NODE **newnode, KEY *lowest) {
    NODE *node;

    *newnode = NULL;
    node = *pnode;
    if (node->nodekind == LEAF) {
        if (keyequal(node->leaf_key, key)) {
            return NULL;
        } else {
            NODE *new;

            new = alloc_node();
            new->nodekind = LEAF;
            new->leaf_key = key;
            if (key < node->leaf_key) {
                *pnode = new;
                *lowest = node->leaf_key;
                *newnode = node;
            } else {
                *lowest = key;
                *newnode = new;
            }
            return new;
        }
    } else {
        int pos;
        NODE *xnode;
        KEY xlow;
        NODE *retv;
        int i, j;

        pos = locate_subtree(node, key);
        retv = insert_aux(&(node->child[pos]), key, &xnode, &xlow);
        if (xnode == NULL) {
            return retv;
        }
        if (node->nchilds < MAX_CHILD) {
            for (i = node->nchilds -1; i > pos; i--) {
                node->child[i + 1] = node->child[i];
                node->low[i + 1] = node->low[i];
            }
            node->child[pos + 1] = xnode;
            node->low[pos + 1] = xlow;
            node->nchilds++;
            return retv;
        } else {
            NODE *new;

            new = alloc_node();
            new->nodekind = INTERNAL;
            if (pos < HALF_CHILD - 1) {
                for (i = HALF_CHILD - 1, j = 0; i < MAX_CHILD; i++, j++) {
                    new->child[j] = node->child[i];
                    new->low[j] = node->low[i];
                }
                for (i = HALF_CHILD - 2; i > pos; i--) {
                    node->child[i + 1] = node->child[i];
                    node->low[i + 1] = node->low[i];
                }
                node->child[pos + 1] = xnode;
                node->low[pos + 1] = xlow;
            } else {
                j = MAX_CHILD - HALF_CHILD;
                for (i = MAX_CHILD - 1; i >= HALF_CHILD; i--) {
                    if (i == pos) {
                        new->child[j] = xnode;
                        new->low[j--] = xlow;
                    }
                    new->child[j] = node->child[i];
                    new->low[j--] = node->low[i];
                }
                if (pos < HALF_CHILD) {
                    new->child[0] = xnode;
                    new->low[0] = xlow;
                }
            }
            node->nchilds = HALF_CHILD;
            new->nchilds = (MAX_CHILD + 1) - HALF_CHILD;
            *newnode = new;
            *lowest = node->low[0];
            return retv;
        }
    }
}

NODE *insert(KEY key) {
    if (root == NULL) {
        root = alloc_node();
        root->nodekind = LEAF;
        root->leaf_key = key;
        return root;
    } else {
        NODE *retv, *new, *newnode;
        KEY lowest;

        retv = insert_aux(&root, key, &newnode, &lowest);
        if (newnode != NULL) {
            new = alloc_node();
            new->nodekind = INTERNAL;
            new->nchilds = 2;
            new->child[0] = root;
            new->child[1] = newnode;
            new->low[1] = lowest;
            root = new;
        }
        return retv;
    }
}

int marge_nodes(NODE *p, int x) {
    NODE *a, *b;
    int an, bn;
    int i;

    a = p->child[x];
    b = p->child[x + 1];
    b->low[0] = p->low[x + 1];
    an = a->nchilds;
    bn = b->nchilds;
    if (an + bn <= MAX_CHILD) {
        for (i = 0; i < bn; i++) {
            a->child[i + an] = b->child[i];
            a->low[i + an] = b->low[i];
        }
        a->nchilds += bn;
        free(b);
        return 1;
    } else {
        int n, move;

        n = (an + bn) / 2;
        if (an > n) {
            move = an - n;
            for (i = bn - 1; i >= 0; i--) {
                b->child[i + move] = b->child[i];
                b->low[i + move] = b->low[i];
            }
            for (i = 0; i < move; i++) {
                b->child[1] = a->child[i + n];
                b->low[1] = a->low[i + n];
            }
        } else {
            move = n - an;
            for (i = 0; i < move; i++) {
                a->child[i + an] = a->child[i];
                a->low[i + an] = a->low[i];
            }
            for (i = 0; i < bn -move; i++) {
                b->child[i] = b->child[i + move];
                b->low[i] = b->low[i + move];
            }
        }
        a->nchilds = n;
        b->nchilds = an + bn - n;
        p->low[x + 1] = b->low[0];
        return 0;
    }
}

#define OK 1
#define REMOVED 2
#define NEED_REORG 3

int delete_aux(NODE *node, KEY key, int *result) {
    *result = OK;
    if (node->nodekind == LEAF) {
        if (keyequal(node->leaf_key, key)) {
            *result = REMOVED;
            free(node);
            return 1;
        } else {
            return 0;
        }
    } else {
        int pos;
        int condition;
        int retv;
        int sub;
        int joined;
        int i;

        pos = locate_subtree(node, key);
        retv = delete_aux(node->child[pos], key, &condition);
        if (condition == OK) {
            return retv;
        }
        if (condition == NEED_REORG) {
            sub = (pos == 0) ? 0 : pos - 1;
            joined = marge_nodes(node, sub);
            if (joined) {
                pos = sub + 1;
            }
        }
        if (condition == REMOVED || joined) {
            for (i = pos; i < node->nchilds - 1; i++) {
                node->child[i] = node->child[i + 1];
                node->low[i] = node->low[i + 1];
            }
            if (--node->nchilds < HALF_CHILD) {
                *result = NEED_REORG;
            }
        }
        return retv;
    }
}

int delete(KEY key) {
    int retv, result;
    NODE *p;

    if (root == NULL) {
        return 0;
    } else {
        retv = delete_aux(root, key, &result);
        if (result == NEED_REORG && root->nchilds == 1) {
            p = root;
            root = p->child[0];
            free(p);
        }
        return retv;
    }
}

void printtree(NODE *p) {
    int i;

    if (p->nodekind == LEAF) {
        printf("%p leaf val = %d\n", (void *)p, p->leaf_key);
    } else {
        printf("%p %02d [%p] %d[%p] %d[%p] %d[%p] %d[%p]\n", (void *)p, p->nchilds, (void *)(p->child[0]), p->low[1], (void *)(p->child[1]), p->low[2], (void *)(p->child[2]), p->low[3], (void *)(p->child[3]), p->low[4], (void *)(p->child[4]));
        for (i = 0; i < p->nchilds; i++) {
            printtree(p->child[i]);
        }
    }
}

int main(void) {
    //static int data[] = {10, 20, 30, 40, 50};
    static int data[] = {13, 5, 2, 7, 6, 21, 15};
    int i, x;
    char str[100];

    for (i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
        insert(data[i]);
    }
    printf("+n : nを挿入する\n-n : nを削除する\nn : nを探索する\n");
    printtree(root);
    printf("\n>");

    while (fgets(str, sizeof(str), stdin) != NULL) {
        x = abs(atoi(str));
        switch (str[0]) {
            case '+':
                if (insert(x) != NULL) {
                    printf("%d inserted.\n", x);
                } else {
                    printf("%d not inserted.\n", x);
                }
                break;
            case '-':
                if (delete(x)) {
                    printf("%d deleted.\n", x);
                } else {
                    printf("%d not deleted.\n", x);
                }
                break;
            default:
                if (search(x) != NULL) {
                    printf("%d found.\n", x);
                } else {
                    printf("%d not found.\n", x);
                }
                break;
        }
        printtree(root);
        printf("\n>");
    }
}