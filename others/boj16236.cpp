#include <iostream> 
#include <vector> 
#include <algorithm>  
#include <queue> 
using namespace std; 

typedef pair<int, int> coo; 
const int MD = 100; 
int map[20][20];       //BFS용 지도(물고기 크기 )
vector<coo> fishes[7]; //1-6 크기인 물고기 
int sharkSize = 2;     // 상어크기 
int N; 
coo shark;             //상어 위치 

coo dir[4] = {coo(1, 0), coo(-1, 0), coo(0, 1), coo(0, -1)}; 

coo operator+ (coo& a, coo& b){
  return coo(a.first + b.first , a.second + b.second); 
}

ostream& operator<< (ostream& os, coo& c){
  os << "(" << c.first << ", " << c.second << ")"; 
  return os; 
}

void printCanEat(vector<pair<coo, int>>& canEat){
  cout << "==================================" << endl; 
  for(int i = 0; i < canEat.size(); i++){
    cout << "( " << canEat[i].first.first <<  " ," << canEat[i].first.second << ") - dist[" << canEat[i].second  << "] " << endl; 
  }
}


int getDistance(coo& start, coo& end, int size, bool debug = false){
  int visited[20][20]; 
  for(int i = 0; i < N; i++){
    for(int j = 0;j < N; j++){
      if(map[i][j] <= size){
        visited[i][j] = -1;  //can go 
      }
      else{
        visited[i][j] = -2; //can not go 
      }
    }
  }

  queue<coo> next; 
  visited[start.first][start.second] = 0; 
  next.push(start); 

  while(!next.empty()){
    coo here = next.front();
    int hereStep = visited[here.first][here.second]; 
    next.pop();
    if(debug){
      cout << "=========" << start  << " => " << end << "================" << endl; 
      for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
          cout << visited[i][j]  << "\t"; 
        }
        cout << endl; 
      }
    } 
    for(int i = 0; i < 4; i++){
      coo n = here + dir[i];  
      if(!(0 <= n.first && n.first < N && 0 <= n.second && n.second < N)) //wrong coo 
        continue; 
      if(visited[n.first][n.second] == -2) //can not go 
        continue; 
      if(visited[n.first][n.second] != -1) //already visited 
        continue; 
      visited[n.first][n.second] = hereStep + 1;
      if(n.first == end.first && n.second == end.second){
        return hereStep + 1;  
      }
      next.push(n); 
    }
  }
  return MD; 
}

bool compare(pair<coo, int>& a, pair<coo, int>& b){
  int distanceA = a.second; 
  int distanceB = b.second; 
  if(distanceB < distanceA)
    return true; 
  else if(distanceB > distanceA)
    return false; 
  else {
    coo cooA = a.first; 
    coo cooB = b.first; 
    if(cooB.first < cooA.first)
      return true; 
    else if(cooB.first > cooA.first)
      return false; 
    else{
      return (cooB.second < cooA.second); 
    }
  }
}

int updateShark(vector<pair<coo, int>>& canEat){
  if(canEat.empty() == true){
    return -1; 
  }
  sort(canEat.begin(), canEat.end(), compare); 
  //printCanEat(canEat);
  coo newPoint = canEat.back().first; 
  //cout << "new point = " << newPoint.first << ", " << newPoint.second << endl; 
  int dist = canEat.back().second; 
  
  shark = newPoint; 
  map[newPoint.first][newPoint.second] = 0; 
  canEat.pop_back(); 
  return dist; 
}

void updateCanEat(vector<pair<coo, int>>& canEat, int size){
  if(size >= 6)
    size = 6; 
  for(int i = 0; i < canEat.size(); i++){
    canEat[i].second = getDistance(canEat[i].first, shark, sharkSize, true); 
  }

  for(int i = 1; i <= size; i++){
    auto it = fishes[i].begin(); 
    while(it != fishes[i].end()){
      int dist; 
      if((dist = getDistance(*it, shark, sharkSize)) != MD){
        canEat.push_back({*it, dist}); 
        it = fishes[i].erase(it); 
      }
      else
        it++;   
    }
  }
}

int main(){

  vector<pair<coo, int>> canEat;  //물고기 위치, 그 물고기 까지 거리 
  cin >> N; 
  int input;

  for(int x = 0; x < N; x++){
    for(int y = 0; y < N; y++){
      cin >> input; 
      if(input == 0){
        map[x][y] = 0; 
        continue; 
      }
      else if(input == 9){
        map[x][y] = 0; 
        shark.first = x; 
        shark.second = y; 
        continue; 
      }
      else{
        map[x][y] = input; 
        fishes[input].emplace_back(x, y); 
      }
    }
  }

  updateCanEat(canEat, 1); 
 // printCanEat(canEat); 

  int second = 0; 
  int level = 0;
  int s;  


  while((s = updateShark(canEat)) != -1){
    second += s; 
    level++; 
    if(level == sharkSize){
      sharkSize++; 
      level = 0; 
    }
    updateCanEat(canEat, sharkSize - 1);  
  } 

  cout << second << endl; 
  return 0; 
}