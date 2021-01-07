#include <iostream> 
#include <vector> 
#include <algorithm> 
using namespace std; 

const int MSIZE = 100; 
void generateNext(vector<pair<int, int>>& v){
  for(int j = 0; j < 10; j++){
    int size = v.size(); 
    for(int i = size - 1; i >= 0; i--){
      if(v[i] == make_pair<int, int>(1, 0))
        v.emplace_back(0, -1); 
      else if(v[i] == make_pair<int, int>(0, -1))
        v.emplace_back(-1, 0);
      else if(v[i] == make_pair<int, int>(-1, 0))
        v.emplace_back(0, 1); 
      else if(v[i] == make_pair<int, int>(0, 1))
        v.emplace_back(1, 0);
    }
  }
}

void initMap(bool map[][MSIZE + 1]){
  for(int i = 0; i <= MSIZE; i++){
    for(int j = 0; j <= MSIZE; j++){
      map[i][j] = false; 
    }
  }
}

int curveCnt(int g){
  int cnt = 1; 
  for(int i = 0; i < g; i++ ){
    cnt *= 2; 
  }
  return cnt; 
}

void checkNext(bool map[][MSIZE + 1], int x, int y, const vector<pair<int, int>>& curve, int g){
  int ccnt = curveCnt(g); 
  //cout << "genCnt = " << ccnt << endl; 
  int currentX = x; 
  int currentY = y; 
  for(int i = 0; i < ccnt; i++){
    if(0 <= currentX && currentX <= 100 && 0 <= currentY && currentY <= 100){
      map[currentX][currentY] = true; 
      //cout << "(" << currentX << ", " << currentY << ") " << endl; 
    }
    currentX += curve[i].first; 
    currentY += curve[i].second; 
  }
    if(0 <= currentX && currentX <= 100 && 0 <= currentY && currentY <= 100){
      map[currentX][currentY] = true; 
      //cout << "(" << currentX << ", " << currentY << ") " << endl; 
    }
}

void print(bool map[][MSIZE + 1]){
  cout << "===============================" << endl; 
  for(int y = 0; y < 20; y++){
    for(int x = 0; x < 20; x++){
      cout << map[x][y] << " "; 
    }
    cout << endl; 
  }
}


int main(){
  vector<pair<int, int>> curveVec[4]; 
  curveVec[0].push_back({1, 0}); 
  curveVec[1].push_back({0, -1}); 
  curveVec[2].push_back({-1, 0}); 
  curveVec[3].push_back({0, 1}); 
  for(int i = 0; i < 4; i++){
    generateNext(curveVec[i]);
    //cout << curveVec[i].size() << endl; 
  }

  bool map[MSIZE + 1][MSIZE + 1];
  initMap(map); 

  int inputSize; 
  cin >> inputSize; 
  int x, y, d, g; 
  for(int i = 0; i < inputSize; i++){
    cin >> x >> y >> d >> g; 
    checkNext(map, x, y, curveVec[d], g); 
    //print(map); 
  } 

  int count = 0; 
  for(int i = 0; i < MSIZE; i++){
    for(int j = 0; j < MSIZE; j++){
      if(map[i][j] && map[i+1][j] && map[i][j+1] && map[i+1][j+1])
        count++; 
    }
  }
  cout << count << endl; 
  return 0; 
} 