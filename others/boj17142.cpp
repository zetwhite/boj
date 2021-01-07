#include <iostream> 
#include <algorithm> 
#include <vector> 
#include <queue> 
using namespace std; 

typedef pair<int, int> coo;  
const int MAX = 50; 
const int INVALID = 1000'000; 

int N; 
int M;
int map[MAX + 2][MAX + 2];
vector<coo> virus; 
coo dir[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; 

coo operator+ (coo& c1, coo& c2){
  return {c1.first + c2.first, c1.second + c2.second}; 
}

void init(){
  for(int i = 0; i <= N + 1; i++){
    map[i][0] = 1; 
    map[i][N+1] = 1; 
    map[0][i] = 1; 
    map[N+1][i] = 1; 
  }
}

void combination(vector<vector<int>>& result, int n, int k, int idx, vector<int> carrier){
  if(carrier.size() == k){
    result.push_back(carrier); 
    return; 
  }
  else if(idx == n)
    return; 
  else{
    carrier.push_back(idx); 
    combination(result, n, k, idx+1, carrier); 
    carrier.pop_back(); 

    combination(result, n, k, idx+1, carrier); 
  }
  return; 
}

int BFS(const vector<int>& picks){
  int visited[N+2][N+2]; 
  for(int i = 0; i <= N+1; i++){
    for(int j = 0; j <= N+1; j++){
      if(map[i][j] == 1)
        visited[i][j] = -1; 
      else
        visited[i][j] = 0; 
    }
  }

  queue<coo> storage; 
  for(int i = 0; i <picks.size(); i++){
    coo v = virus[picks[i]]; 
    storage.push(v);  
    visited[v.first][v.second] = 1; 
  }

  while(!storage.empty()){
    coo current = storage.front(); 
    storage.pop(); 
    int step = visited[current.first][current.second]; 

    for(int i = 0; i < 4; i++){
      coo next = current + dir[i]; 
      if(visited[next.first][next.second] == 0){
        visited[next.first][next.second] = step + 1; 
        storage.push(next); 
      }
    }
  }

  /*cout << "===================================================" << endl; 
  for(int i = 0; i <= N+1; i++){
    for(int j = 0; j <= N+1; j++){
      cout << visited[i][j] << "\t"; 
    }
    cout << endl; 
  }*/

  for(int i = 0; i < virus.size(); i++){
    coo v = virus[i]; 
    visited[v.first][v.second] = 1; 
  }

  int max = 0; 
  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
      if(visited[i][j] == 0){
        return INVALID; 
      }
      if(visited[i][j] > max)
        max = visited[i][j]; 
    }
  }

  /*cout << "===========================" << endl; 
  cout << max << endl; 
  cout << "=============================" << endl; 
  for(int i = 0; i <= N+1; i++){
    for(int j = 0; j <= N+1; j++){
      cout << visited[i][j] << "\t"; 
    }
    cout << endl; 
  }*/
  return max; 
}

int main(){
  cin >> N >> M; 
  init(); 
  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
      cin >> map[i][j]; 
      if(map[i][j] == 2)
        virus.emplace_back(i, j); 
    }
  }

  vector<vector<int>> picks; 
  vector<int> tmp; 

  combination(picks, virus.size(), M, 0, tmp); 
  /*for(int i = 0; i < picks.size(); i++){
    for(int j = 0; j < picks[i].size(); j++){
      cout << picks[i][j] << ", "; 
      }
    cout << endl; 
  }*/

  int min = INVALID; 
  for(int i = 0; i < picks.size(); i++){
    int local = BFS(picks[i]); 
    if( min > local )
      min = local; 
  }
  if(min == INVALID)
    cout << -1 << endl; 
  else
      cout << min  - 1 << endl; 

  return 0; 
}