#include <iostream> 
#include <cmath>

using namespace std; 
int S, N, K; 

int getColor(int size, int row, int col){
    if(size < N){
        return 0; 
    }
    int start = (N-K)/2 * size/N; 
    int end = (N+K)/2 * size/N; 
    if( (start <= row && row < end) && (start <= col && col < end) ){
        return 1; 
    }
    int nextSize = size / N; 
    row = row % nextSize; 
    col = col % nextSize; 
    return getColor(nextSize, row, col); 
}

int main(){
    int R1, R2, C1, C2; 
    cin >> S >> N >> K >> R1 >> R2 >> C1 >> C2; 

    int size = static_cast<int>(pow(N, S)); 
    for(int r = R1; r <= R2; r++){
        for(int c = C1; c <= C2 ; c++){
            if(size <= r || size <= c)
                cout << 0; 
            else 
                cout << getColor(size, r, c); 
        }
        cout << "\n"; 
    }
    return 0; 
}