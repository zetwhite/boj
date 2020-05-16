#include <iostream> 
#define max 1001
#define ll long long
using namespace std; 

ll min2(ll a, ll b){
    if(a < b)
        return a;
    return b;
}

ll min3(ll a, ll b, ll c){
    if( a < b){
        return min2(a, c); 
    }
    else{
        return min2(b, c); 
    }
}

void print_dp(ll dp[max][3], int n){
    cout << "----------------------" << endl; 
    for(int i = 0 ; i < 3; i++){
        for(int j = 0; j < n; j++){
            cout << dp[j][i] << "\t"; 
        }
        cout << endl;
    }
}

int main(){
    ll dp[3][max][3];
    int n; 
    cin >> n; 
    int r, g, b; 
    cin >> r >> g >> b;
    int r2, g2, b2; 
    cin >> r2 >> g2 >> b2;
    dp[0][1][0] = max*2; 
    dp[0][1][1] = r + g2; 
    dp[0][1][2] = r + b2; 

    dp[1][1][0] = g + r2; 
    dp[1][1][1] = max*2; 
    dp[1][1][2] = g + b2; 

    dp[2][1][0] = b + r2;
    dp[2][1][1] = b + g2; 
    dp[2][1][2] = max*2; 

    ll tmp[3]; 
    for(int i = 2; i < n; i++){
        for(int k = 0; k < 3; k++){
            cin >> tmp[k];
        }
        for(int j = 0; j < 3; j++){
            for(int l = 0; l < 3; l++){
                dp[j][i][l] = tmp[l] + min2(dp[j][i-1][(l+1)%3], dp[j][i-1][(l+2)%3]);
            }
        }
    }
    //print_dp(dp[0], n); 
    //print_dp(dp[1], n); 
    //print_dp(dp[2], n);
    ll r_start = min2(dp[0][n-1][1], dp[0][n-1][2]);
    ll g_start = min2(dp[1][n-1][0], dp[1][n-1][2]); 
    ll b_start = min2(dp[2][n-1][0], dp[2][n-1][1]);

    ll res = min3(r_start, g_start, b_start);
    cout << res << endl;

    return 0;
}