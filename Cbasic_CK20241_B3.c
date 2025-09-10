#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct req{
    char url[100];
    int size;
    struct req *next;
};
typedef struct req Takina;
Takina *root;
Takina *makeNew(char u[], int s){
    Takina *newnode = (Takina *)malloc(sizeof(Takina));
    strcpy(newnode->url, u);
    newnode->size = s;
    newnode->next = NULL;
    return newnode;
}
Takina *addLast(char u[], int s, Takina *root){
    if(root == NULL) return makeNew(u, s);
    root->next = addLast(u, s, root->next);
    return root;
}
void printQueue(Takina *root){
    Takina *t;
    int count= 0;
    for(t=root; t!=NULL; t=t->next){
        printf("%s | %d\n", t->url, t->size);
        count++;
    }
    if(count ==0){
        printf("mt\n");
        return;
    }
}
void freeData(Takina *root){
    Takina *t = root;
    while(t!=NULL){
        root = root->next;
        free(t);
        t=root;
    }
}
Takina *removeNode(char u[], Takina *root){
    if(root == NULL) return NULL;
    if(strcmp(root->url, u)==0){
        Takina *t=root;
        root = root->next;
        free(t);
        return root;
    }
    root->next = removeNode(u, root->next);
    return root;
}
Takina *find(char u[], Takina *root){
    if(root == NULL) return NULL;
    Takina *t;
    for(t = root; t!=NULL; t=t->next){
        if(strcmp(t->url, u)==0) return t;
    }
    return NULL;
}
Takina *deleteFirst(Takina *root){
    if(root == NULL){
        printf("fetch\nmt\n");
        return NULL;
    }
    Takina *t = root;
    printf("fetch\n");
    printf("%s | %d\n", t->url, t->size);
    root = root->next;
    free(t);
    return root;
}
int main(){
    while(1){
        char cmd[100];
        scanf("%s%*c", cmd);
        if(strcmp(cmd, "*")==0) break;
        if(strcmp(cmd, "append")==0){
            char u[100];
            int s;
            scanf("%s%*c%d%*c", u, &s);
            root = addLast(u, s, root);
        }
        if(strcmp(cmd, "print")==0){
            printf("print\n");
            printQueue(root);
        }
        if(strcmp(cmd, "abort")==0){
            char u[100];
            scanf("%s%*c", u);
            int count1 = 0;
            while(1){
                if(find(u, root)!=NULL){
                    root = removeNode(u, root);
                    count1++;
                }
                else break;
            }
            printf("abort: %d\n", count1);
        }
        if(strcmp(cmd, "fetch")==0){
            root = deleteFirst(root);
        }
    }
    return 0;
}