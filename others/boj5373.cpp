#include <iostream> 
#include <vector> 

using namespace std; 

typedef vector<char> chars; 
class Cube{
public : 
  // 0 - up, 1 - bottom, 2 - front, 3 - right, 4 - back, 5- left 
  char faces[6][3][3] = {
    {
      {'w', 'w', 'w'}, 
      {'w', 'w', 'w'}, 
      {'w', 'w', 'w'}
    }, 
    {
      {'y', 'y', 'y'}, 
      {'y', 'y', 'y'}, 
      {'y', 'y', 'y'}
    }, 
    {
      {'r', 'r', 'r'}, 
      {'r', 'r', 'r'}, 
      {'r', 'r', 'r'}
    }, 
    {
      {'b', 'b', 'b'}, 
      {'b', 'b', 'b'}, 
      {'b', 'b', 'b'}
    }, 
    {
      {'o', 'o', 'o'}, 
      {'o', 'o', 'o'}, 
      {'o', 'o', 'o'}
    }, 
    {
      {'g', 'g', 'g'}, 
      {'g', 'g', 'g'}, 
      {'g', 'g', 'g'}
    }
  }; 

  string toString(int i){
    switch (i)
    {
    case 0 : return "UP"; 
    case 1 : return "DOWN"; 
    case 2 : return "FRONT"; 
    case 3 : return "RIGHT"; 
    case 4 : return "BACK"; 
    case 5 : return "LEFT"; 
    default : return "WRONG"; 
  }
}

