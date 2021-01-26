#include <iostream> 
#include <algorithm> 
#include <map> 
#include <queue> 
#include <vector> 
#include <cstring> 
using namespace std; 

typedef pair<int, int> coo; 
int N, M, Fuel; 
int Map[22][22]; 
coo DIR[4] = {{0,1}, {1, 0}, {-1, 0}, {0, -1}}; 
map<coo, coo> Reqs; 
const int VACANT = 0; 
const int WALL = 1; 
const int GUEST = 2; 

bool operator== (const coo& a, const coo& b){
  return (a.first == b.first && a.second == b.second);  
}

coo operator+ (const coo& a, const coo& b){
  return {a.first + b.first, a.second + b.second}; 
}

bool operator< (const coo& a, const coo& b){
  if(a.first == b.first){
    return a.second < b.second; 
  }
  return a.first < b.first; 
}


void getMap(){
  for(int i = 0; i <= N+1; i++){
    Map[0][i] = WALL;
    Map[N+1][i] = WALL; 
    Map[i][0] = WALL; 
    Map[i][N+1] = WALL; 
  }
  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
      cin >> Map[i][j]; 
    }
  }
}

void getGuests(){
  coo src; 
  coo dest; 
  for(int i = 0; i < M; i++){
    cin >> src.first >> src.second; 
    cin >> dest.first >> dest.second; 
    Map[src.first][src.second] = GUEST; 
    Reqs.insert({src, dest}); 
  }
}

bool findNearestGuest(coo taxi, coo& guestCoo, int& dist){
  const int visited = -1; 
  int bfsMap[22][22]; 
  for(int i = 0; i <= N+1; i++)
    memcpy(bfsMap[i], Map[i], sizeof(int)*(N+2)); 

  queue<coo> storage; 
  vector<coo> found; 
  if(bfsMap[taxi.first][taxi.second] == GUEST){
    guestCoo = taxi; 
    dist = 0; 
    return true; 
  }
  storage.push(taxi); 
  bfsMap[taxi.first][taxi.second] = visited; 
  int distance = 1; 

  int size = storage.size(); 
  coo here, next; 
  while(1){
    for(int i = 0; i < size; i++){
      here = storage.front(); 
      storage.pop(); 

      for(int d = 0; d < 4; d++){
        next = here + DIR[d]; 
        int& nextResult = bfsMap[next.first][next.second]; 
        if(nextResult == WALL || nextResult == visited)
          continue; 
        if(nextResult == GUEST)
          found.push_back(next);
        nextResult = visited; 
        storage.push(next); 
      }
    }

    if(found.empty() == false) 
      break; 
    size = storage.size(); 
    distance++; 
    if(size == 0)
      break; 
  }
  
  if(found.empty())
    return false; 
  sort(found.begin(), found.end()); 
  guestCoo = found[0]; 
  dist = distance; 
  return true; 
}

bool calcDistance(coo start, coo dest, int& dist){
  int time = 0;  
  const int _wall = -1; 
  const int _vacant = 0; 
  int bfsMap[22][22]; 
  for(int i = 0; i <= N+1; i++){
    for(int j = 0; j <= N+1; j++){
      if(Map[i][j] == WALL)
        bfsMap[i][j] = _wall; 
      else
        bfsMap[i][j] = _vacant; 
    }
  }

  queue<coo> storage; 
  storage.push(start); 
  bfsMap[start.first][start.second] = time; 

  coo here, next; 
  while(storage.empty() == false){
    here = storage.front(); 
    int hTime = bfsMap[here.first][here.second]; 
    storage.pop(); 
    for(int d = 0; d < 4; d++){
      next = here + DIR[d]; 
      if(next == dest){
        dist = hTime + 1; 
        return true; 
      }
      if(bfsMap[next.first][next.second] == _vacant){
        bfsMap[next.first][next.second] = hTime + 1; 
        storage.push(next); 
      }
    }
  }
  return false; 
}

int main(){
  coo taxi; 
  cin >> N >> M >> Fuel; 
  getMap(); 
  cin >> taxi.first >> taxi.second; 
  getGuests(); 

  coo guest, dest; 
  int distance; 
  bool success = true; 
  while(Reqs.empty() == false){
    bool findRes = findNearestGuest(taxi, guest, distance); 
    if(!findRes){
      success = false;
      break; 
    }

    Fuel -= distance; 
    if(Fuel < 0){
      success = false; 
      break; 
    }
    taxi = guest; 
    dest = Reqs[guest];  

    bool distRes = calcDistance(taxi, dest, distance); 
    if(!distRes){
      success = false; 
      break; 
    }
    Reqs.erase(taxi); 
    Map[taxi.first][taxi.second] = VACANT;  
    Fuel -= distance; 
    if(Fuel < 0){
      success = false; 
      break; 
    }
    Fuel += distance*2; 
    taxi = dest; 
  }

  if(!success)
    cout << -1 << endl; 
  else
    cout << Fuel << endl; 
  return 0; 
}