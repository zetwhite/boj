#include <iostream> 
#include <algorithm>
#include <vector> 
#include <list>
using namespace std; 
typedef pair<int, int> coo; 

class Piece{
public: 
  coo dir; 
  coo location; 
  int num; 

  Piece(int x, int y, int d, int n)
  :location(x, y), num(n){
    if(d == 1)
      dir = {0, 1}; 
    if(d == 2)
      dir = {0, -1}; 
    if(d == 3)
      dir = {-1, 0}; 
    if(d == 4)
      dir = {1, 0}; 
  }
};

list<Piece*> pieceMap[14][14]; 
int colorMap[14][14]; 
int N; 
vector<Piece*> allPiece;  

void initColorMap(){
  for(int i = 0; i <= N+1; i++){
    colorMap[i][0] = 2; 
    colorMap[i][N+1] = 2; 
    colorMap[0][i] = 2; 
    colorMap[N+1][i] = 2; 
  }
}

list<Piece*>::iterator findIt(list<Piece*>& l, Piece* p){
  auto it = l.begin(); 
  while(it != l.end()){
    if(*it == p)
      return it; 
    it++; 
  }
  return it; 
}

coo operator + (const coo& c1, const coo& c2){
  return { c1.first + c2.first, c1.second + c2.second }; 
}

coo operator * (int i, coo& c){
  return {c.first*i, c.second * i}; 
}

void print(){
  cout << "==============================" << endl; 
  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
      cout << pieceMap[i][j].size(); 
      cout << "("; 
      for(auto it = pieceMap[i][j].begin(); it != pieceMap[i][j].end(); it++)
        cout << (*it)->num << ", "; 
      cout << ")" << "\t";
    }
    cout << endl; 
  }
}

bool move(Piece* p){
  coo next = p->location + p->dir; 
  list<Piece*>& hList = pieceMap[p->location.first][p->location.second]; 
  list<Piece*>& nList = pieceMap[next.first][next.second]; 
  auto listNode = findIt(hList, p); 

  if(colorMap[next.first][next.second] == 0){ //white color
    auto it = listNode; 
    while(it != hList.end()){
      (*it)->location = next; 
      auto h = it; 
      it++; 
      nList.splice(nList.end(), hList, h); 
    }
  }
  else if(colorMap[next.first][next.second] == 1){ //red color
    auto it = hList.end(); 
    it--; 
    while(it != listNode){
      auto h = it; 
      (*it)->location = next; 
      it--; 
      nList.splice(nList.end(), hList, h); 
    }
    nList.splice(nList.end(), hList, it); 
    (*it)->location = next; 
  }
  else{ //blue color
    p->dir = -1 * p->dir; 
    coo nnext = p->location + p->dir; 
    if(colorMap[nnext.first][nnext.second] != 2){ //blue color again; 
      return move(p); 
    }
  }

  int sz = pieceMap[p->location.first][p->location.second].size();
  if(sz >= 4)
    return false; 
  return true;  
}

int main(){
  int K; 
  cin >> N >> K; 
  initColorMap(); 
  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
      cin >> colorMap[i][j]; 
    }
  }
  int x, y, d; 
  for(int i = 0; i < K; i++){
    cin >> x >> y >> d; 
    Piece* p = new Piece(x, y, d, i+1); 
    allPiece.push_back(p);
    pieceMap[x][y].push_back(p);  
  }

  int turn = 1; 
  while(turn <= 1000){
    bool success = true; 
    cout << "at turn => " << turn << "<= !!!" << endl; 
    for(int i = 0; i < allPiece.size(); i++){ 
      if(move(allPiece[i]) == false){
        success = false; 
        break;
      }
      print();
    }
    if(success == false)
      break; 
    turn++; 
  }

  if(turn > 1000)
    cout << "-1" << endl; 
  else
    cout << turn; 

  return 0; 
}