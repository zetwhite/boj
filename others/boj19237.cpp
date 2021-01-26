#include <iostream> 
#include <algorithm> 
#include <vector> 
using namespace std; 

typedef pair<int, int> coo; 
coo DIR[5] = {{0, 0}, {-1, 0}, {1,0}, {0, -1}, {0, 1}}; 

ostream& operator<< (ostream& os, coo& c){
  cout << "(" << c.first << ", " << c.second << ")"; 
  return os; 
}

coo operator+ (const coo& a, const coo& b){
  return {a.first + b.first, a.second + b.second}; 
}

class Shark{
public: 
  int prio[4][4]; //up-down-left-right
  int dir; 
  int num; 
  bool moved; 
  coo loc; 

  vector<coo> nextLoc(){
    vector<coo> candidates; 
    coo next; 
    for(int i = 0; i < 4; i++){
      next = loc + DIR[prio[dir-1][i]]; 
      candidates.push_back(next); 
    }
    return candidates; 
  }

}; 

ostream& operator<< (ostream& os, Shark& s){
  os << s.num << DIR[s.dir]; 
  return os; 
}


class SeaBlock{
public: 
  int smellLeft; 
  int smellOwner; 
  Shark* sPointer; 
  SeaBlock():smellLeft(100), smellOwner(-1), sPointer(nullptr){}
}; 

ostream& operator<< (ostream& os, SeaBlock& sb){
  os << sb.smellOwner << " => " << sb.smellLeft;
  if(sb.sPointer != nullptr){
    os << " s" << sb.sPointer->num << "!"; 
  } 
  else{
    os << " ---"; 
  }
  return os; 
}

int N, M, K; 
SeaBlock sea[22][22];
Shark sharks[401]; 


void getSeaBlocks(){
  int s; 
  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
      cin >> s; 
      sea[i][j].smellOwner = s; 
      sea[i][j].smellLeft = 0; 
      if(s != 0){
        sharks[s].loc = {i, j}; 
        sea[i][j].smellLeft = K; 
        sea[i][j].sPointer = &(sharks[s]); 
      }
    }
  }
}

void getSharks(){
  vector<int> tmpDir; 
  int d; 
  for(int i = 1; i <= M; i++){
    cin >> d; 
    sharks[i].dir = d; 
    sharks[i].num = i; 
    sharks[i].moved = false; 
  }

  for(int i = 1; i <= M; i++){
    for(int j = 0; j < 4; j++){
      for(int t = 0; t < 4; t++){
        cin >> sharks[i].prio[j][t]; 
      }
    }
  }
}

void printSea(){
  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
      cout << sea[i][j] << "\t"; 
    }
    cout << endl; 
  }
}

void printShark(){
  cout<< "========shark===========" << endl;  
  for(int i = 1; i <= M; i++){
    cout << sharks[i] << endl; 
  }
  cout << endl; 
}

vector<coo> mvNextPosition(Shark& s){
  //cout << "shark " << s.num << "tries "; 
  vector<coo> newSmell; 
  s.moved = true; 
  sea[s.loc.first][s.loc.second].sPointer = nullptr; 

  vector<coo> can1 = s.nextLoc(); 
  bool success = false; 
  coo next; 
  for(int i = 0; i < can1.size(); i++){
    next = can1[i]; 
    //cout << next << "(" << sea[next.first][next.second] << ") " << ",  "; 
    if(sea[next.first][next.second].smellLeft != 0)
      continue; 

    success = true; 
    s.dir = s.prio[s.dir-1][i]; 
    if(sea[next.first][next.second].sPointer == nullptr){ //empty 
      sea[next.first][next.second].smellOwner = s.num; 
      newSmell.emplace_back(next.first, next.second); 
      //sea[next.first][next.second].smellLeft = K;  
      sea[next.first][next.second].sPointer = &s;
      s.loc = next; 
      break; 
    }
    else if(sea[next.first][next.second].sPointer->moved == true){ //already moved 
      s.num = -1; //exit 
      break; 
    }
    else{
      Shark* ns = sea[next.first][next.second].sPointer; 
      sea[next.first][next.second].smellOwner = s.num; 
      newSmell.emplace_back(next.first, next.second); 
      //sea[next.first][next.second].smellLeft = K;  
      sea[next.first][next.second].sPointer = &s; 
      s.loc = next; 
      vector<coo> tmp = mvNextPosition(*ns);
      newSmell.insert(newSmell.end(), tmp.begin(), tmp.end());
      break;  
    }
  }

  if(success){
    //cout << endl; 
    return newSmell; 
  }
  
  for(int i = 0; i < can1.size(); i++){
    next = can1[i]; 
    //cout << next; 
    if(sea[next.first][next.second].smellOwner != s.num )
      continue; 
    s.dir = s.prio[s.dir-1][i]; 
    //sea[next.first][next.second].smellLeft = K; 
    s.loc = next; 
    newSmell.emplace_back(next.first, next.second);
    sea[next.first][next.second].sPointer = &s; 
    break; 
  }
  //cout << endl; 
  return newSmell; 
}

void moveShark(){
  for(int i = 1; i <= M; i++){
    sharks[i].moved = false; 
  }

  vector<coo> cox; 
  for(int i = 1; i <= M; i++){
    if(sharks[i].num <= 0 || sharks[i].moved == true)
      continue; //shark is out of sea or already moved
    vector<coo> tmp = mvNextPosition(sharks[i]); 
    cox.insert(cox.end(), tmp.begin(), tmp.end()); 
  }

  for(int j = 0; j < cox.size(); j++){
    sea[cox[j].first][cox[j].second].smellLeft = K+1; 
  }

  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
      if(sea[i][j].smellLeft > 0)
        sea[i][j].smellLeft--; 
      if(sea[i][j].smellLeft == 0){
        sea[i][j].smellOwner = 0; 
      }
    }
  }
}

bool CheckGood(){
  for(int i = 2; i <= M; i++){
    if(sharks[i].num > 0)
      return false; 
  }
  return true; 
}

int main(){
  cin >> N >> M >> K; 
  getSeaBlocks(); 
  getSharks(); 

  //printSea(); 
  //printShark(); 

  int mv = 0; 
  while(CheckGood() != true){
    moveShark(); 
    mv++; 
    //printSea(); 
    //printShark(); 
    if(mv > 1000)
      break; 
  }
  if(mv > 1000)
    cout << -1 << endl; 
  else 
    cout << mv << endl; 
  return 0; 
}