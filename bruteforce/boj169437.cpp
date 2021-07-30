#include <iostream> 
#include <algorithm> 
#include <vector> 
using namespace std; 
typedef pair<int, int> pii; 

int H, W, N; 
vector<pii> squares; 

int main(){
  cin >> H >> W >> N; 
  int r, c; 
  for(int i = 0; i < N; i++){
    cin >> r >> c; 
    squares.emplace_back(r, c); 
    squares.emplace_back(c, r); 
  }
  N = N * 2; 

  int max = 0; 
  int alloc = 0; 
  int r_ = 0; 
  int c_ = 0; 
  int leftR = 0; 
  int leftC = 0; 
  
  for(int i = 0; i < N-1; i++){
    alloc = 0;
    r = squares[i].first; 
    c = squares[i].second;   
    if(!(r <= H && c <= W))
      continue;
    alloc = r*c;
    leftR = H - r; 
    leftC = W - c;
    int j = 0; 
    if(i % 2 == 0)
      j = i + 2; 
    else 
      j = i + 1;  
    for(; j < N; j++){
      r_ = squares[j].first; 
      c_ = squares[j].second; 
      if(r_ <= leftR && c_ <= W){
        int alloc1 = alloc + r_ * c_; 
        //cout << "alloc1 = (" << r << ", " << c << ") and (" << r_ << ", " << c_ << ")" << endl;  
        if(alloc1 > max)
          max = alloc1; 
      }
      else if(r_ <= H && c_ <= leftC){
        int alloc2 = alloc + r_ * c_; 
        //cout << "alloc2 = (" << r << ", " << c << ") and (" << r_ << ", " << c_ << ")" << endl;  
        if(alloc2 > max)
          max = alloc2; 
      }
    }
  }
  cout << max << endl; 
  return 0; 
}