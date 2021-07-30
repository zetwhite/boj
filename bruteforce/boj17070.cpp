#include <iostream> 
#include <algorithm>
#include <climits> 
#include <vector> 
using namespace std; 

#define HORI 1
#define VERTI 2 
#define DIA 3 

class NextPos{
public: 
  virtual pair<int, int> getNext(int N, int** arr, int& dir, pair<int, int> pos) = 0; 
}; 

class NextHori : public NextPos{
public : 
  pair<int, int>  getNext(int N, int** arr, int& dir, pair<int, int> pos) {
    pair<int, int>  newPos = {pos.first , pos.second + 1}; 
    if(arr[newPos.first][newPos.second] == 1)
      return {-1, -1}; 
    dir = HORI; 
    return newPos; 
  }
}; 

class NextVerti : public NextPos{
public : 
  pair<int, int>  getNext(int N, int** arr, int& dir, pair<int, int> pos){
    pair<int, int>  newPos = {pos.first + 1 , pos.second}; 
    if(arr[newPos.first][newPos.second] == 1)
      return {-1, -1}; 
    dir = VERTI; 
    return newPos; 
  }
}; 

class NextCross: public NextPos{
public : 
  pair<int, int>  getNext(int N, int** arr, int& dir, pair<int, int> pos){
    vector<pair<int, int>> nexts = {{0, 1}, {1, 0}, {1, 1}}; 
    for(int i = 0; i < nexts.size(); i++){
      pair<int, int> newPos = { pos.first + nexts[i].first, pos.second + nexts[i].second }; 
      if ( arr[newPos.first][newPos.second] == 1)
        return {-1, -1}; 
    }
    dir = DIA;
    return { pos.first + 1, pos.second + 1}; 
  }
}; 

NextHori nexthori; 
NextVerti nextverti; 
NextCross nextcross; 
vector<NextPos*> hori, verti, cross; 
int way = 0; 

void DFS(int dir, pair<int,int> pos, int** arr, int N, int count){
  if(pos.first == N && pos.second == N){
    way++; 
  }
  int newDir; 
  pair<int, int> newPos; 
  int totalCount = INT_MAX; 
  if(dir == HORI){
    // newDir = HORI; 
    for(int i = 0; i < hori.size(); i++){
      newPos = hori[i]->getNext(N, arr, newDir, pos);
      if(newPos.first != -1)
        DFS(newDir, newPos, arr, N, count+1);  
    }
  }
  else if(dir == VERTI){
    for(int i = 0; i < verti.size(); i++){
      newPos = verti[i]->getNext(N, arr, newDir, pos);
      if(newPos.first != -1)
        DFS(newDir, newPos, arr, N, count+1);  
    }
  }
  else{
    for(int i = 0; i < cross.size(); i++){
      newPos = cross[i]->getNext(N, arr, newDir, pos);
      if(newPos.first != -1)
        DFS(newDir, newPos, arr, N, count+1);  
    }
  }
}

int main(){
  int N; 
  cin >> N; 
  hori = {&nexthori, &nextcross}; 
  verti = {&nextverti, &nextcross}; 
  cross = {&nexthori, &nextverti, &nextcross}; 


  int pipeDIR = HORI; 
  pair<int, int> pipePosition = {1, 2}; 

  int** arr = new int*[N+2]; 
  for(int i = 0; i < N+2; i++){
    arr[i] = new int[N+2]; 
  }

  for(int i = 0; i <= N+1; i++){
    arr[0][i] = 1; 
    arr[N+1][i] = 1; 
  }
  for(int i = 0; i <= N+1; i++){
    arr[i][0] = 1; 
    arr[i][N+1] = 1; 
  }

  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
      cin >> arr[i][j]; 
    }
  }

  DFS(pipeDIR, pipePosition, arr, N, 0); 
  cout <<  way << endl; 
  return 0; 
}