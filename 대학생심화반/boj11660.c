#include <stdio.h>
#include <stdlib.h>
#define N 1024

int arr[N+1][N+1];
int sum[N+1][N+1];

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 1; i < n+1; i++)
        for(int j = 1 ; j < n+1; j++)
            scanf("%d", &(arr[i][j]));

    for(int i = 0; i < N+1; i++){
        sum[0][i] = 0;
        sum[i][0] = 0;
    }

    for(int i = 1; i < n+1; i++)
        for(int j = 1; j < n+1; j++)
            sum[i][j] = sum[i][j-1] + sum[i-1][j] - sum[i-1][j-1] + arr[i][j];

    for(int i = 0; i < m; i++){
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        int res = sum[x2][y2] - sum[x2][y1-1] - sum[x1-1][y2] + sum[x1-1][y1-1];
        printf("%d\n", res);
    }
    return 0;
}
