#include <stdio.h>

struct {
    int key;
    int data;
} table[100];

int n = 0;

void add(int key, int data) {
    table[n].key = key;
    table[n].data = data;
    n++;
}

int search(int key) {
    int i;

    i = 0;
    while (i < n) {
        if (table[i].key == key) {
            return table[i].data;
        }
        i++;
    }
    return -1;
}

int main(void) {
    add(1, 10);
    add(5, 423);
    add(10, 100);
    add(13, 2);
    add(15, 3);
    add(75, 333);
    add(324, 534);
    add(66, 23);
    add(65, 888);
    add(100, 1000);
    add(8, 2);

    int search_num = 324;
    int result = search(search_num);

    if (result == -1) {
        printf("Not found\n");
    } else {
        printf("Found 324: %d\n", result);
    }

    return 0;
}