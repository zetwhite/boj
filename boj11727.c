#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int dp[1001];
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 3;
    dp[3] = 5;
    for(int i = 4; i <= n; i++){
        dp[i] = dp[i-2] * 3;
        dp[i] += dp[i-3] * 2;
        if(dp[i] >= 10007)
            dp[i] %= 10007;
    }
    printf("%d\n", dp[n]);
}
