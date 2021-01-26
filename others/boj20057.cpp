#include <iostream> 
#include <vector> 
using namespace std; 

typedef pair<int, int> coo; 
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

int N; 
coo Tor;
int map[505][505]; 
coo DIR[4] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
vector<pair<coo, int>> Left = {
    {{-2, 0}, 2}, {{2, 0}, 2},
    {{-1, -1}, 10}, {{1, -1}, 10},
    {{0, -2}, 5}, 
    {{-1, 0}, 7}, {{1, 0}, 7}, 
    {{-1, 1}, 1}, {{1, 1}, 1}
}; 
vector<pair<coo, int>> Right = {
  {{-2, 0}, 2}, {{2, 0}, 2},
  {{1, 1}, 10}, {{-1, 1}, 10}, 
  {{0, 2}, 5}, 
  {{-1, 0}, 7}, {{1, 0}, 7}, 
  {{-1, -1}, 1}, {{1, -1}, 1}
}; 
vector<pair<coo, int>> Up = {
  {{0, -2}, 2}, {{0, 2}, 2},
  {{0, -1}, 7}, {{0, 1}, 7}, 
  {{-2, 0}, 5}, 
  {{-1, 1}, 10}, {{-1, -1}, 10}, 
  {{1, -1}, 1}, {{1, 1}, 1}
}; 
vector<pair<coo, int>> Down = {
  {{0, -2}, 2}, {{0, 2}, 2},
  {{0, -1}, 7}, {{0, 1}, 7}, 
  {{2, 0}, 5}, 
  {{1, 1}, 10}, {{1, -1}, 10}, 
  {{-1, -1}, 1}, {{-1, 1}, 1}
}; 
vector<pair<coo, int>> BLOW[4] = {Left, Right, Down, Up}; 

void print(){
  cout << "=======================================" << endl; 
  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
      cout << map[i][j] << "\t"; 
    }
    cout << endl; 
  }
}

bool inRange(coo x){
  if(x.first <= 0 || x.first > N)
    return false; 
  if(x.second <= 0 || x.second > N) 
    return false; 
  return true; 
}

void go(int dir){
  vector<pair<coo, int>>& blowed = BLOW[dir]; 

  coo BlowPoint = Tor;  
  BlowPoint = BlowPoint + DIR[dir];
  coo LeftPoint = BlowPoint + DIR[dir];  
  int left = map[BlowPoint.first][BlowPoint.second]; 

  for(int i = 0; i < blowed.size(); i++){
    coo Dest = BlowPoint + blowed[i].first; 
    int amount = (map[BlowPoint.first][BlowPoint.second] * blowed[i].second / 100); 
    if(inRange(Dest))
      map[Dest.first][Dest.second] += amount;       
    left -= amount; 
  }
  map[BlowPoint.first][BlowPoint.second] = 0; 
  map[LeftPoint.first][LeftPoint.second] += left; 
  Tor = BlowPoint; 
}

void goLeft(int len){
  for(int i = 0; i < len; i++)
    go(0);
}

void goRight(int len){
  for(int i = 0; i < len; i++)
    go(1); 
}

void goUp(int len){
  for(int i = 0; i < len; i++)
    go(3);
}

void goDown(int len){
  for(int i = 0; i < len; i++)
    go(2); 
}

bool isLast(coo& tor){
  return tor == make_pair(1, N); 
}

int main(){ 
  cin >> N; 
  Tor = make_pair((N+1)/2, (N+1)/2); 
  int all = 0; 

  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
      cin >> map[i][j]; 
      all += map[i][j]; 
    }
  }

  int len = 1; 
  while(!isLast(Tor)){
    goLeft(len); 
    if(isLast(Tor))
      break; 
    goDown(len); 
    if(isLast(Tor))
      break; 
    len++; 

    goRight(len); 
    if(isLast(Tor))
      break; 
    goUp(len); 
    if(isLast(Tor))
      break; 
    len++; 
  }
  goLeft(N-1); 

  int left = 0; 
  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
      left += map[i][j]; 
    }
  }
  cout << all - left << endl; 
  return 0; 
}