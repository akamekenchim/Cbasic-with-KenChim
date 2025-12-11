#include <stdio.h>
#include <stdlib.h>
int visited[1000][1000];
int A, B, TARGET;
int found = 0;
int check(int a, int b){
    if(visited[a][b] == 1) return 0;
    if(a > A || b > B) return 0;
    visited[a][b] = 1;
    return 1;
}
typedef struct Node{
    int firstcan;
    int secondcan;
    int steps;
    struct Node *next;
}Takina;
Takina *root = NULL;
Takina *tail = NULL;
Takina *makeNew(int fc, int sc, int st){
    Takina *t = (Takina *)malloc(sizeof(Takina));
    t->firstcan = fc;
    t->secondcan = sc;
    t->steps = st;
    t->next = NULL;
    return t;
}
Takina *Enqueue(Takina *root, int fc, int sc, int st){
    if(root == NULL){
        Takina *t = makeNew(fc, sc, st);
        tail = t;
        return t;
    }
    Takina *t = makeNew(fc, sc, st);
    tail->next = t;
    tail = tail->next;
    return root;
}
Takina *Dequeue(Takina *root){
    if(root == NULL) return NULL;
    if(root->firstcan == TARGET || root->secondcan == TARGET){
        printf("%d", root->steps);
        found++;
        return root;
    }
    // empty A
    if(check(0, root->secondcan)) Enqueue(root, 0, root->secondcan, root->steps+1);
    // empty B
    if(check(root->firstcan, 0)) Enqueue(root, root->firstcan, 0, root->steps+1);
    // fill A
    if(check(A, root->secondcan)) Enqueue(root, A, root->secondcan, root->steps+1);
    // fill B
    if(check(root->firstcan, B)) Enqueue(root,root->firstcan,B, root->steps+1);
    // pour A into B
    int pour=(root->firstcan + root->secondcan) <= B ? root->firstcan:(B-root->secondcan);
    if(check(root->firstcan-pour, root->secondcan + pour)) Enqueue(root,root->firstcan - pour,root->secondcan + pour, root->steps+1);
    // pour B into A
    pour=(root->firstcan + root->secondcan) <= A ? root->secondcan:(A-root->firstcan);
    if(check(root->firstcan+pour, root->secondcan - pour)) Enqueue(root,root->firstcan + pour,root->secondcan - pour, root->steps+1);
    
    Takina *t = root;
    root=root->next;
    if(root == NULL) tail = NULL;
    free(t);
    return root;
}
void FreeAll(Takina *root){
    Takina *t = root;
    while(t != NULL){
        root = root->next;
        free(t);
        t = root;
    }
}
int main(){
    scanf("%d %d %d%*c", &A, &B, &TARGET);
    root = Enqueue(root, 0, 0, 0);
    visited[0][0] = 1;
    while(root != NULL && found == 0){
        root = Dequeue(root);
    }
    if(found == 0){
        printf("-1\n");
    }
    FreeAll(root);
}
