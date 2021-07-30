#include <iostream> 
#include <cmath>
using namespace std; 

long long N; 
long long K; 

long long findIndex(long long a){
  double cnt = 0; 
  a--; 
  for(long long i = 1; i <= N; i++){
    //cout<< "\t at layer " << i << " :: "; 
      if(a/i <= 0)
        break; 
      else{
        long long _cnt = min(a/i, N); 
        if(_cnt - i >= 0){
          //cout<< (_cnt - i ) + 0.5; 
          cnt += (_cnt - i) + 0.5; 
        }
        //cout<< endl; 
      }
  }
  cnt = cnt*2 + 1; 
  //if((int(sqrt(cnt)*10))%10 == 0)
  //  cnt += 1; 
  //cout<< "findIndex of " << a + 1<< " is " << cnt << endl; 

  return static_cast<long long>(cnt); 
}

long long bSearch(long long min, long long max){
  //cout<< "try (" << min << ", " << max << ") => mid = " << (min + max)/2 << endl; 
  if(min == max || min + 1 == max)
    return min; 
  long long mid = (min + max) / 2; 
  if(findIndex(mid) <= K)
    return bSearch(mid, max); 
  else 
    return bSearch(min, mid); 
}

long long findNear(long long res){
  bool success = false; 
  for(int i = 1; i <= N; i++){
    if(res%i != 0)
      continue; 
    long long a = res/i; 
    if(a <= N){
      ////cout<< "success at " << i << endl; 
      success = true; 
      break; 
    }
  }

  if(success == true)
    return res; 
  return findNear(res + 1); 
}

int main(){
  cin >> N >> K; 
  long long res = bSearch(1, N*N + 1);  
  cout<< findNear(res) << endl; 
  return 0; 
}