#include <bits/stdc++.h>
#define int_pair pair<int, int>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    int** tri = new int*[n];
    int* sum = new int[n]();
    for(int i = 0; i < n; i++){
        tri[i] = new int[i+1]();
    }

    cin >> tri[0][0];
    int tmp;
    for(int i = 1; i < n; i++){
        for(int j = 0; j <= i; j++){
            if(j == 0 ){
                cin >> tmp;
                tri[i][j] = tri[i-1][j] + tmp;
            }
            else{
                cin >> tmp;
                tri[i][j] = tri[i-1][j-1] + tmp;
                if(j != i && tri[i][j] < tri [i-1][j] + tmp)
                    tri[i][j] = tri[i-1][j] + tmp;
            }
        }
    }

    int max = 0;
    for(int i = 0; i < n; i++){
        if(max < tri[n-1][i]) max = tri[n-1][i];
    }
    cout << max << "\n";
    return 0;
}
