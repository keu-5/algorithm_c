#include <stdio.h>
#include <stdlib.h>

typedef int KEY;
typedef struct node {
    KEY data;
    struct node *left, *right;
} NODE;

NODE *root = NULL;

int keyequal(KEY a, KEY b) {
    return a == b;
}

int keylt(KEY a, KEY b) {
    return a < b;
}

//親ノードの次に小さい
NODE *determin(NODE **p) {
    NODE *x;

    while ((*p)->left != NULL) {
        p = &(*p)->left;
    }
    x = *p;
    *p = (*p)->right;
    return x;
}

//小さい順に二分木に格納する
NODE *insert(KEY key) {
    NODE **p, *new;

    p = &root;
    while (*p != NULL) {
        if (keyequal(key, (*p)->data)) {
            //すでにデータが存在していたら
            return NULL;
        } else if (keylt(key, (*p)->data)) {
            //データが存在していないかつ親データより値が小さい
            p = &(*p)->left;
        } else {
            //データが存在していないかつ親データより値が大きい
            p = &(*p)->right;
        }
    }
    if ((new = malloc(sizeof(NODE))) == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    new->left = NULL;
    new->right = NULL;
    new->data = key;
    *p = new;
    return new;
}

NODE *search(KEY key) {
    NODE *p = root;
    while (p != NULL) {
        if (keyequal(key, p->data)) {
            return p;
        } else if (keylt(key, p->data)) {
            p = p->left;
        } else {
            p = p->right;
        }
    }
    return NULL;
}

int delete(KEY key) {
    //**p: 参照ノード **x: 削除ノード
    NODE **p, *x;

    p = &root;
    while (*p != NULL) {
        //目的のデータにたどり着いた場合
        if (keyequal(key, (*p)->data)) {
            x = *p;
            if (x->left == NULL && x->right == NULL) {
                //末端の場合
                *p = NULL;
            } else if (x->left == NULL) {
                //右側が存在していた場合
                *p = x->right;
            } else if (x->right == NULL) {
                //左側が存在していた場合
                *p = x->left;
            } else {
                //どちらも存在していた場合
                //NOTE:ここどうなる？
                *p = determin(&x->right);
                (*p)->right = x->right;
                (*p)->left = x->left;
            }
            free(x);
            return 1;
        } else if (keylt(key, (*p)->data)) {
            p = &(*p)->left;
        } else {
            p = &(*p)->right;
        }
    }
    return 0;
}

//小さい順に出力する
void inorder(NODE *p) {
    if (p == NULL) {
        return;
    } else {
        //通り掛け順
        inorder(p->left);
        printf("%d ", p->data);
        inorder(p->right);
    }
}

int main(void) {
    int select;
    int key;
    NODE *p;

    while (1) {
        puts("どうしますか？");
        puts("1. 追加");
        puts("2. 削除");
        puts("3. 出力");
        puts("4. 終了");
        printf("> ");
        scanf("%d", &select);
        
        switch (select) {
            case 1:
                {
                    puts("挿入する数値を入力してください");
                    printf("整数値:");
                    scanf("%d", &key);
                    if ((p = insert(key)) == NULL) {
                        puts("すでにデータが存在しています");
                    } else {
                        printf("データ%dを追加しました\n", p->data);
                    }
                    break;
                }
            case 2:
                {
                    puts("削除する数値を入力してください");
                    printf("整数値:");
                    scanf("%d", &key);
                    if (delete(key)) {
                        printf("データ%dを削除しました\n", key);
                    } else {
                        puts("データが存在しません");
                    }
                    break;
                }
            case 3:
                {
                    inorder(root);
                    printf("\n");
                    break;
                }
            case 4:
                {
                    exit(0);
                    return 0;
                }
            default:
                {
                    fprintf(stderr, "不正な入力です。\n");
                    exit(1);
                    break;
                }
        }
    }
}