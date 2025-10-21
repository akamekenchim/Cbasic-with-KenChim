#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node{
    int element;
    struct Node *left;
    struct Node *right;
}Takina;
int sum = 0;
Takina *root = NULL;
Takina *makeRoot(int e){
    Takina *t = (Takina *)malloc(sizeof(Takina));
    t->element = e;
    t->left = NULL;
    t->right = NULL;
    return t;
}
int check(Takina *root){
    if(root == NULL) return 1;
    if(root->left == NULL && root->right == NULL) return 1;
    if(((root->left != NULL) && (root->left->element > root->element)) ||
   ((root->right != NULL) && (root->right->element < root->element)))
    return 0;

    else{
        return check(root->left) && check(root->right);
    }
}
Takina *makeNew(int e){
    Takina *t = (Takina *)malloc(sizeof(Takina));
    t->element = e;
    t->left = NULL;
    t->right = NULL;
    return t;
}
Takina *find(Takina *root, int e){
    if(root == NULL) return NULL;
    if(root->element == e) return root;
    Takina *t = find(root->left, e);
    if(t != NULL) return t;
    else return find(root->right, e);
}
Takina *addLeft(Takina *root, int u, int v){
    if(root == NULL) return makeNew(u);
    Takina *t = find(root, v);
    if(t == NULL || t->left != NULL) return root;
    else{
        t->left = makeNew(u);
        return root;
    }
}
Takina *addRight(Takina *root, int u, int v){
    if(root == NULL) return makeNew(u);
    Takina *t = find(root, v);
    if(t == NULL || t->right != NULL) return root;
    else{
        t->right = makeNew(u);
        return root;
    }
}
void PreOrder(Takina *root){
    if(root == NULL) return;
    printf("%d ", root->element);
    PreOrder(root->left);
    PreOrder(root->right);
}
void InOrder(Takina *root){
    if(root == NULL) return;
    InOrder(root->left);
    printf("%d ", root->element);
    InOrder(root->right);
}
void PostOrder(Takina *root){
    if(root == NULL) return;
    PostOrder(root->left);
    PostOrder(root->right);
    printf("%d ", root->element);
}
void FreeAll(Takina *root){
    if(root == NULL) return;
    FreeAll(root->left);
    FreeAll(root->right);
    free(root);
}
int main(){
    while(1){
        char cmd[20];
        scanf("%s%*c", cmd);
        if(strcmp(cmd, "*")==0) break;
        if(strcmp(cmd, "MakeRoot")==0){
            int airi;
            scanf("%d%*c", &airi);
            root = makeRoot(airi);
            sum += airi;
        }
        if(strcmp(cmd, "AddLeft")==0){
            int airi, kenchim;
            scanf("%d %d%*c", &airi, &kenchim);
            root = addLeft(root, airi, kenchim);
            sum += airi;
        }
        if(strcmp(cmd, "AddRight")==0){
            int airi, kenchim;
            scanf("%d %d%*c", &airi, &kenchim);
            root = addRight(root, airi, kenchim);
            sum += airi;
        }
        if(strcmp(cmd, "PreOrder")==0){
            PreOrder(root);
            printf("\n");
        }
        if(strcmp(cmd, "InOrder")==0){
            InOrder(root);
            printf("\n");
        }
        if(strcmp(cmd, "PostOrder")==0){
            PostOrder(root);
            printf("\n");
        }
    }
    printf("%d %d", check(root), sum);
    FreeAll(root);
    return 0;
}