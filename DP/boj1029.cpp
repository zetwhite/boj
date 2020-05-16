#include <iostream> 
#include <string>
#include <cstring>
#define N_MAX 15
using namespace std; 

int dp[N_MAX][1u <<N_MAX][10]; //seller, who_can_buy, price
int market[N_MAX][N_MAX];

void init_dp(int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < (1u<<N_MAX); j ++){
            memset(dp[i][j], -1, sizeof(int)*10); 
        }
    }
}

void print_dp(int n){
    for(int j = 0; j < (1u << n); j++){
        cout << j  << "\t"; 
    }
    cout << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < (1u << n); j++){
            cout << dp[i][j] << "\t"; 
        }
        cout << endl;
    }
}

int max2(int a, int b){
    if(a > b)
        return a;
    return b;  
}

int start_market(int n, int seller, int price, unsigned int visited){
    int res = 1; 
    int& ret = dp[seller][~visited & ((1u<<n)-1)][price]; 
    if((visited + 1) == (1u<<n)){
        ret = 1;
        return ret; 
    }
    for(int i = 1; i <n; i++){
        unsigned int next = 1u << i; 
        if(seller == i)
            continue;
        if((next & visited) == false && price <= market[seller][i]){
            int tmp; 
            int can_go = (~(visited|next)) & ((1u<<n)-1); 
            if(dp[i][can_go][market[seller][i]] != -1)
                tmp = dp[i][can_go][market[seller][i]] + 1;  
            else 
                tmp = start_market(n, i, market[seller][i], visited|(1u << i)) + 1; 
            res = max2(res, tmp);
        }    
    }
    ret = res; 
   // print_dp(n);
    return ret; 
}

int main(){
    int N; 
    cin >> N;
    init_dp(N);  
    for(int i = 0; i < N; i++){
        string tmp; 
        cin >> tmp;
        for(int j = 0; j < N; j++)
            market[i][j] = tmp[j] - '0'; 
    }

    cout << start_market(N, 0, 0, 1u) << endl; 
    //print_dp(N);
    return 0;
}