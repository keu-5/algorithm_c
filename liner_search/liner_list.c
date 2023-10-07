#include <stdio.h>
#include <stdlib.h>

//線形リストを作る(複数のデータをポインタでつなげる)

typedef struct list {
    int date; //データ
    struct list* next; //次の要素へのポインタ
}list;

//構造体が入る予定の場所へのポインタを返す関数
list* cre(void) {
    list* A;
    A = (list*)malloc(sizeof(list)); //自動でサイズを調べ、メモリを確保

    return A;
}

//要素を追加する関数
void insert(list* head) {
    list* new;
    new = cre();
    list* p = head;
    int k, l; //k:挿入する値、l:入れたい位置

    printf("挿入する値を入力してください:");
    scanf("%d", &k);
    printf("何番目の後に挿入しますか(先頭の場合0)");
    scanf("%d", &l);

    for (int i = 0; i < l; i++) {
        p = p->next;
    }
    new->date = k; //newの指定するデータをkにする
    new->next = p->next; //newの指定するポインタを元のpの指定先にする
    p->next = new; //元のpの指定ポインタをnewに指定する
}

//要素を削除する関数
//NOTE:ここから
void delete(list* head) {
    list* p = head;
    int l;

    printf("何番目の要素を削除しますか(先頭の場合0)");
    scanf("%d", &l);

    for (int i = 0; i < l; i++) {
        p = p->next;
    }
    list* q = p->next;
    q = p->next->next;
    p->next = q;
}

void show(list* head) {
    list* p;

    for (p=head->next; p!=NULL; p=p->next) {
        printf("%d\n", p->date);
    }
    printf("~~~~~~~\n");
}

int main(int argc, const char* argv[]) {
    list A, B, C;
    list dummy;
    list* head;

    head = &dummy;
    dummy.next =&A;
    A.next = &B;
    B.next = &C;
    C.next =NULL;

    A.date = 1;
    B.date = 3;
    C.date = 9;
    show(head);
    insert(head);
    show(head);
    delete(head);
    show(head);

    return 0;
}