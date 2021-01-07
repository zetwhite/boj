#include <iostream> 
using namespace std; 
int room[52][52]; 
int airClean1 = -1;
int airClean2 = -1; 
int dx[4] = {1, -1, 0, 0}; 
int dy[4] = {0, 0, 1, -1}; 


void print(int R, int C){
  cout << "=========================" << endl; 
  for(int i = 1; i <= R; i++){
    for(int j = 1 ; j <= C; j++){
      cout << room[i][j] << '\t'; 
    }
    cout << endl; 
  }
}

void initRoom(int R, int C){
  for(int i = 0; i <= C; i++){
    room[0][i] = -2; 
    room[R+1][i] = -2; 
  }
  for(int i = 0; i <= R; i++){
    room[i][0] = -2; 
    room[i][C+1] = -2; 
  }
  for(int x = 1; x <= R; x++){
    for(int y = 1; y <= C; y++){
      cin >> room[x][y];
      if(room[x][y] == -1 && airClean1 == -1){
        airClean1 = x; 
      } 
      if(room[x][y] == -1 && airClean1 != -1){
        airClean2 = x; 
      }
    }
  }
}

void expandDust(int R, int C){
  int movedDust[52][52]; 

  for(int x = 1; x <= R; x++){
    for(int y = 1; y <= C; y++){
      movedDust[x][y] = 0;  
    }
  }

  for(int x = 1; x <= R; x++){
    for(int y = 1; y <= C; y++){
      if(room[x][y] <= 0)
        continue; 

      int dust = room[x][y]/5; 
      for(int i = 0; i < 4; i++){
        int newx = x + dx[i]; 
        int newy = y + dy[i]; 
        if(room[newx][newy] >= 0){
          movedDust[newx][newy] += dust; 
          room[x][y] -= dust; 
        }
      }
    }
  }

  for(int x = 1; x <= R; x++){
    for(int y = 1; y <= C; y++){
      room[x][y] += movedDust[x][y]; 
    }
  }
}

void cleanAir(int R, int C){
  room[airClean1 - 1][1] = 0; 
  for(int r = airClean1 -1 ; r > 1; r--){
    room[r][1] = room[r - 1][1]; 
  }
  for(int c = 1; c < C; c++){
    room[1][c] = room[1][c+1];  
  }
  for(int r = 1; r < airClean1; r++){
    room[r][C] = room[r+1][C]; 
  }
  for(int c = C; c > 2;c--){
    room[airClean1][c] = room[airClean1][c - 1]; 
  }
  room[airClean1][2] = 0; 

  room[airClean2 + 1][1] = 0; 
  for(int r = airClean2 + 1; r < R; r++){
    room[r][1] = room[r+1][1]; 
  }
  for(int c = 1; c < C; c++){
    room[R][c] = room[R][c+1]; 
  }
  for(int r = R; r > airClean2; r--){
    room[r][C] = room[r-1][C]; 
  }
  for(int c = C; c > 2; c--){
    room[airClean2][c] = room[airClean2][c - 1]; 
  }
  room[airClean2][2] = 0; 
}

int main(){ 
  int R, C, T; 
  cin >> R >> C >> T; 
  initRoom(R, C);
  for(int t = 0; t < T; t++){
    expandDust(R, C); 
    //print(R, C); 
    cleanAir(R, C); 
    //print(R, C); 
  }

  int dust = 0; 
  for(int x = 1; x <= R; x++){
    for(int y = 1; y <= C; y++){
      dust += room[x][y]; 
    }
  } 

  cout << dust + 2 << endl; 

  return 0; 
}