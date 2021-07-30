#include <iostream> 
#include <algorithm>
#include <climits> 
#include <vector> 
using namespace std; 

pair<int,int> configGap(vector<int>& ns){
  pair<int,int> res = {INT_MAX, INT_MIN}; //minGap, maxGap 
  int gap; 
  for(int i = 0; i < ns.size()-1; i++){
    gap = ns[i+1] - ns[i]; 
    if(gap < res.first)
      res.first = gap; 
    if(gap > res.second)
      res.second = gap; 
  }

  /*if(res.first - res.second > 4)
    return {-1, -1};*/ 
  return res; 
}

int getSequence(int start, int gap, vector<int>& ns){
  int cnt = 0; 
  int target; 
  int t; 
  for(int i = 0; i < ns.size(); i++){
    int target = start + gap * i; 
    int t = abs(target - ns[i]); 
    if(t > 1)
      return INT_MAX; 
    cnt += t;  
  }
  return cnt; 
}


int main(){
  int N; 
  cin >> N; 
  vector<int> ns; 
  int n; 
  for(int i = 0; i < N; i++){
    cin >> n; 
    ns.emplace_back(n); 
  }

  if(N == 1){
    cout << "0" << endl; 
    return 0; 
  }
  pair<int, int> gaps = configGap(ns); 
  
  if(gaps.second - gaps.first > 4){
    cout << "-1" << endl; 
    return 0; 
  }
  if(gaps.second == gaps.first){
    cout << "0" << endl; 
    return 0; 
  }

  int min = INT_MAX; 
  for(int i = ns[0]-1; i <= ns[0] + 1; i++){
    for(int j = gaps.second; j >= gaps.first; j--){ 
      int _min = getSequence(i, j, ns); 
      if(min > _min)
        min = _min; 
    }
  }
  if(min == INT_MAX)
    cout << "-1" << endl; 
  else 
    cout << min << endl; 

  return 0; 
}