  void printUP(){
    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
        cout << faces[0][i][j]; 
      }
      cout << endl; 
    }
  }
  void print(){
    for(int i = 0; i < 6; i++){
      cout << "face = " << toString(i) << endl; 
      for(int j = 0; j < 3; j++){
        for(int k = 0; k < 3; k++){
          cout << faces[i][j][k]; 
        }
        cout << endl; 
      }
    }
  }

  void rotateFace(int f, bool isPlus){
    char oldFace[3][3]; 
    for(int i = 0; i < 3; i++){
      for(int j = 0;j < 3; j++){
        oldFace[i][j] = faces[f][i][j]; 
      }
    }

    if(!isPlus){
      for(int i = 0; i < 3; i++){
        for(int j = 0;  j < 3; j++){
          faces[f][2-j][i] = oldFace[i][j]; 
        }
      }
    }
    else{
      for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
          faces[f][j][2-i] = oldFace[i][j];  
        }
      }
    }
  }

  chars getColors(int f, bool isCol, int idx){
    chars colors; 
    if(isCol == true){
      for(int i = 0; i < 3; i++)
        colors.push_back(faces[f][i][idx]); 
    }
    else{
      for(int i = 0; i < 3; i++)
        colors.push_back(faces[f][idx][i]); 
    }
    return colors; 
  }

  void putColors(chars src, int f, bool isCol, int idx, bool reverse = false){
    if(isCol == true){
      for(int i = 0; i < 3; i++)
        if(reverse == true){
          faces[f][i][idx] = src[2 - i]; 
        }
        else
          faces[f][i][idx] = src[i]; 
    }
    else{
      for(int i = 0; i < 3; i++)
        if(reverse == true)
          faces[f][idx][i] = src[2 - i];
        else
          faces[f][idx][i] = src[i]; 
    }
    return; 
  }

  // 0 - up, 1 - down, 2 - front, 3 - right, 4 - back, 5- left 
  void rotate(char face, char direction){
  if(face == 'F'){
      // U -> R -> B -> L -> U 
      chars up = getColors(0, false, 2); 
      chars right = getColors(3, true, 0); 
      chars down = getColors(1, false, 0); 
      chars left = getColors(5, true, 2); 

      if(direction == '+'){
        rotateFace(2, true); 
        putColors(up, 3, true, 0); 
        putColors(right, 1, false, 0, true); 
        putColors(down, 5, true, 2); 
        putColors(left, 0, false, 2, true); 
      }
      else{
        rotateFace(2, false); 
        putColors(up, 5, true, 2, true); 
        putColors(left, 1, false, 0);
        putColors(down, 3, true, 0, true); 
        putColors(right, 0, false, 2);
      }
  }
  else if(face == 'B' ){
      //(+) U -> L -> B -> R -> U 
      chars up = getColors(0, false, 0); 
      chars left = getColors(5, true, 0); 
      chars down = getColors(1, false, 2); 
      chars right = getColors(3, true, 2); 
      if(direction == '+'){
        rotateFace(4, true); 
        putColors(up, 5, true, 0, true); 
        putColors(left, 1, false, 2); 
        putColors(down, 3, true, 2, true); 
        putColors(right, 0, false, 0); 
      }
      else{
        rotateFace(4, false); 
        putColors(up, 3, true, 2); 
        putColors(right, 1, false, 2, true); 
        putColors(down, 5, true, 0); 
        putColors(left, 0, false, 0, true); 
      }
  }
  else if(face == 'U'){
      //(+) B-> R -> F -> L -> B 
      chars back = getColors(4, false, 0); 
      chars right = getColors(3, false, 0); 
      chars front = getColors(2, false, 0); 
      chars left = getColors(5, false, 0); 
      if(direction == '+'){
        rotateFace(0, true); 
        putColors(back, 3, false, 0); 
        putColors(right, 2, false, 0); 
        putColors(front, 5, false, 0); 
        putColors(left, 4, false, 0); 
      }
      else{
        rotateFace(0, false); 
        putColors(back, 5, false, 0); 
        putColors(left, 2, false, 0); 
        putColors(front, 3, false, 0); 
        putColors(right, 4, false, 0); 
      }
  }
  else if(face == 'D'){
      //(+) F -> R -> B -> L -> F
      chars back = getColors(4, false, 2); 
      chars right = getColors(3, false, 2); 
      chars front = getColors(2, false, 2); 
      chars left = getColors(5, false, 2); 
      if(direction == '+'){
        rotateFace(1, true); 
        putColors(front, 3, false, 2);
        putColors(right, 4, false, 2);
        putColors(back, 5, false, 2);
        putColors(left, 2, false, 2);
      }
      else{
        rotateFace(1, false); 
        putColors(front, 5, false, 2);
        putColors(left, 4, false, 2);
        putColors(back, 3, false, 2);
        putColors(right, 2, false, 2);
      }
  }
  else if(face == 'R'){
    chars front = getColors(2, true, 2); 
    chars up = getColors(0, true, 2); 
    chars back = getColors(4, true, 0); 
    chars down = getColors(1, true, 2); 
    if(direction == '+'){
      //U -> B -> D -> F -> U 
      rotateFace(3, true); 
      putColors(up, 4, true, 0, true); 
      putColors(back, 1, true, 2, true); 
      putColors(down, 2, true, 2); 
      putColors(front, 0, true, 2); 
    }
    else{
      rotateFace(3, false); 
      putColors(up, 2, true, 2); 
      putColors(front, 1, true, 2); 
      putColors(down, 4, true, 0, true); 
      putColors(back, 0, true, 2, true); 
    }
  }
  else if(face == 'L'){
    chars front = getColors(2, true, 0); 
    //cout << "front = " << front[0] << ', ' << front[1] << ', ' << front[2] << endl; 
    chars up = getColors(0, true, 0); 
    chars back = getColors(4, true, 2); 
    chars down = getColors(1, true, 0);  
    if(direction == '+'){
      //U -> F -> D -> B -> U 
      rotateFace(5, true); 
      putColors(up, 2, true, 0); 
      putColors(front, 1, true, 0); 
      putColors(down, 4, true, 2, true); 
      putColors(back, 0, true, 0, true); 
    }
    else{
      rotateFace(5, false); 
      putColors(up, 4, true, 2, true); 
      putColors(back, 1, true, 0, true); 
      putColors(down, 2, true, 0); 
      putColors(front, 0, true, 0); 
    }
  }
  }
}; 

int main(){
  int N; 
  int size; 
  cin >> N; 
  for(int i = 0; i < N; i++){
    Cube cube;
    cin >> size; 
    for(int j = 0; j < size; j++){
      char face, direction; 
      cin >> face >> direction; 
      // cout << "=========================" << endl; 
      //cout << face << ", " << direction << endl; 
      cube.rotate(face, direction); 
      //cube.print(); 
    }
    cube.printUP(); 
  }
  return 0; 
}