#include <stdio.h>

struct node {
    struct node *left;
    struct node *right;
    char label;
};

//行きがけ順
void preorder(struct node *root) {
    //木が空ならcontinue
    if (root == NULL) {
        return;
    }
    printf("節%cに立ち寄りました\n", root->label);
    preorder(root->left);
    preorder(root->right);
}

//通り掛け順
void inorder(struct node *root) {
    //部分木が空ならcontinue
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("節%cに立ち寄りました\n", root->label);
    inorder(root->right);
}

//帰りがけ順
void postorder(struct node *root) {
    //木が空ならcontinue
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("節%cに立ち寄りました\n", root->label);
}