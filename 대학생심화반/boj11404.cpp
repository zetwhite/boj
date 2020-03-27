#include <bits/stdc++.h>
#define N 101
#define INF 10000001
using namespace std;
int C[N][N][N];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <=n; j++)
            C[0][i][j] = INF;

    int a, b, c;
    for(int i = 0; i < m; i++){
        cin >> a >> b >> c;
        if(C[0][a][b] > c ) C[0][a][b] = c;
    }

    for(int i = 1; i <= n; i++){
        C[0][i][i] = 0;
    }

    for(int k = 1; k <= n; k++){
        for(int u = 1; u <= n; u ++){
            for(int v = 1; v <= n; v++){
                C[k][u][v] = min(C[k-1][u][v], C[k-1][u][k]+C[k-1][k][v]);
            }
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(C[n][i][j] >= INF)
                cout << "0 ";
            else
                cout << C[n][i][j] <<" ";
        }
        cout << endl;
    }
    return 0;
}
