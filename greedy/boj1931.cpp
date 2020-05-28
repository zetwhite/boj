#include <iostream>
#include <vector> 
#include <algorithm>
using namespace std; 

typedef long long ll;
typedef pair<ll, ll> PL;

ostream& operator << (ostream& os, PL& p){
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

bool compare(const PL& left, const PL& right){
    if(left.second < right.second)
        return true; 
    else if(left.second > right.second)
        return false; 
    if(left.second == right.second){
        if(left.first > right.first)
            return false; 
        else
            return true;
    }
}

int main(){
    int n; 
    cin >> n; 
    vector<PL> candidates;
    candidates.reserve(n);
    ll start, end; 
    for(int i = 0; i < n; i++){
        cin >> start >> end; 
        candidates.emplace_back(start, end); 
    }
    sort(candidates.begin(), candidates.end(), compare);
   /* for(int i = 0; i < n; i++){
        cout << candidates[i] << endl;
    }
    cout << "------------------" << endl;*/
    ll last = candidates[0].second; 
    //cout << candidates[0] << endl; 
    int cnt = 1; 
    for(int i = 1; i < n; i++){
        if(candidates[i].first >= last){
            cnt++; 
            last = candidates[i].second; 
            //cout << candidates[i] << endl;
        }
    }
    cout << cnt << endl;
    return 0; 
}