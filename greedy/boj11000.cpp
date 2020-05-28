#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
using namespace std; 
typedef pair<int, int> PI;

ostream& operator << (ostream& os, PI& p){
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

bool compare(const PI& left, const PI& right){
    if(left.first < right.first)
        return true; 
    else if(left.first > right.first)
        return false; 
    if(left.first == right.first){
        if(left.second < right.second)
            return true; 
        else
            return false;
    }
    return false;
}

void print_vector(vector<int>& v){
    for(int i = 0; i < v.size(); i++){
        cout << v[i] << ", ";
    }
    cout << endl; 
}

int main(){
    int N; 
    cin >> N;
    int start, end;  
    vector<PI> lectures;
    lectures.reserve(N); 
    for(int i = 0; i < N; i++){
        cin >> start >> end;
        lectures.emplace_back(start, end); 
    }
    sort(lectures.begin(), lectures.end(), compare);
    priority_queue<int, vector<int>, greater<int>> classRoom; 
    classRoom.push(lectures[0].second); 
    for(int i = 1; i < lectures.size(); i++){
        if(classRoom.top() <= lectures[i].first){
            classRoom.pop(); 
        }
        classRoom.push(lectures[i].second); 
    }

    cout << classRoom.size() << endl;
    return 0; 
}