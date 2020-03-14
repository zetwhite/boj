#include <stdio.h>
#include <stdlib.h>
#define INF 1000001

int main(){
    int n;
    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int)*(n+1));
    arr[1] = 0;
    arr[2] = 1;
    arr[3] = 1;

    for(int i = 4; i <= n; i++){
        arr[i] = INF;
    }
    for(int i = 4; i <= n; i++){
        int tmp = 0;
        if(!(i%3)){
            tmp = arr[i/3] + 1;
            if(arr[i] > tmp) arr[i] = tmp;
        }
        if(!(i%2)){
            tmp = arr[i/2] + 1;
            if(arr[i] > tmp) arr[i] = tmp;
        }
        tmp = arr[i-1] + 1;
        if(arr[i] > tmp) arr[i] = tmp;
    }
    printf("%d\n", arr[n]);
}
