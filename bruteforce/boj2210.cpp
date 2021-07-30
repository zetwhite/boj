#include <iostream> 
#include <set> 
using namespace std; 

#define N 7

int arr[N][N]; 
int dirX[4] = {0, 0, 1, -1}; 
int dirY[4] = {1, -1, 0, 0}; 
set<int> nums; 

void getNumber(int x, int y, int cnt, int number){
  if(cnt == 6){
    //cout << number << endl;
    nums.insert(number); 
    return;
  }

  int newX, newY, newNumber;  
  for(int i = 0; i < 4; i++){
    newX = x + dirX[i]; 
    newY = y + dirY[i]; 
    if(arr[newX][newY] == -1)
      continue; 
    newNumber = number*10 + arr[newX][newY]; 
    getNumber(newX, newY, cnt+1, newNumber); 
  }

}

int main(){
  for(int i = 0; i < N; i++){
    arr[i][N-1] = -1; 
    arr[i][0] = -1; 
  }
  for(int i = 0; i < N; i++){
    arr[N-1][i] = -1; 
    arr[0][i] = -1; 
  }
  for(int i = 1; i <= 5; i++){
    for(int j = 1; j <= 5; j++){
      cin >> arr[i][j]; 
    }
  }

  for(int i = 1; i <= 5; i++){
    for(int j = 1; j <= 5; j++){
      getNumber(i, j, 0, 0); 
    }
  }
  cout << nums.size() << endl; 
}