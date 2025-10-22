// Online C compiler to run C program online
#include <stdio.h>
typedef struct Segment{
    int start;
    int end;
}Takina;
void Merge(Takina a[], int start, int mid, int end){
    int l1 = (mid - start + 1);
    int l2 = (end - mid);
    Takina L[l1];
    Takina R[l2];
    for(int i = 0; i<l1; i++){
        L[i] = a[start+i];
    }
    for(int i = 0; i<l2; i++){
        R[i] = a[mid+1+i];
    }
    int i = 0;
    int j = 0;
    int k = start;
    while(i < l1 && j < l2){
        if(L[i].end <= R[j].end){
            a[k] = L[i];
            k++; i++;
        }
        else{
            a[k] = R[j];
            k++; j++;
        }
    }
    while(i < l1){
        a[k] = L[i];
        k++; i++;
    }
    while(j < l2){
        a[k] = R[j];
        k++; j++;
    }
}
void MergeSort(Takina a[], int start, int end){
    if(start < end){
        int mid = (start + end)/2;
        MergeSort(a, start, mid);
        MergeSort(a, mid+1, end);
        Merge(a, start, mid, end);
    }
}
int main() {
    int count = 1;
    int n;
    Takina segments[100000];
    scanf("%d", &n);
    for(int i = 0; i<n; i++){
        scanf("%d %d", &segments[i].start, &segments[i].end);
    }
    MergeSort(segments, 0, n-1);
    int i = 0;
    int curend = segments[0].end;
    while(i < n){
        for(int p = i; p<n; p++){
            //if(i == p) continue;
            if(curend < segments[p].start){
                count++;
                curend = segments[p].end;
                i = p;
            }
        }
        i++;
    }
    printf("%d", count);
    return 0;
}s