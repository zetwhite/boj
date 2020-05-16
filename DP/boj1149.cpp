#include <iostream>
#define max 1000
using namespace std; 

int min2(int a, int b){
    if(a < b)
        return a;
    return b;
}

int min3(int a, int b, int c){
    if( a < b){
        return min2(a, c); 
    }
    else{
        return min2(b, c); 
    }
}

void print_dp(int dp[max][3], int n){
    cout << "----------------------" << endl; 
    for(int i = 0 ; i < 3; i++){
        for(int j = 0; j < n; j++){
            cout << dp[j][i] << " "; 
        }
        cout << endl;
    }
}

int main(){
    int dp[max][3]; 
    int n; 
    cin >> n;
    cin >> dp[0][0];
    cin >> dp[0][1]; 
    cin >> dp[0][2];
    for(int i = 1; i < n; i++){
        for(int j = 0; j < 3; j++){
            int t; 
            cin >> t; 
            dp[i][j] = t + min2(dp[i-1][(j+1)%3], dp[i-1][(j+2)%3]);  
        }
    }

//    print_dp(dp, n); 

    int res = min3(dp[n-1][0], dp[n-1][1], dp[n-1][2]);
    cout << res << endl;
    return 0;
}