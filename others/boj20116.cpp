#include <iostream>

using namespace std; 

int box[200'002]; 
int main(){
    int n ;
    int L;  
    cin >> n >> L; 
    for(int i = 0; i < n; i++){
        cin >> box[i]; 
    } 

    long long sum = 0; 
    int cnt = 0; 
    for(int i = n-1; i >= 1; i--){
        cnt++; 
        sum += box[i]; 
        //double p = sum / cnt; 
       // cout << "p = " << p << endl; 

        long long begin = (long long)box[i-1] - L;
        long long end = (long long)box[i-1] + L;  
        if(!(begin*cnt < sum && sum < end*cnt)){
            cout << "unstable"; 
            return 0; 
        }
    }
    cout << "stable";
    return 0; 
}