#include <iostream> 
#include <vector> 
using namespace std; 

int R, C; 

class Shark{
public : 
  int r; 
  int c;
  int speed;  
  int dir; 
  int size; 
  bool moved; 
  Shark(int _r, int _c, int _s, int _d, int _z)
  :r(_r), c(_c), speed(_s), dir(_d), size(_z), moved(false){}
  void calcLocation(){
    
    if(dir == 1 || dir == 2){ //1 - go up, 2 - down 
      int RR = R - 1 ; 
      int currentState; 
      if(dir == 1)
        currentState = RR*2 - r ;  
      else 
        currentState = r; 

      int nextState = ( currentState + speed ) % ( RR * 2 ); 
      if(nextState >= RR){
        dir = 1; //go up 
        r = RR*2 - nextState; 
      }
      else{
        dir = 2; //go down
        r = nextState; 
      }
    }

    if(dir == 3 || dir == 4){  // 3 - right, 4-left 
      int CC = C - 1; 
      int currentState; 
      if(dir == 3)
        currentState = c; 
      else 
        currentState = CC*2 - c; 

      int nextState = (currentState + speed) % (CC*2); 
      if(nextState >= CC){
        dir = 4; 
        c = CC*2 - nextState; 
      }
      else{
        dir = 3; 
        c = nextState; 
      }
    }
  }
}; 

Shark* map[101][101]; 

void initMap(){
  for(int i = 0; i < R; i++){
    for(int j = 0; j < C; j++){
      map[i][j] = nullptr; 
    }
  }
}

int catchShark(int where){
  int size = 0; 
  for(int r = 0; r < R; r++){
    if(map[r][where] != nullptr){
      size = map[r][where]->size; 
      delete map[r][where]; 
      map[r][where] = nullptr; 
      break; 
    }
  }
  return size; 
}

void move(Shark* s){
  //Shark* s = map[r][c]; 
  s -> calcLocation(); 
  //map[r][c] = nullptr; 

  Shark* next = map[s->r][s->c];
  if(next == nullptr){
    map[s->r][s->c] = s; 
    s->moved = true; 

  } 
  else if(next != nullptr && next->moved == false){
    s->moved = true; 
    map[s->r][s->c] = s; 
    move(next); 
  } 
  else if(next != nullptr && next->moved == true){
    if(next->size > s->size){
      delete s;
    }
    else{
      delete next; 
      map[s->r][s->c] = s; 
      s->moved = true; 
    }
  }
}


void moveSharks(){
  for(int i = 0; i < R; i++){
    for(int j = 0; j < C; j++){
      Shark* s = map[i][j]; 
      if(s == nullptr)
        continue; 
      if(s->moved == true)
        continue; 
      map[i][j] = nullptr; 
      move(s); 
    }
  }
}

void resetMoved(){
  for(int i = 0; i < R; i++){
    for(int j = 0; j < C; j++){
      if(map[i][j] != nullptr) 
        map[i][j]->moved = false; 
    }
  }
}

void print(){
  cout << "===================================" << endl;
  for(int i = 0; i < R; i++){
    for(int j = 0; j < C; j++){
      if(map[i][j] == nullptr)
        cout << "0" <<"\t"; 
      else
        cout << map[i][j]->size << "\t"; 
    }
    cout << endl; 
  }
}

int main(){
  int M; 
  //vector<Shark*> sharks; 
  cin >> R >> C >> M; 
  int r, c, s, d, z; 
  
  for(int i = 0; i < M; i++){
    cin >> r >> c >> s >> d >> z;  
    r--; 
    c--; 
    if(r == R-1 && d == 2)
      d = 1; 
    if(r == 0 && d == 1)
      d = 2; 
    if(c == C-1 && d == 3)
      d = 4; 
    if(c == 0 && d == 4)
      d = 3;    
    map[r][c] = new Shark(r, c, s, d, z); 
  }

  //print(); 

  int sum = 0; 
  for(int t = 0; t < C; t++){
    sum += catchShark(t); 
    moveSharks(); 
    //print(); 
    resetMoved(); 
  }
  cout << sum << endl; 
  return 0; 
}