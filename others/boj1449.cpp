#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; 

int main(){
    int n, l; 
    cin >> n >> l;
    vector<int> leaks; 
    leaks.reserve(n);
    for(int i = 0; i < n; i++){
        int t; 
        cin >> t;
        leaks.push_back(t);
    } 
    sort(leaks.begin(), leaks.end()); 

    int cnt = 1; 
    double tape = leaks[0] - 0.5 + l;
    for(int i = 1; i < n; i++){
        /*cout << "====================================" << endl;
        cout << "leaks[" << i << "] = " << leaks[i] << endl;
        cout << "tape = " <<tape << endl; */
        if((leaks[i] + 0.5) <= tape){
            continue;
        }
        if((leaks[i] - 0.5) > tape){
            tape = leaks[i] - 0.5 + l; 
        }
        else{
            tape = tape + l; 
        }
        cnt++; 
    }
    cout << cnt << endl;
    return 0;
}