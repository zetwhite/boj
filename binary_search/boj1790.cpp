#include <iostream> 

using namespace std; 

char tmp[1000'000]; 

int countSpace(long long n){
  int cnt = 0; 
  while( n > 0){
    n = n / 10; 
    cnt ++; 
  }
  return cnt; 
}

int main(){
  long long cnt = 0; 
  for(long long i = 1; i < 15000; i++){
    cnt += countSpace(i); 
    if( i % 10 == 0 )
      cout << i << ", \tsize : " << cnt << endl; 
    if( cnt > 1000'000'000)
      break; 
  }
  return 0; 
}