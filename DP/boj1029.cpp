#include <iostream> 
#include <string>
#define N_MAX 15
using namespace std; 

int market[N_MAX][N_MAX];

int max2(int a, int b){
    if(a > b)
        return a;
    return b;  
}

int start_market(int N, int index, int price, bool visited[N_MAX]){
    int max = 0; 
    if(visited[index])
        return 0;
    visited[index] = 1; 
    for(int i = 0; i < N; i++){
        if(price <= market[index][i]){
            int next = 1 + start_market(N, i, market[index][i], visited); 
            max = max2(max, next); 
        }
    }
    visited[index] = 0; 
    return max;
}

int main(){
    int N; 
    int dp[N_MAX][N_MAX];
    bool visited[N_MAX] = {false, }; 
    cin >> N; 
    for(int i = 0; i < N; i++){
        string tmp; 
        cin >> tmp;
        for(int j = 0; j < N; j++)
            market[i][j] = tmp[j]; 
    }
    cout << start_market(N, 0, 0, visited) + 1 << endl; 
    return 0;
}