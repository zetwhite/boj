#include <stdio.h>
#define N 30
//nCk = n-1Ck-1 + n-1Ck

int dp[N+1][N+1] = {0, };

int combination(int n, int k){
    if(n==k || k == 0)
        return 1;
    else if( n-k == 1 || k == 1 )
        return n;
    else if(dp[n][k] != 0)
        return dp[n][k];
    else{
        int res = (combination(n-1, k-1) + combination(n-1, k));
        dp[n][k] = res;
        dp[n][n-k] = res;
        return res;
    }
}

int main(){
    int k;
    scanf("%d\n", &k);
    for(int i = 0; i < k; i++){
        int n, m;
        scanf("%d%d", &n, &m);
        printf("%d\n", combination(m,n));
    }
    return 0;
}
