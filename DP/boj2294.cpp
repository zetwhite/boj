#include<stdio.h>
#include <stdlib.h>
#define INF 100001

int main(){
    int n, k;
    scanf("%d%d", &k, &n);
    int* k_arr = (int*)malloc(sizeof(int)*k);
    int* dp = (int*)malloc(sizeof(int)*(n+1));
    int min = INF;
    for(int i = 0; i < k; i++){
        scanf("%d", k_arr+i);
        if(k_arr[i] < min)
            min = k_arr[i];
    }

    for(int i = 0; i < n+1; i++)
        dp[i] = INF;
    for(int j = 0; j < k; j++){
        dp[k_arr[j]] = 1;
    }
    for(int i = min+1; i < n+1; i++){
        for(int j = 0; j < k; j++){
            int tmp = i - k_arr[j];
            if(tmp <= 0)
                continue;
            if(dp[tmp] == INF)
                continue;
            if(dp[i] > dp[tmp] + 1)
                dp[i] = dp[tmp] + 1;
        }
    }
    if(dp[n] == INF)
        printf("-1\n");
    else
        printf("%d\n", dp[n]);
}
