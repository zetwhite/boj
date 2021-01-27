#include <string>
#include <vector>
#include <algorithm> 
#include <queue>

using namespace std;

bool cmp(vector<int>& a, vector<int>& b){
  return a[1] > b[1]; 
}

int solution(vector<vector<int>> routes) {
  int answer = 0; 
  sort(routes.begin(), routes.end(), cmp); 
  priority_queue<int, vector<int>,  less<int>> pq;
  int idx = 1; 
  pq.push(routes[0][0]); 
  for(; idx < routes.size(); idx++){
    int newLineStart = routes[idx][1]; 
    int newLineEnd = routes[idx][0]; 
    if( pq.top() > newLineStart ){
      answer++; 
      pq = priority_queue<int, vector<int>, less<int>>(); 
    }
    pq.push(routes[idx][0]); 
  }
  if(!pq.empty()){
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