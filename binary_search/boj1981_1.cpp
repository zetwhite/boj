#include <iostream> 
#include <algorithm>
#include <queue>
#include <set> 
using namespace std; 

int arr[105][105]; 
bool visit[105][105]; 
set<int> nums;  
int N; 

pair<int, int> dir[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}; 

pair<int, int> operator+ (pair<int, int> a, pair<int, int> b){
  return {a.first + b.first, a.second + b.second}; 
}

bool isPossible(int limitMin, int limitMax){
  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
      visit[i][j] = false; 
    }
  }
  if(limitMin > arr[1][1] || arr[1][1] > limitMax)
    return false; 

  queue<pair<int, int>> q; 
  q.push({1, 1});
  
  pair<int,int> here, next;  
  while(!q.empty()){
    here = q.front(); 
    q.pop(); 
    for(int i = 0; i < 4; i++){
      next = here + dir[i]; 
      if( limitMin > arr[next.first][next.second] || arr[next.first][next.second] > limitMax)
        continue; 
      if(visit[next.first][next.second] == false){
        visit[next.first][next.second] = true; 
        if(next.first == N && next.second == N){
          return true; 
        }
        q.push(next); 
      }
    }
  }
  return false; 
}

int findMinGap(int limitMin, int limitMax){
  int maxLeft = limitMin - 1; 
  int maxRight = limitMax;
  int mid = 0;
  while(1){
    mid = (maxLeft + maxRight) / 2; 
    if(maxLeft == maxRight || maxLeft + 1 == maxRight)
      break; //maxRight is min possible gap 
    if(isPossible(limitMin, mid))
      maxRight = mid; //go fewer  
    else
      maxLeft = mid; 
  }
  return maxRight; 
}


int main(){
  cin >> N; 

  int _max = 0; 
  int _min = 20000; 
  for(int i = 0; i <= N+1; i++){
    arr[i][0] = 50000; 
    arr[i][N+1] = 50000; 
  }
  for(int i = 0; i <= N+1; i++){
    arr[0][i] = 50000; 
    arr[N+1][i] = 50000; 
  }
  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
      cin >> arr[i][j]; 
      nums.insert(arr[i][j]); 
      _min = min(arr[i][j], _min); 
      _max = max(arr[i][j], _max);
    }
  }

  int res = _max - _min; 
  for(auto i:nums){
    if(isPossible(i, _max) == false)
      continue; 
    int _gap = findMinGap(i, _max) - i; 
    if(res > _gap)
      res = _gap; 
  }
  cout << res << endl; 
  return 0; 
}