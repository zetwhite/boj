#include <iostream> 
#include <climits> 
#define INF 30000000
using namespace std; 

int dp[16][1u << 17];

void init_dp(){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 1u << 17; j++)
            dp[i][j] = 0; 
    }
}

int min (int a, int b){
    if( a < b )
        return a; 
    else
        return b; 
}

int find_way(int w[16][16], unsigned int n, unsigned int left, int last, int k = 0){
    if((left + 1u) == (1u << n)){ 
        if(w[last][0] == 0)
            return INF;
        return w[last][0]; 
    } 

    unsigned int gone = (~left) & ((1u << 17) - 1);

    if(dp[last][gone] != 0)
        return dp[last][gone];
    
    int res = INF; 
    for(int i = 0; i < n; i++){
        if(w[last][i] == 0)
            continue;
        if(! ((left >> i) & 1u)){
            unsigned int further_left = left | (1u << i);     
            int cost = find_way(w, n, further_left, i, k+1) + w[last][i]; 
            res = min(res, cost); 
        }
    }
    dp[last][gone] = res;
    return res;
}

int main(){
    int n; 
    cin >> n; 
    init_dp(); 
    int w[16][16]; 
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            cin >> w[i][j];
    }
    int left = 1u; 
    cout << find_way(w, n, left, 0); 
    return 0; 
}