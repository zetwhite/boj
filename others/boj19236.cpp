#include <iostream> 
#include <algorithm> 
#include <map> 
#include <vector> 
using namespace std; 

typedef pair<int, int> coo;    
coo dir[8] = {{-1, 0}, {-1, -1}, {0, -1},  {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}}; 
coo operator + (const coo& c1, const coo& c2){
  return { c1.first + c2.first, c1.second + c2.second }; 
}

class Fish{
public: 
  int d; 
  int number; 
  Fish(int _n, int _d){
    d = _d; 
    number = _n; 
  }
  Fish(){
  }
}; 

//global variable 
const int S_NUM = 99; 
const int INVALID = -1; 
//vector<Fish*> fishList; 
Fish fishTank[6][6];  // coo -> 번호, direction 
map<int, coo> fishMap;  // 번호 -> 좌표  
Fish* shark; 


void getFishTank(int& point, int& sharkDir, coo& sharkCoo){
  for(int i = 0; i <= 5; i++){
    fishTank[0][i] = Fish(INVALID, 0); 
    fishTank[5][i] = Fish(INVALID, 0);  
    fishTank[i][5] = Fish(INVALID, 0); 
    fishTank[i][0] = Fish(INVALID, 0); 
  }

  int a, b; 
  for(int i = 1; i <= 4; i++){
    for(int j = 1; j <= 4; j++){
      cin >> a >> b; 
      fishTank[i][j] = Fish(a, b-1); 
      //fishList.push_back(&(fishTank[i][j])); 
      fishMap.insert({a, {i, j}}); 
    }
  }
  fishMap.erase(fishTank[1][1].number); 
  shark = &(fishTank[1][1]);
  point = shark->number; 
  sharkDir = shark->d; 
  sharkCoo = {1, 1}; 
  shark->number = S_NUM; 
}

void printFishTank(Fish fishTank[6][6]){
  cout << "=======================================" << endl; 
  for(int i = 1; i <= 4; i++){
    for(int j = 1; j <= 4; j++){
      if(fishTank[i][j].number == 0)
        cout << "____" << "\t"; 
      else 
        cout << fishTank[i][j].number << "(" << fishTank[i][j].d << ")" << "\t"; 
    }
    cout << endl; 
  }
}

int moveFish(Fish tank[6][6], map<int, coo> fmap, int sharkDir, coo sharkCoo){
  /*
  cout << "======================================" << endl; 
  cout << "======================================" << endl; 
  cout << "shark is at " << sharkCoo.first << ", " << sharkCoo.second << endl; 
  printFishTank(tank); 
  */

  Fish newTank[6][6]; 
  for(int i = 0; i <= 5; i++){
    for(int j = 0; j <= 5; j++){
      newTank[i][j] = tank[i][j]; 
    }
  }

  //moveFish
  for(int f = 1; f <= 16; f++){
    auto it = fmap.find(f); 
    if(it == fmap.end())
      continue; 
    
    coo fcoo = it->second;     
    for(int i = 0; i < 8; i++){
      //cout << "here is " << fcoo.first << ", " << fcoo.second << endl; 
      coo nextLocation = fcoo + dir[newTank[fcoo.first][fcoo.second].d]; 
      int nextNumber = newTank[nextLocation.first][nextLocation.second].number; 
      if(nextNumber == -1 || nextNumber == S_NUM){
        newTank[fcoo.first][fcoo.second].d = ( newTank[fcoo.first][fcoo.second].d + 1 ) % 8; 
      }
      else if(nextNumber == 0){ //empty 
       // cout << "move to empty place " << nextLocation.first << ", " << nextLocation.second << endl;  
        newTank[nextLocation.first][nextLocation.second] = newTank[fcoo.first][fcoo.second]; 
        newTank[fcoo.first][fcoo.second].number = 0; 
        fmap[f] = {nextLocation.first, nextLocation.second}; 
        break; 

      }
      else{ // other Fish
        //cout << "exchange place " << nextLocation.first << ", " << nextLocation.second << endl; 
        Fish tmp = newTank[fcoo.first][fcoo.second]; 
        newTank[fcoo.first][fcoo.second] = newTank[nextLocation.first][nextLocation.second]; 
        newTank[nextLocation.first][nextLocation.second] = tmp;
        fmap[f] = {nextLocation.first, nextLocation.second};
        fmap[nextNumber] = {fcoo.first, fcoo.second}; 
        break; 
      }
    }
    //printFishTank(newTank);
  }
  //printFishTank(newTank);

  
  newTank[sharkCoo.first][sharkCoo.second].number = 0; 
  coo nextSharkCoo = sharkCoo + dir[sharkDir]; 
  int maxPoint = 0; 
  while(newTank[nextSharkCoo.first][nextSharkCoo.second].number != INVALID){
    if(newTank[nextSharkCoo.first][nextSharkCoo.second].number != 0){
      int number = newTank[nextSharkCoo.first][nextSharkCoo.second].number; 
      int dir = newTank[nextSharkCoo.first][nextSharkCoo.second].d; 
      fmap.erase(number); 

      newTank[nextSharkCoo.first][nextSharkCoo.second].number = S_NUM; 
      int ret = moveFish(newTank, fmap, dir, nextSharkCoo); 
      ret += number; 
      if(ret > maxPoint){
        maxPoint = ret; 
      }
      fmap[number] = nextSharkCoo; 
      newTank[nextSharkCoo.first][nextSharkCoo.second].number = number; 
      newTank[nextSharkCoo.first][nextSharkCoo.second].d = dir; 
    }
    nextSharkCoo = nextSharkCoo + dir[sharkDir]; 
    //cout << "next is " << nextSharkCoo.first << " , " << nextSharkCoo.second << endl; 
  }
  
  return maxPoint; 
}

int main(){
  int point; 
  int sharkDir; 
  coo sharkCoo; 
  getFishTank(point, sharkDir, sharkCoo); 
  //printFishTank(fishTank); 
  int res = moveFish(fishTank, fishMap, sharkDir, sharkCoo); 
  cout << res + point << endl; 
  return 0; 
}