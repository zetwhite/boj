#include <iostream>
#define div 1000000003 
using namespace std; 
int dp[1001][1001];

void init_dp(int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            dp[i][j] = 0; 
        } 
    }
}

int main(){
    int n, k; 
    cin >> n >> k; 
    for(int i = 0; i <= n; i++){
        dp[i][0] = 1;
    }
    for(int i = 1; i <= n; i++){
        dp[i][1] = i;
    }
    for(int i = 3; i <= n; i++){
        for(int j = 2; j <= k; j++){
            dp[i][j] = (dp[i-1][j]%div + dp[i-2][j-1]%div) % div; 
        }
    }
    cout << (dp[n-1][k]%div + dp[n-3][k-1]%div)%div << endl;
    return 0;
}