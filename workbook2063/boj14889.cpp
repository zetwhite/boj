#include <iostream>

using namespace std;

int make_team(int now, int k, int n, bool picked[20], int s[20][20]){
    if(k == 0){
        int team1=0, team2=0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < i; j++){
                if(picked[i]){
                    if(picked[j]){
                        team1 += s[i][j];
                        team1 += s[j][i];
                    }
                }
                else{
                    if(!picked[j]){
                        team2 += s[i][j];
                        team2 += s[j][i];
                    }
                }
            }
        }
        if(team1 > team2)
            return team1 - team2;
        else
            return team2 - team1;
    }
    if(now-1 < 0)
        return 1000000000;
    picked[now-1] = true;
    int res1 = make_team(now-1, k-1, n, picked, s);
    picked[now-1] = false;
    int res2 = make_team(now-1, k, n, picked, s);
    if(res1 < res2)
        return res1;
    else
        return res2;
}

int main(){
    int n;
    int s[20][20];
    bool picked[20] = {0, };
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            cin >> s[i][j];
    }
    cout << make_team(n, n/2, n, picked, s);

    return 0;
}
