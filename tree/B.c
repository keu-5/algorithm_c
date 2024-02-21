#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 五分木
#define MAX_CHILD 5
#define HALF_CHILD ((MAX_CHILD + 1) - 2)

typedef int KEY;
typedef int DATA;

// NOTE: 葉にデータが入る。テンソルみたいな概念。節がもつ子の最大値はMAX_CHILD。
typedef struct node {
    int nodekind;

    union {
        // 内部節の場合
        struct {
            int _nchilds; //NOTE: 子の数
            struct node* _child[MAX_CHILD]; //NOTE: 子要素
            KEY _low[MAX_CHILD]; //NOTE: 各部分木の一番左をたどってった時の最終的にぶち当たるキー
        } _internal;

        // 葉の場合
        struct {
            KEY _leaf_key; //NOTE: 葉の持つキーの値
            DATA _your_data; //NOTE: オプショナル
        } _leaf;
    } _u;
} NODE;

//NOTE: nodeに用いる節のタグ(内部 or 葉)
#define INTERNAL 1
#define LEAF 2

//NOTE: 内部参照のための定数
#define nchilds _u._internal._nchilds
#define child _u._internal._child
#define low _u._internal._low

//NOTE: 葉参照のための定数
#define leaf_key _u._leaf._leaf_key
#define your_data _u._leaf._your_data

NODE* root = NULL;

/**-------------------------------------------------------------------------------**/

error(char* s) {
    fprintf(stderr, "%d", s);
    exit(1);
}

//NOTE: 構造体作成関数
NODE* alloc_node(void) {
    NODE* p;

    if (p = malloc(sizeof(NODE)) == NULL) {
        error("メモリを使い果たしてしまった");
    }

    return p;
}


//NOTE: 2つのキーが等しいか確認する関数
int keyequal(KEY a, KEY b) {
    return a == b;
}

//NOTE: 2つのキーが小さい順かどうか確認する関数
int keylt(KEY a, KEY b) {
    return a < b;
}

/**-------------------------------------------------------------------------------**/

//NOTE: 節pにおいて、目的のキーを持つデータはどの部分木にあるか探索
//BUG: なんでこうなるのかわからん
int locate_subtree(NODE* p, KEY key) {
    int i;

    for (i = p->nchilds -1; i > 0; i--) {
        if (key >= p->low[i]) { // BUG: ここ不等号逆じゃないの?
            return i;
        }
    }

    return 0;
}

