#include <iostream> 
#include <vector> 
using namespace std; 

vector<vector<int>> a = {{0},{0, 0, 0, 0}}; 
vector<vector<int>> b = {{0, 0}}; 
vector<vector<int>> c = {{0, 0, -1}, {-1, 0}}; 
vector<vector<int>> d = {{-1, 0, 0}, {0, -1}}; 
vector<vector<int>> e = {{0, 0, 0}, {0, -1}, {-1, 0, -1}, {-1, 0}}; 
vector<vector<int>> f = {{0, 0, 0}, {0, 0}, {0, -1, -1}, {-2, 0}}; 
vector<vector<int>> g = {{0, 0, 0}, {0, 0}, {-1, -1, 0}, {0, -2}}; 
vector<vector<vector<int>>> blocks = {a, b, c, d, e, f, g};

bool checkFit(vector<int>& arr, int index, vector<int>& blockSection){
  vector<int> sec; 
  for(int i = 0; i < blockSection.size(); i++){
    sec.emplace_back(arr[index+i] + blockSection[i]); 
  }
  bool success = true; 
  for(int i = 0; i < sec.size() - 1; i++){
    if(sec[i] != sec[i+1]){
      success = false; 
      break; 
    }
  }
  return success; 
}

int main(){
  int C, P; 
  cin >> C >> P; 

  vector<int> arr; 
  arr.reserve(C); 
  int tmp; 
  for(int i = 0; i < C; i++){
    cin >> tmp; 
    arr.emplace_back(tmp); 
  }

  vector<vector<int>>& shapeBlock = blocks[P-1]; 
  int cnt = 0; 
  for(int i = 0; i < shapeBlock.size(); i++){
    /*cout << "try block fit at "; 
    for(int j = 0; j < shapeBlock[i].size(); j++){
      cout << shapeBlock[i][j] << " "; 
    }
    cout << endl;*/ 
    for(int j = 0; j <= C-shapeBlock[i].size(); j++){

      if(checkFit(arr, j, shapeBlock[i])){
        /*cout << "fit at arraay "; 
        for(int t = 0; t < shapeBlock[i].size(); t++){
          cout << arr[j + t] << " "; 
        }
        cout << endl;*/ 
        cnt++; 
      }
    }
  }
  cout << cnt << endl; 
  return 0; 
}