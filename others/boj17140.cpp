#include <iostream> 
#include <vector> 
#include <map> 
#include <algorithm> 
using namespace std; 

int arr[101][101];  
int R = 3; 
int C = 3; 

void init(){
  for(int i = 0; i < 101; i++){
    for(int j = 0; j < 101; j++){
      arr[i][j] = 0; 
    }
  }
}

bool check(int r, int c, int k){
  return arr[r][c] == k; 
}

bool compare(pair<int, int> &lhs, pair<int, int>& rhs){
  if(lhs.second == rhs.second)
    return lhs.first < rhs.first; 
  return lhs.second < rhs.second; 
}

void print(){
  cout << "==========================" << endl; 
  for(int i = 0; i < R; i++){
    for(int j = 0; j < C; j++){
      cout << arr[i][j] << "\t"; 
    }
    cout << endl; 
  }
}


void uploadRow(){
  int mRow = 0; 
  map<int, int> counts[R]; 
  
  //find using map 
  for(int i = 0; i < R; i++){
    for(int j = 0; j < C; j++){
      if(arr[i][j] == 0)
        continue; 
      auto it = counts[i].find(arr[i][j]); 
      if(it == counts[i].end()){
        counts[i].insert({arr[i][j], 1}); 
      }
      else{
        it->second++; 
      }
    }
    int sz = counts[i].size(); 
    if( sz > mRow )
      mRow = sz; 
  }

  //updates
  if(mRow > 50)
    mRow = 50; 
  for(int i = 0; i < R; i++){
    vector<pair<int, int>> countsVec(counts[i].begin(), counts[i].end()); 
    sort(countsVec.begin(), countsVec.end(), compare); 
    int j = 0; 
    for(j = 0 ; j < countsVec.size(); j++){
      if(j >= 50)
        break; 
      arr[i][j*2] = countsVec[j].first; 
      arr[i][j*2 + 1] = countsVec[j].second; 
    }
    for(; j < mRow; j++){
      arr[i][j*2] = 0; 
      arr[i][j*2  + 1] = 0; 
    }
  }
  C = mRow * 2; 
}


void uploadCol(){
  int mCol = 0; 
  map<int, int> counts[C]; 
  
  //find using map 
  for(int i = 0; i < C; i++){
    for(int j = 0; j < R; j++){
      if(arr[j][i] == 0)
        continue; 
      auto it = counts[i].find(arr[j][i]); 
      if(it == counts[i].end()){
        counts[i].insert({arr[j][i], 1}); 
      }
      else{
        it->second++; 
      }
    }
    int sz = counts[i].size(); 
    if( sz > mCol )
      mCol = sz; 
  }

  //updates
  if(mCol > 50)
    mCol = 50; 
  for(int i = 0; i < C; i++){
    vector<pair<int, int>> countsVec(counts[i].begin(), counts[i].end()); 
    sort(countsVec.begin(), countsVec.end(), compare); 
    int j = 0; 
    for(j = 0 ; j < countsVec.size(); j++){
      if(j >= 50)
        break; 
      arr[j*2][i] = countsVec[j].first; 
      arr[j*2 + 1][i] = countsVec[j].second; 
    }
    for(; j < mCol; j++){
      arr[j*2][i] = 0; 
      arr[j*2  + 1][i] = 0; 
    }
  }
  R = mCol * 2; 
}

int main(){
  int r, c, k; 
  cin >> r >> c >> k; 

  init(); 
  for(int i = 0; i < R; i++){
    for(int j = 0; j < C; j++){
      cin >> arr[i][j]; 
    }
  }

  int t = 0; 
  bool success = true; 
  while(check(r-1, c-1, k) == false){ 
    if(R >= C){
      uploadRow(); 
    }
    else{
      uploadCol(); 
    }
    //print(); 
    t++; 
    if(t > 100){
      success = false; 
      break; 
    }
  }

  if(success == false)
    cout << -1 << endl; 
  else 
    cout << t << endl; 
  return 0; 
}