//NOTE: キーがどこにあるか探す。
//BUG: locate_subtreeのせいでわからん
NODE* search(KEY key) {
    NODE* p;
    int i;

    if (root == NULL) {
        //木が空の場合
        return NULL;
    } else {
        //内部節をたどる
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

/**-------------------------------------------------------------------------------**/

/*
 * 1. 節*pnodeに対して、キーkeyを持つ要素を挿入
 * 2. 挿入した要素が置かれている節へのポインタを返す
 * 3. 新しい節を作った場合、それを*newnodeにセットして*newnodeの指す部分木中の最小要素を*lowestに返す
 * 4. 新しい節を作らなかった場合、*newnodeにはNULLを返す
 */

NODE* insert_aux(NODE* *pnode, KEY key, NODE* *newnode, KEY* lowest) {
    NODE* node;

    *newnode = NULL;
    node = *pnode;

    if (node->nodekind == LEAF) {
    //NOTE: 指定の節が葉の場合
        if (keyequal(node->leaf_key, key)) {
            //すでに登録済みの場合
            return NULL;
        } else {
            NODE* new;

            new = alloc_node();
            new->nodekind = LEAF;
            new->leaf_key = key;

            if (key < node->leaf_key) {
            //NOTE: 新しい葉newのほうがpnodeよりも小さい場合、これらを入れ替える
                *pnode = new;
                //BUG: なぜ最小要素に指定要素を設定するの?
                *lowest = node->leaf_key;
                *newnode = node;
            } else {
            //BUG: newがpnodeよりも大きい場合、最小要素をkeyにする？？
                *lowest = key;
                *newnode = new;
            }

            return new;
        }
    } else {
    //NOTE: 指定の節が内部節の場合
        int pos;  //何番目の部分木に挿入するか？

        //NOTE: 再帰呼び出しに使うためのパラメータ。多分挿入時要素をずらしたときに使う
        NODE* xnode;  //パラメータnewnode
        KEY xlow;  //パラメータlowest
        NODE* retv; //関数値
        int i, j;

        // 順番通りに挿入するため
        pos = locate_subtree(node, key);
        //BUG: これなんのためにするの？
        retv = insert_aux(&(node->child[pos]), key, &xnode, &xlow);

        //NOTE: 分割が行われていない場合、そのままreturn。再帰の過程の中でxlowが設定される
        if (xnode == NULL) {
            return retv;
        }

        if (node->nchilds < MAX_CHILD) {
        //NOTE: 節nodeに追加の余地がある場合
            //要素をずらすことで指定のnodeに挿入する
            for (i = node->nchilds - 1; i > pos; i--) {
                node->child[i+1] = node->child[i];
                node->low[i+1] = node->low[i];
            }

            // 実際に挿入
            node->child[pos+1] = xnode;
            node->low[pos+1] = xlow;
            node->nchilds++;

            return retv;
        } else {
        //NOTE: nodeに追加の余地がない場合, 節を分割する
            NODE* new;

            new = alloc_node();
            new->nodekind = INTERNAL;

            if (pos < HALF_CHILD -1) {
            //NOTE: posが節の半分より小さい場合
                // HALF_CHILDからMAX_CHILDまでの部分木を別の節に移す
                for (i = HALF_CHILD - 1, j = 0; i < MAX_CHILD; i++, j++) {
                    new->child[j] = node->child[i];
                    new->low[j] = node->low[i];
                }

                for (i = HALF_CHILD - 2; i > pos; i--) {
                    node->child[i+1] = node->child[i];
                    node->low[i+1] = node->low[i];
                }

                // 残りの部分木の中で適切な位置に挿入する
                node->child[pos+1] = xnode;
                node->low[pos+1] = xlow;
            } else {
            //NOTE: posが節の半分より大きい場合
                j = MAX_CHILD - HALF_CHILD;

                // HALF_CHILDからMAX_CHILDまでの部分木を別の節に移すと同時に挿入もする
                for (i = MAX_CHILD - 1; i >= HALF_CHILD; i--) {
                    if (i == pos) {
                        new->child[j] = xnode;
                        new->low[j--] = xlow;
                    }

                    new->child[j] = node->child[i];
                    new->low[j--] = node->low[i];
                }

                //BUG: これなに？
                if (pos < HALF_CHILD) {
                    new->child[0] = xnode;
                    new->low[0] = xlow;
                }

                //NOTE: 子の数を変更する
                node->nchilds = HALF_CHILD;
                new->nchilds = (MAX_CHILD + 1) - HALF_CHILD;

                //NOTE: 分割した場合の節と最小値をそれぞれ返す
                *newnode = new;
                *lowest = new->low[0];

                return retv;
            }
        }
    }

}

/**-------------------------------------------------------------------------------**/

/*
 * 1. B木に挿入する
 * 2. 挿入した要素が置かれている節へのポインタを返す
 * 3. 既に要素が登録されているなら、何もしないでNULLを返す
*/

NODE* insert(KEY key) {
    if (root == NULL) {
    // 木が空の場合、葉を作ってそれを返す
        root = alloc_node();
        root->nodekind = LEAF;
        root->leaf_key = key;

        return root;
    } else {
    // 木が空でない場合、insert_auxをよび出して要素の挿入を行う
        NODE *retv, *new, *newnode;
        KEY lowest;

        retv = insert_aux(&root, key, &newnode, &lowest);

        // NOTE: 分割が行われた場合、木の高さを1段高くする
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

/**-------------------------------------------------------------------------------**/

/*
 * 1. 節pのx番目とx+1番目の部分木とを再編成する
 * 2. 合併が必要な場合、すべての要素をx番目の部分木に集めて、1を返す。
 * 3. そうでなければ0を返す
*/

int marge_nodes(NODE *p, int x) {
    NODE *a, *b; //x, x+1番目の部分木
    int an, bn; //部分木a, bの子の数
    int i;

    a = p->child[x];
    b = p->child[x+1];
    b->low[0] = p->low[x+1];
    an = a->nchilds;
    bn = b->nchilds;

    if (an + bn <= MAX_CHILD) {
    //NOTE: 簡単に合併できる場合
        //NOTE: bの子をすべてaへ移動する
        for (i = 0; i < bn; i++) {
            a->child[i + an] = b->child[i];
            a->low[i + an] = b->low[i];
        }

        a->nchilds += bn;
        free(b);

        return 1;
    } else {
    //NOTE: 簡単に合併できない場合
        int n, move;

        n = (an + bn) / 2;

        if (an > n) {
        //NOTE: aの子の余剰をbへ移動する
            move = an -n;

            //NOTE: bの要素をずらす
            for (i = bn - 1; i >= 0; i--) {
                b->child[i+move] = b->child[i];
                b->low[i+move] = b->low[i];
            }

            //NOTE: moveに指定されたaの要素をbへ移動する
            for (i = 0; i < move; i++) {
                b->child[i] = a->child[i + n];
                b->low[i] = a->low[i + n];
            }
        } else {
        //NOTE: bの子の余剰をaへ移動する
            move = n - an;

            for (i = 0; i < move; i++) {
                a->child[i + an] = b->child[i];
                a->low[i + an] = b->low[i];
            }

            for (i = 0; i < bn - move; i++) {
                b->child[i] = b->child[i + move];
                b->low[i] = b->low[i + move];
            }
        }

        a->nchilds = n;
        b->nchilds = an + bn -n;

        p->low[x + 1] = b->low[0];

        return 0;
    }
}

/**-------------------------------------------------------------------------------**/
