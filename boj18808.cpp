#include <bits/stdc++.h>
using namespace std;

int laptop[41][41];

class Sticker{
public:
    int r1[4], r2[4];
    bool st[4][11][11];

    Sticker(){}
    void setr(int _r1, int _r2){
        r1[0]= _r1; r2[0]=_r2;
    }
    void setst(){
        for(int i = 1; i <=r1[0]; i++){
            for(int j = 1; j <= r2[0]; j++)
                cin >> st[0][i][j];
        }
    }
    void setst(int d){
        if(d <= 0 || 4 <= d)
            return;
        r1[d] = r2[d-1];
        r2[d] = r1[d-1];
        for(int i = 1; i <= r1[d-1]; i++){
            for(int j = 1; j <= r2[d-1]; j++)
                st[d][j][r1[d-1]-i+1] = st[d-1][i][j];
        }
    }
};

inline int is_okay(bool st[11][11], int r1, int r2, int x, int y){
    for(int i = x; i < x+r1; i++){
        for(int j = y; j < y+r2; j++){
            if(st[i-x+1][j-y+1] && laptop[i][j])
                return false;
        }
    }
    for(int i = x; i <= x+r1; i++){
        for(int j = y; j <= y+r2; j++)
            laptop[i][j] += st[i-x+1][j-y+1];
    }
    return true;
}

bool conflict(Sticker &s, int degree, int n, int m){
    for(int i = 1; i <= n-s.r1[degree]+1; i++){
        for(int j = 1; j <= m-s.r2[degree]+1; j++){
            if(is_okay(s.st[degree], s.r1[degree], s.r2[degree], i, j))
                return true;
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    Sticker* skrs = new Sticker[k];
    for(int i = 0; i < k; i++){
        int r1, r2;
        cin >> r1 >> r2;
        skrs[i].setr(r1, r2);
        skrs[i].setst();
    }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            laptop[i][j] = 0;

    for(int i = 0; i < k; i++){
        for(int j = 0; j < 4; j++){
            skrs[i].setst(j);
            if(conflict(skrs[i], j, n, m))
                break;
        }
    }

    int cnt = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <=m; j++)
            if(laptop[i][j])
                cnt++;
    }
    cout << cnt << endl;
    return 0;
}
