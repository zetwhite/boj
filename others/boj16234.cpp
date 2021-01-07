#include <iostream> 
#include <vector> 
using namespace std; 

bool fence[50][50][2]; //0(->), 1(to down) 
bool visited[50][50]; 
int population[50][50]; 

void initFance(int N){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      fence[i][j][0] = true; 
      fence[i][j][1] = true; 
    }
  }
}

void initVisited(int N){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      visited[i][j] = false; 
    }
  }
}

void getPopulation(int N){
  for(int i = 0 ; i < N; i++){
    for(int j = 0; j < N; j++){
      cin >> population[i][j]; 
    }
  }
}

void printPopulation(int N){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      cout << population[i][j] << "\t"; 
    }
    cout << endl; 
  }
}

bool openFance(int N, int L, int R){
  bool changed = false; 
  for(int i = 0; i < N-1; i++){
    for(int j = 0; j < N - 1; j++){
      int diff1 = abs(population[i][j] - population[i][j+1]); 
      if( diff1 >= L && diff1 <= R){
        fence[i][j][0] = false; 
        changed = true; 
      }
      int diff2 = abs(population[i][j] - population[i+1][j]); 
      if(diff2 >= L && diff2 <= R){
        fence[i][j][1] = false; 
        changed = true; 
      }
    }
  }
  
  for(int i = 0; i < N-1; i++){
    int diff = abs(population[i][N-1] - population[i+1][N-1]); 
    if(diff >= L && diff <= R){
      fence[i][N-1][1] = false; 
      changed = true; 
    }
  }

  for(int i = 0; i < N-1; i++){
    int diff = abs(population[N-1][i] - population[N-1][i+1]); 
    if(diff >= L && diff <= R){
      fence[N-1][i][0] = false; 
      changed = true; 
    }
  }
  return changed; 
}

void getArea(int N, int x, int y, vector<pair<int, int>>& area, int& sum){
  visited[x][y] = true; 
  sum += population[x][y]; 
  area.emplace_back(x, y);  
  if(fence[x][y][0] == false){
    if( x < N && y + 1 < N && visited[x][y+1] == false)
      getArea(N, x, y+1, area, sum); 
  }
  if(fence[x][y][1] == false){
    if( x + 1 < N && y < N && visited[x+1][y] == false)
      getArea(N, x+1, y, area, sum); 
  }
  if(x >= 1){
    if(fence[x-1][y][1] == false && visited[x-1][y] == false){
      getArea(N, x-1, y, area, sum); 
    }
  }
  if(y >= 1){
    if(fence[x][y-1][0] == false && visited[x][y-1] == false)
      getArea(N, x, y-1, area, sum); 
  }
}

void movePopulation(int N){
  initVisited(N); 

  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      if(visited[i][j]) 
        continue; 
      
      int sum = 0; 
      vector<pair<int, int>> area; 
      getArea(N, i, j, area, sum); 
      int aSize = area.size(); 
      for(int k = 0; k < aSize; k++){
        population[area[k].first][area[k].second] = sum / aSize; 
      }

    }
  }
  //cout << "===============================" << endl; 
  //printPopulation(N); 
}

int main(){
  int N, L, R; 
  cin >> N >> L >> R; 
  initFance(N); 
  getPopulation(N); 

  int changedCnt = 0; 
  while(openFance(N, L, R)){
    changedCnt++; 
    movePopulation(N); 
    initFance(N); 
  }

  cout << changedCnt << endl; 
  return 0; 
}