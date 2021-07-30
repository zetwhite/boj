#include <iostream> 
#include <vector> 
#include <climits> 
#include <cstring>
using namespace std; 

int N, M, K; 
vector<int> rows; 
vector<int> cols; 
vector<int> scale; 
int gmin = INT_MAX; 

void print(int** arr){
  //cout << "============================" << endl; 
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      //cout << arr[i][j] << "\t"; 
    }
    //cout << endl; 
  }
}


void spinOp(int** arr, int r, int c, int s){
  for(int i = 1; i <= s; i++){
    // //cout << "scale" << i << endl; 
    int tmp = arr[r-i][c-i]; 
    for(int _r = r-i; _r < r+i; _r++){
      ////cout << "( " << _r  << ", " << c - i << ")" << endl; 
      arr[_r][c-i] = arr[_r + 1][c-i]; 
    }
    for(int _c = c-i; _c < c+i; _c++){
      ////cout << "( " << r + i << ", " << _c << ")" << endl; 
      arr[r + i][_c] = arr[r + i][_c + 1]; 
    }
    for(int _r = r +i; _r > r-i; _r--){
      ////cout << "( " << _r << ", " << c + i << ")" << endl; 
      arr[_r][c + i] = arr[_r - 1][c + i]; 
    }
    for(int _c = c + i; _c > c-i; _c--){
      ////cout << "( " << r-i << ", " << _c << ")" << endl; 
      arr[r-i][_c] = arr[r-i][_c - 1]; 
    }
    arr[r-i][c-i + 1] = tmp;  
  }
}

int getValue(int** arr){
  int min = INT_MAX; 
  for(int i = 0; i < N; i++){
    int sum = 0; 
    for(int j = 0; j < M; j++){
      sum += arr[i][j]; 
    } 
    if(min > sum)
      min = sum; 
  }
  return min; 
}

void bruteForce(int** arr, int* visit, int count){
  //cout << "called at " << count << endl; 
  
  if(count == K){
    int res =  getValue(arr);
    //cout << "res = " << res << endl; 
    if(gmin > res)
      gmin = res; 
      return; 
  }
    
  //cout << "called at " << count << endl; 
  int* _visit = new int[K]; 
  memcpy(_visit, visit, sizeof(int)*K); 

  //cout << "visit copy finished" << endl;
  for(int i = 0; i < K; i++){
    //cout << _visit[i] << endl; 
    if(_visit[i])
      continue; 
    
    int** _arr = new int*[N]; 
    for(int t = 0; t < M; t++){
      _arr[t] = new int[M]; 
      memcpy(_arr[t], arr[t], sizeof(int)*M); 
    } 
    
    _visit[i] = true; 
    //cout << "count " << count << endl; 
    //cout << "sipnOp ( " << rows[i] + 1 << ", " << cols[i] + 1 << ", " << scale[i] << ") " << endl; 
    spinOp(_arr, rows[i], cols[i], scale[i]); 
    //print(_arr); 
    bruteForce(_arr, _visit, count + 1); 
    _visit[i] = false; 
  }
}


int main(){
  cin >> N >> M >> K; 
  int** arr = new int*[N]; 
  for(int i = 0; i < M; i++){
    arr[i] = new int[M]; 
  }

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      cin >> arr[i][j]; 
    }
  }

  int r, c, s; 
  for(int i = 0; i < K; i++){
    cin >> r >> c >> s; 
    rows.push_back(r-1);
    cols.push_back(c-1); 
    scale.push_back(s);
  }

  int* visit = new int[K]; 
  for(int i = 0; i < K; i++)
    visit[i] = false; 
  bruteForce(arr, visit, 0); 
  cout << gmin << endl; 
  return 0; 
}