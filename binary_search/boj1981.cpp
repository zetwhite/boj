#include <iostream> 
#include <algorithm>
#include <cstring> 
using namespace std; 

int arr[105][105]; 
bool visit[105][105]; 
int N; 

inline bool isFine(int x, int y, int& _min, int& _max, bool _v[105][105], int limit){
  
  if(_v[x][y]){
    //////cout << "(" << x << "," << y << ") "; 
    //////cout << "already visited " << endl; 
    return false; 
  }

  int next = arr[x][y]; 
  if(next < _min){
    if(_max - next > limit){
      // ////cout << "(" << x << "," << y << ") "; 
      // ////cout << "min limit over" << endl;     
      return false; 
    }
    _min = next; 
  }

  if(next > _max){
    if(next - _min > limit){
      // ////cout << "(" << x << "," << y << ") "; 
      // ////cout << " max limit over" << endl; 
      return false; 
    }
    _max = next; 
  }

  _v[x][y] = true; 
  return true;
}

bool dfs(int x, int y, int _min, int _max, bool v[105][105], int limit){
  if(x == N && y == N)
    return true;

  int pmin = _min; 
  int pmax = _max; 
  //cout << "(" << x << ", " << y << ")"; 
  bool _v[105][105]; 
  memcpy(_v, v, sizeof(_v)); 

  bool res1 = false; 
  if(isFine(x+1, y, _min, _max, _v, limit)){
    res1 = dfs(x+1, y, _min, _max,_v, limit); 
    _min = pmin; _max = pmax; 
    _v[x+1][y] = false; 
  }
  if(res1) return true; 

  bool res3 = false; 
  if(isFine(x, y+1, _min, _max, _v, limit)){
    res3 = dfs(x, y+1, _min, _max,_v, limit); 
    _min = pmin; _max = pmax; 
    _v[x][y+1] = false; 
  }
  if(res3) return true; 

  bool res2 = false; 
  if(isFine(x-1, y, _min, _max, _v, limit)){
    res2 = dfs(x-1, y, _min, _max,_v, limit); 
    _min = pmin; _max = pmax; 
    _v[x-1][y] = false;     
  }
  if(res2) return true; 

  bool res4 = false;
  if(isFine(x, y-1, _min, _max, _v, limit)){
    res4 = dfs(x, y-1, _min, _max,_v, limit); 
  }
  if(res4) return true; 
  return false; 
}

bool isPossible(int limit){
  visit[1][1] = true; 
  return dfs(1, 1, arr[1][1], arr[1][1], visit, limit); 
}


int biSearch(int min, int max){
  if(min == max || min + 1 == max)
    return max; 
  int mid = (min + max)/2; 

  //cout << "try (" << min << ", " << max << ") = " << mid << endl; 
  if(isPossible(mid))
    return biSearch(min, mid); 
  else
    return biSearch(mid, max); 
}

int main(){
  cin >> N; 
  int _min = 20000; 
  int _max = 0; 

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
      visit[i][j] = false; 
    }
  }

  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
      cin >> arr[i][j]; 
      _min = min(arr[i][j], _min); 
      _max = max(arr[i][j], _max);
    }
  }
  cout << biSearch(0, _max - _min) << endl; 
  return 0; 
}