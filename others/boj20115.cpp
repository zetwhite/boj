#include <iostream> 

using namespace std; 

int main(){
    int n; 
    cin >> n; 
    long long d; 
    //long long drinks[n]; 

    long long max = 0; 
    long long idx = 0; 
    long long sum = 0; 
    for(int i = 0; i < n; i++){
        cin >> d; 
        if(max < d){
            max = d; 
        } 
        sum += d; 
    }

    sum -= max; 
    cout << static_cast<double>(max) + static_cast<double>(sum) / 2;
    return 0; 
}