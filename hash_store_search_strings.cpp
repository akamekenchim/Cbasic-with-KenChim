#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Node{
    char string[50];
    struct Node *next;
}Takina;
Takina *keys[10000];
int hash_value(char s[]){
    int sum = 0;
    for(int i = 0; i<strlen(s); i++){
        sum += s[i];
    }
    return sum;
}
Takina *makeNew(char s[]){
    Takina *t = (Takina *)malloc(sizeof(Takina));
    strcpy(t->string, s);
    t->next = NULL;
    return t;
}
Takina *find(Takina *root, char s[]){
    if(root == NULL) return NULL;
    Takina *t;
    for(t=root; t!=NULL; t=t->next){
        if(strcmp(s, t->string)==0) return t;
    }
    return NULL;
}
Takina *addLast(Takina *root, char s[]){
    if(root == NULL) return makeNew(s);
    if(find(root, s)!=NULL) return root;
    root->next = addLast(root->next, s);
    return root;
}
void ProcessAddKey(int hash, char s[]){
    keys[hash] = addLast(keys[hash], s);
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
    while(1){
        char str[60];
        scanf("%s%*c", str);
        if(strcmp(str, "*")==0) break;
        int hash = hash_value(str);
        ProcessAddKey(hash, str);
    }
    while(1){
        char cmd[20];
        scanf("%s%*c", cmd);
        if(strcmp(cmd, "***")==0) break;
        if(strcmp(cmd, "insert")==0){
            char airi[60];
            scanf("%s%*c", airi);
            int h = hash_value(airi);
            if(find(keys[h], airi)==NULL){
                printf("1\n");
            }
            else printf("0\n");
            ProcessAddKey(h, airi);
        }
        if(strcmp(cmd, "find")==0){
            char airi[60];
            scanf("%s%*c", airi);
            if(find(keys[hash_value(airi)], airi)!= NULL) printf("1\n");
            else printf("0\n");
        }
    }
    for(int i =0; i<10000; i++){
        freeAll(keys[i]);
    }
    return 0;
}
