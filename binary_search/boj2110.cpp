#include <iostream> 
#include <vector> 
#include <algorithm> 

using namespace std; 

int N, C; 
vector<int> Cs; 

bool install(int S){
  int gap = 0; 
  int count = C - 1; 
  int idx = 0; 

  //cout << "install at " << Cs[0] << endl; 
  while(idx < Cs.size()){
    idx++; 
    if(count == 0)
      return true; 
    int gap = (Cs[idx] - Cs[idx-1]);
    while(idx < Cs.size() && gap < S){
      idx++; 
      gap += (Cs[idx] - Cs[idx-1]); 
    }
    //cout << "install at " << Cs[idx] << endl; 
    gap = 0; 
    count--; 
  }
  return false; 
}

int biSearch(int minSpace, int maxSpace){
  //cout << "search ( " << minSpace << ", " << maxSpace << ")" << endl;
  if(minSpace + 1 == maxSpace)
    return minSpace; 
  if(minSpace == maxSpace)
    return maxSpace; 
  
  int midSpace = (minSpace + maxSpace) / 2; 
  //cout << "install space " << midSpace << " is ...."  << endl;
  bool res = install(midSpace); 
  //cout << "install space " << midSpace << " is " << res << endl;
  if(res){
    return biSearch(midSpace, maxSpace); 
  }
  else{
    return biSearch(minSpace, midSpace); 
  }
  
}

int main(){
  cin >> N >> C; 
  int tmp; 
  for(int i = 0; i < N; i++){
    cin >> tmp; 
    Cs.push_back(tmp); 
  }
  sort(Cs.begin(), Cs.end()); 
  int maxGap = Cs[N-1] - Cs[0] + 1;
  cout << biSearch(1, maxGap) << endl; 
  return 0; 
}