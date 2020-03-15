#include <stdio.h>
//��� ��찡 ||, =, |= �� �ϳ��� ���۵Ǵ� �ɷ� �з��ȴ�.

int main(){
    int n;
    scanf("%d", &n);

    int dp[1001];
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 3;
    for(int i = 4; i <= n; i++){
        dp[i] = 2 * dp[i-2];
        dp[i] += dp[i-3];
        if(dp[i] > 10007)
            dp[i] %= 10007;
    }
    printf("%d\n", dp[n]%10007);
    return 0;
}
