#include <iostream> 

using namespace std; 

char note[11][1002]; 
char org[102]; 

int main(){
    int N, H, W; 
    cin >> N >> H >> W; 

    for(int i = 0; i < H; i++){
        cin >> note[i]; 
    }
    for(int i = 0; i < N; i++){
        org[i] = '?'; 
    }
    org[N] = '\0'; 

    for(int idx = 0; idx < N; idx++){
        for(int j = 0; j < W; j++){
            for(int l = 0; l < H; l++){
                if(note[l][idx*W + j] != '?'){
                    org[idx] = note[l][idx*W+j]; 
                    break; 
                }
            }
            if(org[idx] != '?') 
                break; 
        }
    }

    cout << org; 
    return 0; 
}