#include <iostream> 
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Homework{
public:
    int due; 
    int score; 
    Homework(int _due, int _score):
    due(_due), 
    score(_score){};
}; 

bool operator < (const Homework& left, const Homework& right){
    return (left.due < right.due); 
}

bool operator > (const Homework& left, const Homework& right){
    return (left.due > right.due); 
}

int main(){
    int n; 
    cin >> n; 
    vector<Homework> hws;
    hws.emplace_back(0, 0);
    for(int i = 0; i < n; i++){
        int d, w; 
        cin >> d >> w; 
        hws.emplace_back(d, w); 
    }
    sort(hws.begin(), hws.end(), greater<Homework>()); 
    priority_queue<int> selections;

    int last = hws[0].due;
    int res = 0;
    int idx = 0; 
    for(int i = last; i > 0; i--){
        while(hws[idx].due == i){
            selections.push(hws[idx].score); 
            idx++;
        }
        if(selections.empty())
            continue;
        res += selections.top(); 
        selections.pop();
    }
    cout << res << endl;
    return 0; 
}