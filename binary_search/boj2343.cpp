#include <iostream> 
#include <vector> 
using namespace std; 

int N, M; 
vector<int> lessons; 

int getSum(vector<int>& a){
  int sum = 0; 
  for(auto &it : a){
    sum += it; 
  }
  return sum; 
}

bool record(int len){
  int cnt = 1; 
  int _len = 0; 
  for(auto it : lessons){
    if(it + _len > len){
      cnt++; 
      _len = it; 
      if(cnt > M){
        return false;
      } 
    }
    else{
      _len += it; 
    }
  }
  if(cnt > M)
    return false; 
  return true; 
}

int binarsySearch(int min, int max){
  if(min == max || min+1 == max){
    return max; 
  }
  int mid = (min + max)/2; 
  bool res = record(mid); 
  if(res == true){
    return binarsySearch(min, mid);
  }
  else{
    return binarsySearch(mid, max); 
  }
}

int main(){

  cin >> N >> M; 
  int t; 
  int max = 0; 
  for(int i = 0; i < N; i++){
    cin >> t; 
    if(t > max)
      max = t; 
    lessons.emplace_back(t);
  }  
  cout << binarsySearch(max-1, getSum(lessons)) << endl;  

  return 0; 
}