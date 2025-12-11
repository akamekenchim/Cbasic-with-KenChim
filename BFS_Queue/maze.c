#include <stdio.h>
#include <stdlib.h>
int maze[1000][1000];
int rstart; 
int cstart;
int rend;
int cend;
int found = 0;
int visited[1000][1000];
int check(int r, int c){
    if(r < 0 || c < 0 || c >= cend || r >= rend) return 0;
    if(visited[r][c] == 1) return 0;
    if(maze[r][c]==1) return 0;
    
    visited[r][c] = 1;
    return 1;
}

typedef struct Node{
    int row;
    int column;
    int steps;
    struct Node *next;
}Takina;
Takina *root = NULL;
Takina *tail = NULL;
Takina *makeNew(int r, int c, int st){
    Takina *t = (Takina *)malloc(sizeof(Takina));
    t->row = r;
    t->column = c;
    t->steps = st;
    t->next = NULL;
    return t;
}
Takina *Enqueue(Takina *root, int r, int c, int st){
    if(root == NULL){
        Takina *t = makeNew(r, c, st);
        tail = t;
        return t;
    }
    Takina *t = makeNew(r, c, st);
    tail->next = t;
    tail = tail->next;
    return root;
}
Takina *Dequeue(Takina *root){
    if(root == NULL) return NULL;
    if(root->row == 0 || root->row == rend-1 || root->column == 0 || root->column == cend-1){
        printf("%d\n", root->steps + 1);
        found++;
        return root;
    }
    if(check(root->row, root->column + 1)) Enqueue(root, root->row, root->column+1, root->steps + 1);
    if(check(root->row, root->column - 1)) Enqueue(root, root->row, root->column-1, root->steps + 1);
    if(check(root->row + 1, root->column)) Enqueue(root, root->row + 1, root->column, root->steps + 1);
    if(check(root->row - 1, root->column)) Enqueue(root, root->row - 1, root->column, root->steps + 1);
    
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
    scanf("%d %d %d %d", &rend, &cend, &rstart, &cstart);
    for(int i = 0; i<rend; i++){
        for(int j = 0; j <cend; j++){
            scanf("%d", &maze[i][j]);
        }
    }
    root = Enqueue(root, rstart-1, cstart-1, 0);
    visited[rstart - 1][cstart - 1] = 1;
    while(root != NULL && found == 0){
        root = Dequeue(root);
    }
    if(found == 0){
        printf("-1\n");
    }
    FreeAll(root);
}
