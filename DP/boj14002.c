#include <stdio.h>
#include <stdlib.h>
#define s sizeof(int)*n

int main(){
    int n;
    scanf("%d", &n);

    int* seq = (int*)malloc(s);
    int* next = (int*)malloc(s);
    int* len = (int*)malloc(s);

    for(int i = 0; i < n; i++){
        scanf("%d", seq+i);
        len[i] = 1;
        next[i] = -1;
    }

    for(int i = n-1; i >= 0; i--)
        for(int j = n-1; j > i; j--)
            if(seq[j] > seq[i] && len[j] >= len[i]){
                len[i] = len[j] + 1;
                next[i] = j;
            }

    int max_len = 0;
    int idx = 0;
    for(int i = 0; i < n; i++)
        if(max_len < len[i]){
            max_len = len[i];
            idx = i;
        }
        
    printf("%d\n", max_len);
    while(idx!=-1){
        printf("%d ", seq[idx]);
        idx = next[idx];
    }
}
