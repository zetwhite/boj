#include <iostream> 
#include <vector> 
#include <cmath> 
#include <queue> 
using namespace std; 
typedef pair<int, int> coo; 
int map[100][100]; 
bool operator== (const coo& a, const coo& b){
  return (a.first == b.first && a.second == b.second);  
}

coo operator+ (const coo& a, const coo& b){
  return {a.first + b.first, a.second + b.second}; 
}

ostream& operator<< (ostream& os, const coo& a){
  os << "(" << a.first << ", " << a.second << ")"; 
  return os; 
}

int N, Q, SZ; 
vector<int> Levels; 
coo DIR[4] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

void getMap(){
  for(int i = 0; i <= SZ + 1; i++){
    map[i][0] = -1; 
    map[i][SZ+1] = -1;
    map[0][i] = -1;
    map[SZ+1][i] = -1; 
  }
  for(int i = 1; i <= SZ; i++){
    for(int j = 1; j <= SZ; j++){
      cin >> map[i][j]; 
    }
  } 
}

void rotate(int x, int y, int levelSZ){
  vector<int> tmp; 
  for(int i = 0; i < levelSZ - 1; i++)
    tmp.push_back(map[x][y+i]); 
  for(int i = 0; i < levelSZ - 1; i++)
    tmp.push_back(map[x+i][y+levelSZ-1]);
  for(int i = 0; i < levelSZ - 1; i++)
    tmp.push_back(map[x+levelSZ-1][y+levelSZ-1-i]);
  for(int i = 0; i < levelSZ-1; i++)
    tmp.push_back(map[x+levelSZ-1-i][y]); 

  int idx = 0; 
  for(int i = 0; i < levelSZ - 1; i++)
    map[x+i][y+levelSZ-1] = tmp[idx++]; 
  for(int i = 0; i < levelSZ -1; i++)
    map[x+levelSZ-1][y+levelSZ-1-i] = tmp[idx++]; 
  for(int i = 0; i < levelSZ-1; i++)
    map[x+levelSZ-1-i][y] = tmp[idx++];  
  for(int i = 0; i < levelSZ - 1; i++)
    map[x][y+i] = tmp[idx++]; 
}

void localFireStorm(int x, int y, int level){
  int MaxSZ = pow(2, level); 
  for(int i = 0; i < MaxSZ/2; i++){
    rotate(x, y, MaxSZ-i*2);
    x++; 
    y++;  
  }
}

void fireStorm(int level){
  int unit = pow(2, level); 
  for(int i = 1; i <= SZ; i = i + unit){
    for(int j = 1; j <= SZ; j = j + unit){
      localFireStorm(i, j, level); 
    }
  }
}

void melting(){
  bool meltPoint[100][100]; 
  for(int i = 1; i <= SZ; i++){
    for(int j = 1; j <= SZ; j++){
      meltPoint[i][j] = false; 
    }
  }

  int notIce = 0;
  for(int i = 1; i <= SZ; i++){
    for(int j = 1; j <= SZ; j++){
      int notIce = 0; 
      if(map[i][j] <= 0)
        continue; 
      for(int d=0; d<4; d++){
        if(map[i+DIR[d].first][j+DIR[d].second] <= 0)
          notIce++; 
      }
      if(notIce >= 2)
        meltPoint[i][j] = true; 
    }
  }

  for(int i = 1; i <= SZ; i++){
    for(int j = 1; j <= SZ; j++){
      if(meltPoint[i][j])
        map[i][j]--; 
    }
  }
}

int countIce(){
  int cnt = 0; 
  for(int i = 1; i <= SZ; i++){
    for(int j = 1; j <= SZ; j++){
      if(map[i][j] > 0)
        cnt += map[i][j]; 
    }
  }
  return cnt; 
}

int findIceBall(int x, int y){
  vector<coo> land; 
  queue<coo> storage; 
  if(map[x][y] <= 0)
    return 0; 
  map[x][y] = 0; 
  land.emplace_back(x, y); 
  storage.push({x, y}); 
  while(storage.empty() == false){
    coo here = storage.front(); 
    storage.pop(); 
    for(int d = 0; d < 4; d++){
      coo next = here + DIR[d]; 
      if(map[next.first][next.second] > 0){
        storage.push(next); 
        land.push_back(next); 
        map[next.first][next.second] = 0; 
      }
    }
  }
  return land.size(); 
}


int main(){
  cin >> N >> Q; 
  SZ = pow(2, N);   
  getMap(); 
  int l; 
  for(int i = 0; i < Q; i++){
    cin >> l; 
    fireStorm(l);
    melting(); 
  }
  cout << countIce() << endl; 

  int max = 0; 
  for(int i = 1; i <= SZ; i++){
    for(int j = 1; j <= SZ; j++){
      int loc = findIceBall(i, j);
      if(loc > max)
        max = loc; 
    }
  }
  cout << max << endl; 
  return 0; 
}