#include <iostream> 
#include <vector> 
using namespace std; 

long long N, M; 
vector<int> pTime; 

long long getN(long long t){
  if(t < 0)
    return 0; 
  long long cnt = M; 
  for(auto i: pTime){
    cnt += t / i; 
  }
  return cnt; 
}

long long findTime(long long min, long long max){
  if(min == max || min + 1 == max)
    return max; 

  long long mid = (min + max)/2; 
  long long _N = getN(mid); 
  if(_N >= N){
    return findTime(min, mid); 
  }
  else
    return findTime(mid, max); 
}

vector<int> emptyPlay(long long Time){
  
  vector<int> res; 
  if(Time == 0){
    for(int i = 0; i < M; i++){
      res.push_back(i); 
    }
    return res; 
  }
  for(int i = 0; i < M;i++){
    if(Time % pTime[i] == 0){
      res.push_back(i); 
    }
  }
  for(int i : res){
    cout << i << endl; 
  }
  return res; 
}


int main(){
  cin >> N >> M; 
  int tmp; 

  for(int i = 0; i < M; i++){
    cin >> tmp; 
    pTime.push_back(tmp); 
  }
  long long t = findTime(-1, N * 30); 
  cout << "time = " << t << endl; 

  vector<int> empty = emptyPlay(t); 
  long long last = getN(t-1);
  cout << empty[ N - last - 1] + 1 << endl;     
  return 0; 
}
