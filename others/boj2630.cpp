#include <iostream> 
using namespace std; 

int blue = 0; 
int white = 0; 
bool dp[128][128]; 

void count(int start_x, int start_y,  int size){
    bool success = true; 
    bool color = dp[start_x][start_y];  
    for(int i = start_x; i < start_x + size; i++){
        for(int j = start_y; j < start_y + size; j++){
            if(dp[i][j] != color){
                success = false; 
                break; 
            }
        }
    }

    if(success){
        if(color){
            blue ++; 
        }
        else{
            white ++; 
        }
    }
    else{
        int half = size / 2; 
        count(start_x, start_y, half); 
        count(start_x + half , start_y, half); 
        count(start_x, start_y + half, half); 
        count(start_x + half, start_y + half, half); 
    }
}

int main(){
    int N; 
    cin >> N; 
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> dp[i][j]; 
        }
    }
    count(0, 0, N); 
    cout << white << endl; 
    cout << blue << endl; 
    return 0; 
}