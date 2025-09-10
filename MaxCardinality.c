#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Node{
    int element;
    struct Node *next;
}Takina;
Takina *keys[100000];
Takina *makeNew(int e){
    Takina *t = (Takina *)malloc(sizeof(Takina));
    t->element = e;
    t->next = NULL;
    return t;
}
Takina *find(Takina *root, int e){
    if(root == NULL) return NULL;
    Takina *t;
    for(t=root; t!=NULL; t=t->next){
        if(e == t->element) return t;
    }
    return NULL;
}
Takina *removal(Takina *root, int e){
    if(root == NULL) return NULL;
    if(root->element == e){
        Takina *t = root;
        root = root->next;
        free(t);
        return root;
    }
    root->next = removal(root->next, e);
    return root;
}
Takina *addLast(Takina *root, int e){
    if(root == NULL) return makeNew(e);
    root->next = addLast(root->next, e);
    return root;
}
void ProcessAddKey(int e){
    int hash = e % 100000;
    keys[hash] = addLast(keys[hash], e);
}
void freeAll(Takina *root){
    Takina *t = root;
    while(t != NULL){
        root = root->next;
        free(t);
        t = root;
    }
}
int main(){
    int a, b;
    scanf("%d %d%*c", &a, &b);
    int arr[100000];
    int count = 0;
    for(int i = 0; i<a; i++){
        scanf("%d%*c", &arr[i]);
    }
    int temp;
    for(int i = 0; i<b; i++){
        scanf("%d%*c", &temp);
        ProcessAddKey(temp);
    }
    for(int i = 0; i<a; i++){
        int hash = arr[i] % 100000;
        if(find(keys[hash], arr[i])!=NULL){
            count++;
            keys[hash] = removal(keys[hash], arr[i]);
        }
    }
    printf("%d", count);
    for(int i =0; i<10000; i++){
        freeAll(keys[i]);
    }
    return 0;
}
