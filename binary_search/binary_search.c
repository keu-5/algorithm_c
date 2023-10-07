#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//２分木の要素を定義
typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} Node;

//２分木に要素を追加する関数
Node* insert(Node* pNode, int insert_data) {
    //現在注目している要素が存在するかを判定する
    //最初に要素を挿入するとき
    if (pNode == NULL) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = insert_data;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }
    //追加する要素が挿入されるべき位置までポインタが移動したとき
    if (insert_data < pNode->data) {
        //再帰的に処理
        pNode->left = insert(pNode->left, insert_data);
    } else if (insert_data > pNode->data) {
        //再帰的に処理
        pNode->right = insert(pNode->right, insert_data);
    }
    return pNode;
}

//二分木の要素を探索する関数
Node* search(Node* pNode, int search_data) {
    //要素が見つかった場合と見つからなかった場合
    if (pNode == NULL || pNode->data == search_data) {
        return pNode;
    }
    //再帰的に探索
    if (search_data < pNode->data) {
        return search(pNode->left, search_data);//左を探索
    } else {
        return search(pNode->right, search_data);//右を探索
    }
}

//二分探索木のすべての要素を出力する関数
void traverse(Node* root) {
    if (root == NULL) {
        return;
    }
    traverse(root->left);
    printf("%d ", root->data);
    traverse(root->right);
}

int main(void) {
    Node* root = NULL;
    root = insert(root, 6);
    root = insert(root, 8);
    root = insert(root, 9);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 4);
    root = insert(root, 1);
    root = insert(root, 0);
    root = insert(root, 2);
    root = insert(root, 5);

    printf("Inoder traversal:");
    traverse(root);
    printf("\n");

    int search_data = 7;
    Node* result = search(root, search_data);
    if (result == NULL) {
        printf("%d is not found\n", search_data);
    } else {
        printf("%d is found\n", search_data);
    }
}