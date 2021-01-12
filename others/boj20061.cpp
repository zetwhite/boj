#include <iostream> 

using namespace std; 

class Partition{
public : 
  bool area[7][4]; 
  Partition(){
    for(int i = 0; i < 6; i++)
      for(int j = 0; j < 4; j++)
        area[i][j] = false; 

    for(int j = 0; j < 4; j++){
      area[6][j] = true; 
    }
  }

  int getColored(){
    int colored = 0; 
    for(int i = 0; i < 6; i++){
      for(int j = 0; j < 4; j++){
        if(area[i][j])
          colored++; 
      }
    }
    return colored; 
  }

  void print(){
    for(int i = 0; i < 6; i++){
      for(int j = 0; j < 4; j++){
        cout << area[i][j] << "\t"; 
      }
      cout << endl; 
    }
  }

  void moveGreen(int x, int y, int t){
    int _x = 1; 
    int _y = y; 
    if(t == 1 || t == 3){
      while(area[_x + 1][_y] != true)
        _x += 1; 
      area[_x][_y] = true; 
      if(t == 3)
        area[_x - 1][_y] = true; 
    }
    else{
      while(area[_x+1][_y] == false && area[_x+1][_y+1] == false){
        _x += 1;
      }
      area[_x][_y] = true; 
      area[_x][_y+1] = true; 
    }
  }

  void moveBlue(int x, int y, int t){
    int _x = 1; 
    int _y = x; 
    if(t == 1 || t == 2){
      while(area[_x + 1][_y] != true)
        _x += 1; 
      area[_x][_y] = true; 
      if(t == 2)
        area[_x - 1][_y] = true; 
    }
    else{
      while(area[_x+1][_y] == false && area[_x+1][_y+1] == false){
        _x += 1;
      }
      area[_x][_y] = true; 
      area[_x][_y+1] = true; 
    }
  }

  //line x disappear
  void drawDown(int x){
    for(int _x = x; _x >= 1; _x--){
      for(int _y = 0; _y < 4; _y++){
          area[_x][_y] = area[_x - 1][_y]; 
      }
    }
    for(int _y = 0; _y < 4; _y++){
      area[0][_y] = false; 
    }
  }

  int getPoint(){
    int point = 0; 
    for(int x = 5; x >= 0; x--){
      bool full = true; 
      for(int y = 0; y < 4; y++){
        if(area[x][y] == false){
          full = false; 
          break; 
        }
      }

      if(full == true){
        point++; 
        drawDown(x); 
        x++; 
      }
    }
    return point; 
  }

  void checkShadow(){
    bool isSth = false; 
    for(int y = 0; y < 4; y++){
      if(area[1][y] == true){
        isSth = true; 
        break; 
      }
    }
    if(isSth == true){
      drawDown(5); 
    }

    isSth = false; 
    for(int y = 0; y < 4; y++){
      if(area[1][y] == true){
        isSth = true; 
        break; 
      }
    }
    if(isSth == true){
      drawDown(5); 
    }
  }
}; 

int main(){
  Partition bluePart; 
  Partition greenPart; 
  int N; 
  int t, x, y; 
  cin >> N; 
  int point; 
  for(int i = 0; i < N; i++){
    //cout << "i = " << i << endl; 
    cin >> t >> x >> y; 
    bluePart.moveBlue(x, y, t); 
    /*cout << "============ after move ================" << endl; 
    bluePart.print(); */
    point += bluePart.getPoint(); 
    /*cout << "============ get Point =================" << endl; 
    bluePart.print(); */
    bluePart.checkShadow();
    //cout << "============ BLUE afger delete shadow ==========" << endl; 
    //bluePart.print(); 

    greenPart.moveGreen(x, y, t); 
    //cout << "============ after move ================" << endl; 
    //greenPart.print(); 
    point += greenPart.getPoint(); 
    //cout << "============ get Point =================" << endl; 
    //greenPart.print(); 
    greenPart.checkShadow();
    //cout << "============GREEN afger delete shadow ==========" << endl; 
    //greenPart.print();
    //cout << endl << endl; 
  }
  cout << point << endl; 
  cout << bluePart.getColored() + greenPart.getColored() << endl; 
  return 0; 
} 