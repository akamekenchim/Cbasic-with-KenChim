#include <stdio.h>
int TSP[1000][1000];
int n;
int min_sol = 10000000;
int cmin = 100000;
int q[1000];
int visited[1000];
void Try(int k, int sum){
    for(int v = 1; v<=n; v++){
        if(visited[v] == 0){
            int w = 0;
            if(k > 1) w = TSP[q[k-1]][v];
            int new_sum = sum + w;
            if(new_sum + (n-k+1)*cmin >= min_sol) continue;
            q[k] = v;
            visited[v] = 1;
            
            if(k == n){
               int tour = new_sum + TSP[v][q[1]];
               if(tour < min_sol) min_sol = tour;
            }
            else{
                Try(k+1, new_sum);
            }
            visited[v] = 0;
        }
    }
}
int main(){
    scanf("%d", &n);
    for(int i =1; i<=n; i++){
        for(int j = 1; j<=n; j++){
            scanf("%d", &TSP[i][j]);
            if(TSP[i][j] > 0 && TSP[i][j] < cmin) cmin = TSP[i][j];
        }
    }
    Try(1, 0);
    printf("%d", min_sol);
}
