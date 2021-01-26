#include <string>
#include <vector>
#include <algorithm> 
#include <unordered_map>
#include <set> 
#include <iostream> 

using namespace std;

bool cmp(set<int>& a, set<int>& b){
  return a.size() > b.size(); 
}

int findMax(unordered_map<int, set<int>>& connect){
  int maxInt = 0; 
  int maxSz = 0; 
  for(auto it : connect){
    if(it.second.size() > maxSz){
      maxSz = it.second.size(); 
      maxInt = it.first; 
    }
  }
  return maxInt; 
}

int solution(vector<vector<int>> routes) {
    int answer = 0;
    int sz = routes.size() * 2; 
    unordered_map<int, set<int>> connect; 
    for(int i = 0; i < routes.size() * 2; i++){
      int q = i/2; 
      int l = i%2; 
      for(int k = 0; k < routes.size(); k++){
        if(routes[k][0] <= routes[q][l] && routes[q][l] <= routes[k][1])
          connect[i].insert(k); 
      }
    } 
    //sort(connect, connect + sz, cmp); 
    while(!connect.empty()){
      int idx = findMax(connect); 
      set<int> del = connect[idx]; 
      for(auto i : del){
        connect[i].clear(); 
      }
      for(int i = 0; i < sz; i++){
        if(connect.find(i) == connect.end())
          continue; 
        for(auto j : del){
          cout << "at = " << i << ", del = " << j << endl; 
          auto f = connect[i].find(j); 
          if(f != connect[i].end())
           connect[i].erase(f); 
        }
      }
      answer++; 
    }
    return answer;
}

int main(){
  int n; 
  vector<vector<int>> v; 
  cin >> n; 
  for(int i = 0; i < n; i++){
    int a, b; 
    cin >> a >> b; 
    vector<int> tmp; 
    tmp.push_back(a); 
    tmp.push_back(b); 
    v.push_back(tmp); 
  }
  cout << solution(v) << endl; 
  return 0; 
}