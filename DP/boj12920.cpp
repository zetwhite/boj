#include <bits/stdc++.h>
using namespace std;
#define IP pair<int, int> //weight, satisfaction

vector<IP> values;
int** dp; //dp for best_satisfaction

int best_satisfaction(int limit, int pos){
    if(limit == 0)
        return 0;
    if(values.size() <= pos)
        return 0;

    int tmp1 = 0, tmp2 = 0;
    int next_limit = limit - values[pos].first;
    if(next_limit >= 0){
        if(dp[next_limit][pos+1] != -1)
            tmp1 = dp[next_limit][pos+1];
        else
            tmp1 = best_satisfaction(next_limit, pos+1);
        tmp1 += values[pos].second;
    }
    if(dp[limit][pos+1] != -1)
        tmp2 = dp[limit][pos+1];
    else
        tmp2 = best_satisfaction(limit, pos+1);

    int res = (tmp1 > tmp2) ? tmp1 : tmp2;
    dp[limit][pos] = res;
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;

    for(int i = 0; i < n; i++){
        int v, c, k;
        cin >> v >> c >> k;
        int j;
        for(j = 1; 2*j-1 <= k; j=j*2){
            values.push_back(make_pair(v*j, c*j));
        }
        int remain = k - j + 1;
        values.push_back(make_pair(v*remain, c*remain));
    }

    int sz = values.size();
    dp = new int*[m+1];
    for(int i = 0; i < m+1; i++){
        dp[i] = new int[sz+2];
        memset(dp[i], -1, sizeof(int)*(sz+2));
    }

    cout << best_satisfaction(m, 0) << endl;
    return 0;
}
