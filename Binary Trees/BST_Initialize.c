// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Node{
    long long element;
    struct Node *left;
    struct Node *right;
}Takina;
Takina *root = NULL;
Takina *makeNew(long long e){
    Takina *t = (Takina *)malloc(sizeof(Takina));
    t->element = e;
    t->left = NULL;
    t->right = NULL;
    return t;
}
Takina *find(Takina *root, long long e){
    if(root == NULL) return NULL;
    Takina *t = root;
    while(t!=NULL){
        if(e < t->element){
            t=t->left;
        }
        else if(e > t->element){
            t=t->right;
        }
        else if(e == t->element){
            return t;
        }
    }
    return NULL;
}
Takina *addNew(Takina *root, long long e){
    if(root == NULL) return makeNew(e);
    if(find(root, e)!=NULL) return root;
    if(root->element > e){
        root->left = addNew(root->left, e);
        return root;
    }
    else if(root->element < e){
        root->right = addNew(root->right, e);
        return root;
    }
}
void PrintAll(Takina *root){
    if(root == NULL) return;
    printf("%lld ", root->element);
    PrintAll(root->left);
    PrintAll(root->right);
}
void FreeAll(Takina *root){
    if(root == NULL) return;
    FreeAll(root->left);
    FreeAll(root->right);
    free(root);
}
int main() {
    while(1){
        char cmd[29];
        scanf("%s%*c", cmd);
        if(strcmp(cmd, "#")==0) break;
        if(strcmp(cmd, "insert")==0){
            long long airi;
            scanf("%d%*c", &airi);
            root = addNew(root, airi);
        }
    }
    PrintAll(root);
    FreeAll(root);
    return 0;
}