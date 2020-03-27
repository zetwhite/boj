#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

int dp[40500];
bool refill[40500] = {0, };
int* can_eat;

int max_eat(int remain_candy, int nopt, int f, int m, int n, int count){
    if(remain_candy == 0)
        return 0;
    int res = 0;

    for(int i = 0; i < nopt; i++){
        int remain = remain_candy - can_eat[i];
        if(remain >= 0){
            while(remain <= n && refill[remain]){
                remain += m;
                count++;
            }
            int tmp;
            if(count >= f+1)
                return -1;
            if(dp[remain] != -1)
                tmp = dp[remain] + can_eat[i];
            else{
                tmp = max_eat(remain, nopt, f, m, n, count);
                if(tmp == -1)
                    return -1;
                tmp += can_eat[i];
            }
            if(res < tmp)
                res = tmp;
        }
    }
    dp[remain_candy] = res;
    return res;
}

int main(){
    int n, nopt, f, m;
    scanf("%d%d%d%d", &n, &nopt, &f, &m);
    can_eat = (int*)malloc(sizeof(int)*nopt);
    for(int i = 0; i < nopt; i++)
        scanf("%d", can_eat + i);
    for(int i = 0; i < f; i++){
        int tmp;
        scanf("%d", &tmp);
        refill[tmp] = true;
    }
    memset(dp, -1, sizeof(int)*40500);

    int res = max_eat(n, nopt, f, m, n, 0);
    printf("%d\n", res);
    return 0;
}
