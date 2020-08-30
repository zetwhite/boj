#include <iostream> 

using namespace std; 


int main(){
    long long a, b, c; 
    cin >> a >> b >> c; 

    long long power = b; 
    bool bin[65]; 
    int i = 0; 
    while(power > 0){
        if( power % 2 ){
            bin[i] = 1; 
        }
        else {
            bin[i] = 0; 
        }
        i++; 
        power = power / 2; 
    }
    i = i - 2; 

    long long result = a; 
    while (i >= 0){
        result = result * result; 
        result = result % c; 
        if(bin[i]){
            result = result * a; 
            result = result % c; 
        }
        i--; 
    }
    result = result % c; 
    cout << result; 
    return 0; 
}