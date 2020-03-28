#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, m;
    int* arr;
    int* sum;
    scanf("%d %d", &n, &m);
    arr = (int*)malloc(sizeof(int)*n);
    sum = (int*)malloc(sizeof(int)*(n+1));
    for(int i = 0; i < n; i++)
        scanf("%d", arr+i);

    int s = 0;
    sum[0] = 0;
    for(int i = 1; i < n + 1; i++){
        s += arr[i-1];
        sum[i] = s;
    }

    for(int i = 0; i < m; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", sum[b] - sum[a-1]);
    }

    return 0;
}
