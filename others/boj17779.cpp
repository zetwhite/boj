#include <iostream> 
#include <vector> 
using namespace std; 

int N; 

void print(int map[22][22]){
  cout << "===========================================" << endl; 
  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
      cout << map[i][j] << "\t"; 
    }
    cout << endl; 
  }
}

int calcPopulation(int origin[22][22], int x, int y, int d1, int d2){
  int map[22][22]; 
  for(int i = 0; i <= N; i++)
    for(int j = 0; j <= N; j++)
      map[i][j] = origin[i][j]; 

  vector<int> firstLine; 
  vector<int> secondLine; 
  int startRow = x; 
  int endRow = x + d1 + d2; 
  for(int i = 0; i <= d1; i++){
    firstLine.push_back(y - i); 
  }
  for(int i = 0; i <= d2; i++){
    secondLine.push_back(y + i); 
  }
  for(int i = 1; i <= d2 ; i++){
    firstLine.push_back(y - d1 + i); 
  }
  for(int i = 1; i <= d1; i++){
    secondLine.push_back(y + d2 - i); 
  }
  int seg5 = 0; 
  for(int r = startRow; r <= endRow; r++){
    for(int c = firstLine[r-startRow]; c <= secondLine[r-startRow]; c++){
      seg5 += map[r][c]; 
      map[r][c] = 0; 
    }
  }
  //print(map); 

  int seg1 = 0; 
  for(int r = 1; r < x + d1; r++){
    for(int c = 1; c <= y; c++ ){
      seg1 += map[r][c]; 
      map[r][c] = 0; 
    }
  }
  //print(map); 

  int seg2 = 0; 
  for(int r = 1; r <= x + d2 ; r++){
    for(int c = y+1; c <= N; c++){
      seg2 += map[r][c]; 
      map[r][c] = 0; 
    }
  }
  //print(map); 

  int seg3 = 0; 
  for(int r = x + d1; r <= N; r++){
    for(int c = 1; c < y - d1 + d2; c++){
      seg3 += map[r][c]; 
      map[r][c] = 0; 
    }
  }
  //print(map); 

  int seg4 = 0; 
  for(int r = x + d2 + 1; r <= N; r++){
    for(int c = y - d1 + d2; c <= N; c++){
      seg4 += map[r][c]; 
      map[r][c] = 0; 
    }
  }
  //print(map); 

  vector<int> segs = {seg1, seg2, seg3, seg4, seg5}; 
  /*cout << "===============================" << endl; 
  for(int i = 0; i < 5; i++){
    cout << segs[i] << "\t"; 
  }
  cout << endl;*/ 
  int max = 0; 
  for(int i = 0; i < 5; i++){
    if(max < segs[i])
      max = segs[i]; 
  }
  int min = 1000'000'000; 
  for(int i = 0; i < 5; i++){
    if(min > segs[i])
      min = segs[i]; 
  }
  //cout << "=> " << max - min << endl; 
  return max - min; 
}


int main(){
  int map[22][22]; 
  cin >> N; 
  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
      cin >> map[i][j]; 
    }
  }

  int min = 1000'000'000; 
  for(int x = 1; x <= N-2; x++){
    for(int y = 2; y <= N-1; y++){
      for(int d1 = 1; d1 <= y - 1; d1++){
        for(int d2 = 1; d2 <= N - y; d2++){
          if(x + d1 + d2 > N)
            break; 
          //cout << "x = " << x << ", y = " << y << ", d1 = " << d1 << ", d2 = " << d2 << endl; 
          int loc = calcPopulation(map, x, y, d1, d2); 
          if(loc < min)
            min = loc; 
        }
      }
    }
  }
  //calcPopulation(map, x, y, d1, d2); 
  cout << min << endl; 
  return 0; 
}