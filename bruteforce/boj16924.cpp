#include <iostream> 
#include <algorithm> 
#include <vector>
using namespace std;

pair<int, int> dir[4 ]= {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; 

int N, M; 
vector<int> xs; 
vector<int> ys; 
vector<int> lens; 
bool paint[102][102];
bool newpaint[102][102]; 

int findX(int a, int b){
  int len = 0;
  bool success = true;  
  while(success){
    len++; 
    for(int i = 0; i < 4; i++){
      int x = a + dir[i].first * len; 
      int y = b + dir[i].second * len; 
      if(paint[x][y] == false){
        len--; 
        success = false; 
        break; 
      }
    }
  }
  return len; 
}


bool finalCheck(){
  for(int i = 0; i < xs.size(); i++){
    int x = xs[i]; 
    int y = ys[i]; 
    int len = lens[i]; 
    newpaint[x][y] = true; 
    for(int j = 1; j <= len; j++){
      for(int d = 0; d < 4; d++){
        newpaint[x + j*dir[d].first][y + j*dir[d].second] = true; 
      }
    }
  }

  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= M; j++){
      if(paint[i][j] != newpaint[i][j])
        return false; 
    }
  }
  return true; 
}

int main(){

  for(int i = 0; i <= 101; i++){
    paint[0][i] = false; 
    paint[101][i] = false; 
    newpaint[0][i] = false; 
    newpaint[101][i] = false; 
  }
  for(int i = 0; i <= 101; i++){
    paint[i][0] = false; 
    paint[i][101] = false; 
    newpaint[i][0] = false; 
    newpaint[i][101] = false; 
  }
  cin >> N >> M; 

  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= M; j++){
      char tmp; 
      cin >> tmp; 
      if(tmp == '.')
        paint[i][j] = false; 
      else 
        paint[i][j] = true; 
    }
  }

  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= M; j++){
      if(paint[i][j] == false)
        continue; 
      int len = findX(i , j); 
      if(len <= 0)
        continue; 
      xs.push_back(i); 
      ys.push_back(j); 
      lens.push_back(len);
    }
  }

  if(finalCheck() == false){
    cout << "-1" << endl; 
    return 0; 
  }
  cout << xs.size() << endl; 
  for(int i = 0; i < xs.size(); i++){
    cout << xs[i] << " " << ys[i] << " " << lens[i] << endl;
  }
  
  return 0; 
}