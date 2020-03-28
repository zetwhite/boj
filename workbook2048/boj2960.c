#include <stdio.h>
#include <stdlib.h>

int main(void){
    int* arr;
    int n , k;
    scanf("%d%d", &n, &k);
    arr = (int*)malloc(sizeof(int)*(n+1));
    for(int i = 2; i < n+1; i++){
        arr[i] = i;
    }
    int del = -1;
    int k_count = k;
    for(int i = 2; i < n+1; i++){
        if(arr[i]!=0){
            int j = i;
            while( j < n+1 && k_count > 0){
                del = arr[j];
                if(del != 0){
                    arr[j] = 0;
                    k_count--;
                }
                j += i;
            }
        }
        if(k_count < 0)
            break;
    }
    printf("%d\n", del);
    return 0;
}
