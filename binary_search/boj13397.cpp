#include <iostream> 
#include <vector> 

using namespace std; 
int N, M; 
vector<int> arr; 

int minPossible(int q){
  int m = 1;
  int min = arr[0]; 
  int max = arr[0];  
  //cout << arr[0] << " "; 
  for(int j = 1; j < arr.size(); j++){
    if(arr[j] < min)
      min = arr[j]; 
    if(arr[j] > max)
      max = arr[j]; 
    if(max - min > q){
      //cout << " || "; 
      m++; 
      min = arr[j]; 
      max = arr[j]; 
    }
  }
  return m; 
}

int binarySearch(int min, int max){
  //cout << "Try (" <<  min << ", " << max << ") = mid: " << (min + max) /2 << endl; 
  if(min == max || min + 1 == max)
    return max; 

  int mid = (min + max) / 2; 
  int a = minPossible(mid); 
  if(a <= M)
    return binarySearch(min, mid); 
  else 
    return binarySearch(mid, max); 
}

int main(){
  cin >> N >> M; 
  int _t; 
  int max = 0; 
  int min = 200000; 
  for(int i, t = 0; i < N; i++){
    cin >> _t; 
    if(_t > max)
      max = _t; 
    if(_t < min)
      min = _t; 
    arr.emplace_back(_t); 
  }

  cout << binarySearch(-1, max - min) << endl; 

  return 0; 
}