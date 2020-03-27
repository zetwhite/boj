#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int invest_result[21];
int** iv;

int dp[301][21]; //(m, c) c 이상의 회사에 m을 투자했을때 얻을 수 있는 최대 이익
int invest_res[301][21]; //(m, c) c 이상의 회사에 m을 투자했을 때 최대 이득을 얻기 위해서 회사c에 투자해야하는 값


int invest(int money, int company){
    if(money <= 0){
        invest_res[money][company] = 0;
        dp[money][company] = 0;
        return 0;
    }
    int res = 0;
    int invest_m = 0;
    for(int i = money; i >= 0; i--){
        int tmp;
        if(dp[money-i][company+1] != -1)
            tmp = dp[money-i][company+1] + iv[i][company];
        else
            tmp = invest(money-i, company+1) + iv[i][company];
        if(tmp > res){
            res = tmp;
            invest_m = i;
        }
    }
    dp[money][company] = res;
    invest_res[money][company] = invest_m;
    return res;
}


void reconstruct(int max, int* res, int n, int m){
    int find = max;
    for(int i = 0; i < m; i++){
        for(int j = 0; j <= n; j++){
            if(dp[j][i] == find){
                res[i] = invest_res[j][i];
                find = find - iv[res[i]][i];
                break;
            }
        }
    }
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);

    iv = (int**)malloc(sizeof(int*)*(n+1));
    for(int i = 0; i < n+1; i++)
        iv[i] = (int*)malloc(sizeof(int)*m);
    for(int i = 0; i < m; i++)
        iv[0][i] = 0;

    for(int i = 0; i < n; i++){
        int value;
        scanf("%d", &value);
        for(int j = 0; j < m; j++){
            scanf("%d", iv[value]+j);
        }
    }

    for(int i = 0; i < n+1; i++){
        memset(dp+i, -1, sizeof(int)*(m));
        dp[i][m] = 0;
    }
    for(int i = 0; i < n+1; i++)
        memset(invest_res+i, -1, sizeof(int)*m);

    int max = invest(n, 0);
    printf("%d\n", max);
    int* picks = (int*)malloc(sizeof(int)*m);
    reconstruct(max, picks, n, m);
    for(int i = 0; i < m; i++)
        printf("%d ", picks[i]);
    return 0;
}
