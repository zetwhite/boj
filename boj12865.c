#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int** dp;

int knapsack(int pos, int limit, int* weights, int* values){
    if(weights[pos] == -1)
        return 0;
    if(limit == 0)
        return 0;
    if(dp[pos][limit] != -1)
        return dp[pos][limit];

    int res1 = 0, res2 = 0;
    if(weights[pos] <= limit)
        res1 = knapsack(pos+1, limit-weights[pos], weights, values) + values[pos];
    res2 = knapsack(pos+1, limit, weights, values);
    dp[pos][limit] = res1 > res2 ? res1 : res2;
    return dp[pos][limit];
}

int main(){
    int n, k;
    scanf("%d%d", &n, &k);
    int* weights = (int*)malloc(sizeof(int)*(n+1));
    int* values = (int*)malloc(sizeof(int)*(n+1));

    dp = (int**)malloc(sizeof(int*)*(n+1));
    for(int i = 0; i < n+1; i++){
        dp[i] = (int*)malloc(sizeof(int)*(k+1));
        memset(dp[i], -1, sizeof(int)*(k+1));
    }

    for(int i = 0; i < n; i++)
        scanf("%d%d", weights+i, values+i);
    weights[n] = -1;
    values[n] = -1;
    int totalvalue = knapsack(0, k, weights, values);
    printf("%d\n", totalvalue);
    return 0;
}
