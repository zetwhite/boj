#include<stdio.h>
#define MOD 10007

//nHr = n+r-1Cr
//n개 중 중복을 포함해서 r개 뽑기
int dp[1010][1010] = {0, };

int combination(int n, int k){
    if (n==k || k==0)
        return 1;
    else if (n-1 == k || k ==1)
        return n;
    else if(dp[n][k])
        return dp[n][k];
    else{
        int res = (combination(n-1, k-1)%MOD + combination(n-1, k)%MOD)%MOD;
        dp[n][k] = res;
        dp[n][n-k] = res;
        return res;
    }
}

int main(){
    int r;
    scanf("%d", &r);
    printf("%d", combination(r+10-1, r));
    return 0;
}
