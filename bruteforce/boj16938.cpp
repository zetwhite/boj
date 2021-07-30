#include <iostream> 
#include <vector>
using namespace std; 

int N, L, R, X; 
vector<int> As; 

void search(int idx, int sum, int _min, int _max, int c, int& count){
  if(idx >= N)
    return;  

  search(idx+1, sum, _min, _max, c, count); 
  
  int newSum = sum + As[idx]; 
  int newMin = min(_min, As[idx]);
  int newMax = max(_max, As[idx]);
  int newX = newMax - newMin; 
  c = c + 1; 
  if(L <= newSum &&  newSum <= R && newX >= X && c >= 2){
    count++; 
  }
    search(idx+1, newSum, newMin, newMax, c+1, count); 
}

int main(){
  cin >> N >> L >> R >> X;
  int a;  
  for(int i = 0; i < N; i++){
    cin >> a; 
    As.push_back(a); 
  }

  int count = 0; 
  search(0, 0, 2000'000'000, 0, 0, count); 
  cout << count << endl; 
  return 0; 
}