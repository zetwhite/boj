#include <iostream> 
#include <queue> 
#include <algorithm> 
using namespace std; 
typedef pair<int, int> D_C; 

bool DCsort(D_C left, D_C right) {
    if(left.first > right.first)
        return true; 
    else if(left.first == right.first)
        return left.second > right.second; 
    return false; 
}

int main(){
    int n; 
    cin >> n; 
    vector<D_C> dcs; 
    dcs.reserve(n);  
    for(int i = 0; i < n; i++){
        int deadline, cupRamen;
        cin >> deadline >> cupRamen;  
        dcs.emplace_back(deadline, cupRamen); 
    }
    sort(dcs.begin(), dcs.end(), DCsort); 
    //for(int i = 0; i < n; i++)
    //    cout << dcs[i].first << ", " << dcs[i].second << endl; 

    priority_queue<int, vector<int>, less<int>> pq; 
    int idx = 0; 
    int res = 0; 
    for(int day=n; day > 0; day--) {
        while(idx < n && dcs[idx].first >= day) {
            pq.push(dcs[idx].second); 
            idx++; 
        }
        if(!pq.empty()){
            res += pq.top(); 
            //cout << "day " << day << " , "<< pq.top() << endl; 
            pq.pop(); 
        }
    }
    cout << res << endl; 
    return 0; 
}