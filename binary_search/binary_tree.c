#include <stdio.h>
#include <stdlib.h>

//構造体を作る。これは再帰的に二分木となっている
typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} Node;

//二分木に要素を差し込む
//pNode: 現在注目している要素  insert_data: 差し込む要素
Node *insert(Node *pNode, int insert_data) {
    //末端部にたどり着いた場合
    if (pNode == NULL) {
        Node* new_node = (Node*) malloc(sizeof(Node)); //メモリ確保
        new_node->data = insert_data;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node; //その位置に値を代入して終了
    }
    //差し込む要素が親要素より小さい場合
    if (insert_data < pNode->data) {
        //左側を注目要素として再度計算
        pNode->left = insert(pNode->left, insert_data);
    //差し込む要素が親要素より大きい場合
    } else if (insert_data > pNode->data) {
        //右側を注目要素として再度計算
        pNode->right = insert(pNode->right, insert_data);
    }
    return pNode; //なにも変化しないで終了
}

//２分木の要素を探索する関数
Node *search(Node *pNode, int search_data) {
    if (pNode == NULL || pNode->data == search_data) {
        return pNode; // NULL または その要素を指すポインタを返す
    }
    //結果が確定するまで遷移を続ける
    if (search_data < pNode->data) {
        return search(pNode->left, search_data);
    } else {
        return search(pNode->right, search_data);
    }
}

//２分木のすべての要素を出力する関数
void traverse(Node *root) {
    if (root== NULL) {
        return; //要素が途切れたら終了、ひとつ前の処理に戻り続く
    }
    traverse(root->left);
    printf("%d ", root->data);
    traverse(root->right);
}

int main(void) {
    Node *root = NULL;
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

    printf("Inorder traversal:");
    traverse(root);
    printf("\n");

    int search_data = 7;
    Node *result = search(root, search_data);
    if (result == NULL) {
        printf("%d not found\n", search_data);
    } else {
        printf("%d found\n", result->data);
    }

    return 0;
}