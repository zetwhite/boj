#include <stdio.h>
#define N 10
#define MOD 10007
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
    int n, k;
    scanf("%d %d", &n, &k);
    int res = combination(n, k);

    printf("%d\n", res);
    return 0;
}
