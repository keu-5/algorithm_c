#include <stdio.h>
#include <stdlib.h>

typedef int KEY;
typedef char DATA;

#define EMPTY (KEY) 0
#define DELETED (KEY) 1
#define BUCKET_SIZE 70

typedef struct bucket {
    KEY key;
    DATA data;
} BUCKET;

BUCKET table[BUCKET_SIZE];

int hash(KEY key) {
    return key % BUCKET_SIZE;
}

//衝突が発生した際に別のバケットに入れるために前回のハッシュ値を用いて再ハッシュを行う
int reflesh(int h) {
    return (h + 1) % BUCKET_SIZE;
}

int keyequal(KEY k1, KEY k2) {
    return k1 == k2;
}

void init() {
    int i;

    for (i = 0; i < BUCKET_SIZE; i++) {
        table[i].key = EMPTY;
    }
}

DATA *find(KEY key) {
    int h, count;
    KEY k;

    count = 0;
    h = hash(key);

    while ((k = table[h].key) != EMPTY) {
        if (k != DELETED && keyequal(key, k)) {
            return &table[h].data;
        }
        //バケットサイズを超えてしまったら終了
        if (++count >= BUCKET_SIZE) {
            return NULL;
        }
        //再ハッシュ
        h = reflesh(h);
    }
    return NULL;
}

//成功したら1,失敗したら0を返す
int insert(KEY key, DATA *data) {
    int h, count;
    KEY k;

    count = 0;
    h = hash(key);

    //バケットに値が存在している場合
    while ((k = table[h].key) != EMPTY && k != DELETED) {
        //完全にキーが一致している場合0を返す
        if (keyequal(key, k)) {
            return 0;
        }
        //バケットサイズを超えてしまったら終了
        if (++count > BUCKET_SIZE) {
            fprintf(stderr, "hash table overflow\n");
            exit(1);
        }
        //再ハッシュ
        h = reflesh(h);
    }
    table[h].key = key;
    table[h].data = *data;
    return 1;
}

//成功したら1,失敗したら0を返す
int delete(KEY key) {
    int h, count;
    KEY k;

    count = 0;
    h = hash(key);

    while ((k = table[h].key) != EMPTY) {
        if (k != DELETED && keyequal(key, k)) {
            table[h].key = DELETED;
            return 1;
        }
        if (++count > BUCKET_SIZE) {
            return 0;
        }
        h = reflesh(h);
    }
    return 0;
}

int main(void) {
    int select;
    KEY key;
    DATA data;

    while(1) {
        puts("操作を選んでください");
        puts("1.insert");
        puts("2.delete");
        puts("3.find");
        puts("4.init");
        puts("5.exit");
        scanf("%d", &select);

        switch (select) {
            case 1:
                puts("keyを入力してください");
                scanf("%d", &key);
                puts("dataを入力してください");
                scanf("%s", &data);

                if (insert(key, &data) == 1) {
                    puts("insert success");
                } else {
                    puts("insert fail");
                }
                break;
            case 2:
                puts("keyを入力してください");
                scanf("%d", &key);
                if (delete(key) == 1) {
                    puts("delete success");
                } else {
                    puts("delete fail");
                }
                break;
            case 3:
                puts("keyを入力してください");
                scanf("%d", &key);
                DATA *data = find(key);

                if (data == NULL) {
                    puts("not found");
                } else {
                    printf("data = %s\n", data);
                }
                break;
            case 4:
                init();
                puts("init success");
                break;
            case 5:
                exit(0);
                break;
            default:
                fprintf(stderr, "invalid select\n");
                exit(1);
                break;
        }
    }
}