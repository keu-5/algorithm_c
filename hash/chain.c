#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 50

typedef int KEY;
typedef char DATA;

// Define a structure for a linked list node
typedef struct cell {
    KEY key;
    DATA data;
    struct cell *next;
} CELL;

CELL *table[BUCKET_SIZE];

void init() {
    for (int i = 0; i < BUCKET_SIZE; i++) {
        table[i] = NULL;
    }
}

int hash(KEY key) {
    return key % BUCKET_SIZE;
}

int keyequal(KEY k1, KEY k2) {
    return k1 == k2;
}

DATA *find(KEY key) {
    int h = hash(key);
    CELL *p = table[h];

    //pになにか入っている場合
    while (p != NULL) {
        if (keyequal(key, p->key)) {
            return &p->data;
        }
        p = p->next;
    }

    //なにも見つからなかった場合
    return NULL;
}

int insert(KEY key, DATA data) {
    if (find(key) != NULL) {
        //キーが既に存在する場合
        return 0;
    }

    int h = hash(key);
    CELL *p = (CELL *)malloc(sizeof(CELL));

    if (p == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(2);
    }
    //循環リスト?
    p->key = key;
    p->data = data;
    p->next = table[h];
    table[h] = p;

    return 1;
}

int delete(KEY key) {
    int h = hash(key);
    CELL *p = table[h];
    CELL *q = NULL;

    while (p != NULL) {
        //バケットがそれだった場合
        if (keyequal(key, p->key)) {
            if (q == NULL) {
                // 初項がそれだった場合
                table[h] = p->next;
            } else {
                q->next = p->next;
            }
            free(p);
            return 1;
        }
        //NOTE: ここから
        q = p;
        p = p->next;
    }

    return 0;
}

int main(void) {
    init();

    for (int i = 0; i < 100; i++) {
        KEY key = i;
        DATA data = (char)(i + 'A'); // You can use any meaningful data here
        insert(key, data);
    }

    for (int i = 0; i < 100; i++) {
        KEY key = i;
        DATA *result = find(key);
        if (result == NULL) {
            fprintf(stderr, "Key %d not found\n", key);
        } else {
            printf("Key %d found with value %c\n", key, *result);
        }
    }

    for (int i = 0; i < 100; i++) {
        KEY key = i;
        int deleted = delete(key);
        if (!deleted) {
            fprintf(stderr, "Key %d not deleted\n", key);
        }
    }

    return 0;
}
