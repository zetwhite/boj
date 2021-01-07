#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <list> 
//42% 시간초과

using namespace std; 

class UnitGround{
public: 
  list<int> aliveTree; 
  int nextSeed; 
  int nutrition; 
  UnitGround():nextSeed(0), nutrition(5){}; 

  inline void addTree(int age){
    aliveTree.push_front(age); 
  }

  inline void addTree(list<int> tmp){
    aliveTree.splice(aliveTree.begin(), tmp, tmp.begin(), tmp.end()); 
  }

  void passSpringSummar(bool sort = false){
    if(aliveTree.size() == 0)
      return; 
    if(sort)
      aliveTree.sort(); 
    list<int>::iterator it = aliveTree.begin(); 
    while(it != aliveTree.end()){
      if(nutrition >= *it){
        nutrition -= *it; 
        (*it)++; 
        if(((*it) % 5) == 0)
          nextSeed++; 
        it++;
      }
      else break; 
    }
    while(it != aliveTree.end()){
      nutrition += (*it)/2; 
      aliveTree.erase(it++); 
    }
  }

  inline int passAutumn(){
    return nextSeed; 
  }

  inline void passWinter(int nu){
    nextSeed = 0; 
    nutrition += nu; 
  }
}; 

UnitGround ground[10][10]; 
int neigborX[8] = {-1,  -1, -1,   0,  0,   1,  1,  1}; 
int neigborY[8] = {-1,  0,  +1,  -1, +1,   1, 0, -1 }; 
int newNutrition[10][10]; 


inline void getNutrition(int N){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      cin >> newNutrition[i][j]; 
    }
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL); 

  int N, M, K; 
  cin >> N >> M >> K; 
  getNutrition(N); 
  int x, y, age; 
  for(int i = 0; i < M; i++){
    cin >> x >> y >> age; 
    ground[x -1][y-1].addTree(age); 
  }

  bool sort = true; 
  for(int i = 0; i < K; i++){
    if(i != 0)
      sort = false; 
    for(int x = 0; x < N; x++){
      for(int y = 0; y < N; y++){
        ground[x][y].passSpringSummar(sort);
      }
    } 

    for(int x = 0; x < N; x++){
      for(int y = 0; y < N; y++){
        int seed = ground[x][y].passAutumn(); 
        ground[x][y].passWinter(newNutrition[x][y]); 
        
        if(seed == 0)
          continue; 
        list<int> tmp(seed, 1); 
        for(int d = 0; d < 8; d++){
          int nextx = neigborX[d] + x; 
          int nexty = neigborY[d] + y; 
          if(nextx >= 0 && nextx < N && nexty >= 0 && nexty < N){
            ground[nextx][nexty].addTree(tmp);       
          }
        }
      }
    }
  }

  int tree = 0; 
  for(int x = 0; x < N; x++){
    for(int y = 0; y < N; y++){
      tree += ground[x][y].aliveTree.size(); 
    }
  }
  cout << tree << "\n"; 
  return 0; 
}