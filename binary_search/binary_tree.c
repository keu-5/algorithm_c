#include <stdio.h>

//構造体を作る。これは再帰的に二分木となっている
typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} Node;

//二分木に要素を差し込む
//pNode: 現在注目している要素  insert_data: 差し込む要素
Node* insert(Node* pNode, int insert_data) {
    //初期状態
    if (pNode == NULL) {
        Node* new_node = (Node*) malloc(sizeof(Node));
        new_node->data = insert_data;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }
    if (insert_data < pNode->data) {
        pNode->left = insert(pNode->left, insert_data);
    } else if (insert_data > pNode->data) {
        pNode->right = insert(pNode->right, insert_data);
    } else {
        return pNode;
    }
}

//NOTE: ここから