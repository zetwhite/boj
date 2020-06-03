#include <iostream> 
#include <algorithm> 
#include <vector> 
using namespace std; 

int main(){
    int n; 
    vector<int> tie;
    cin >> n;
    for(int i = 0; i < n; i++){
        int t; 
        cin >> t;
        tie.push_back(t);
    }
    sort(tie.begin(), tie.end(), greater<int>()); 
    int result = tie[0]; 
    for(int i = 1; i < n; i++){
        if(result < tie[i]*(i+1))
            result = tie[i] * (i+1); 
    }
    cout << result << endl;
    return 0;
}