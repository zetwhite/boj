#include <iostream> 
#include <algorithm> 
#include <vector> 
#include <list> 
using namespace std; 

typedef pair<int, int> coo; 
coo DIR[8] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}; 
bool operator== (const coo& a, const coo& b){
  return (a.first == b.first && a.second == b.second);  
}

coo operator* (const coo& c, int i){
  return {c.first*i, c.second*i}; 
}

coo operator+ (const coo& a, const coo& b){
  return {a.first + b.first, a.second + b.second}; 
}

ostream& operator< (ostream& os, const coo& a){
  os << "(" << a.first << ", " << a.second << ")"; 
  return os; 
}

class FireBall{
public: 
  int m; 
  int s; 
  int d; 
  bool moved; 
  FireBall(int _m, int _s, int _d):m(_m), s(_s), d(_d), moved(false){}
};

ostream& operator<< (ostream& os, FireBall& fb){
  os << "fb[" << fb.m << ", " << fb.s << ", " << fb.d << "]"; 
  return os; 
}

list<FireBall*> map[50][50]; 
int N, M, K;

coo trim(coo c){
  while(c.first < 0 || c.first >= N){
    c.first = (c.first + N) % N; 
  }
  while(c.second < 0 || c.second >= N){
    c.second = (c.second + N) % N; 
  }
  return c; 
}

void MoveAllBalls(){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      auto it = map[i][j].begin(); 
      while(it != map[i][j].end()){
        (*it)->moved = false; 
        it++; 
      }
    }
  }

  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
    
      auto it = map[i][j].begin(); 
      while(it != map[i][j].end()){
        FireBall* fb = (*it); 
        if(fb->moved){
          it++; 
          continue; 
        }  
        map[i][j].erase(it++); 
        fb->moved = true; 
        coo next = trim(make_pair(i, j) + (DIR[fb->d]*fb->s)); 
        map[next.first][next.second].push_back(fb); 
      }
    }
  }
}

void FuseFireBall(){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      if(map[i][j].size() <= 1)
        continue; 

      int fuseM = 0; 
      int fuseS = 0; 
      //int fuseD = 0;
      bool alldEven = true; 
      bool alldOdd = true; 
      int cnt = 0;  
      auto it = map[i][j].begin(); 
      while(it != map[i][j].end()){
        FireBall* fb = (*it); 
        fuseM += fb->m;  
        fuseS += fb->s; 
        if(fb->d % 2 == 0)
          alldOdd = false; 
        else
          alldEven = false; 
        cnt++; 
        it++; 
      }
      map[i][j].clear(); 

      int newM = fuseM / 5; 
      int newS = fuseS / cnt; 
      if(newM == 0)
        continue; 
      for(int t = 0; t < 4; t++){
        if(alldEven || alldOdd)
          map[i][j].push_back(new FireBall(newM, newS, t * 2)); 
        else
          map[i][j].push_back(new FireBall(newM, newS, t * 2 + 1)); 
      }
    }
  }
}

void print(){
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl; 
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      if(map[i][j].empty()){
        cout << "-----" << "\t\t"; 
      }
      else{
        auto it = map[i][j].begin(); 
        while(it != map[i][j].end()){
          cout << *(*it) << ", "; 
          it++; 
        }
        cout << "\t\t"; 
      }
    }
    cout << endl; 
  }
}

int getMess(){
  int mess = 0; 
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      if(map[i][j].empty())
        continue; 
      auto it = map[i][j].begin(); 
      while(it != map[i][j].end()){
        mess += (*it)->m; 
        it++; 
      }
    }
  }
  return mess; 
}

int main(){

  cin >> N >> M >> K; 
  int r, c, m, s, d; 
  for(int i = 0; i < M; i++){
    cin >> r >> c >> m >> s >> d; 
    map[r-1][c-1].push_back(new FireBall(m, s, d)); 
  }

  //print(); 
  for(int k = 0; k < K; k++){
    MoveAllBalls(); 
    //print(); 
    FuseFireBall(); 
    //print(); 
  }
  cout << getMess() << endl; 
  return 0; 
}