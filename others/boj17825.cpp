#include <iostream> 
#include <vector> 
using namespace std; 
                  //   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32
int redLine[40]   = {  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 32, 22, 23, 29, 25, 29, 27, 28, 29, 30, 31, 20, -1}; 
int blueLine[40]  = {  1,  2,  3,  4,  5, 21,  7,  8,  9, 10, 24, 12, 13, 14, 15, 26, 17, 18, 19, 20, 32, 22, 23, 29, 25, 29, 27, 28, 29, 30, 31, 20, -1}; 
int point[40]     = {  0,  2,  4,  6,  8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 13, 16, 19, 22, 24, 28, 27, 26, 25, 30, 35,  0}; 

int inputs[10]; 
int horses[4] = {0, 0, 0, 0}; 

int moves(int currentPoint, int idx, int hNum, vector<int> path){
  if(horses[hNum] == -1) //this horse is ready in End Position; 
    return -1; 

  int oldPosition = horses[hNum]; 
  int moveCnt = inputs[idx];
  moveCnt--; 
  horses[hNum] = blueLine[horses[hNum]]; //start with blue line;
  if(horses[hNum] != -1) {
    while(moveCnt > 0){
      moveCnt--; 
      horses[hNum] = redLine[horses[hNum]]; //continue with redLine; 
      if(horses[hNum] == -1)
        break; 
    }
  }
  if(horses[hNum] != -1){
    /*for(int i = 0; i < idx; i++){
    cout << "\t"; 
    }
    cout << "point ( " << currentPoint << ") => "; */
    currentPoint += point[horses[hNum]]; 
    //cout << "point ( " << currentPoint << ")" << endl; 
  }

  if(horses[hNum] != -1){
    for(int i = 0; i < 4; i++){
      if(hNum == i)
        continue; 
      if(horses[hNum] == horses[i]){
        horses[hNum] = oldPosition; 
        return -1;   //this horses can not move, destination is already occupied...
      } 
    }
  }
  path.push_back(hNum); 

  if(idx == 9){
    horses[hNum] = oldPosition; 
    /*for(int i = 0; i < path.size(); i++){
      cout << path[i] << "\t"; 
    }
    cout << "=> " << currentPoint << endl;*/
    return currentPoint; 
  }

  int max = -1; 
  for(int i = 0; i < 4; i++){
    if(horses[i] == -1)
      continue; 
    int res = moves(currentPoint, idx+1, i, path); 
    if(max  <  res){
      max = res; 
    }
  }
  horses[hNum] = oldPosition; 
  return max;  
}

int main(){
  for(int i = 0; i < 10; i++){
    cin >> inputs[i]; 
  }
  int max = -1; 
  for(int i = 0; i < 4; i++){
    vector<int> path; 
    int local = moves(0, 0, i, path); 
    if(local > max)
      max = local; 
  }
  cout << max << endl; 
  return 0; 
}