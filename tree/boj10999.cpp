#include <stdio.h> 
#include <iostream> 
using namespace std;
typedef long long ll;

class SegTree{
private: 
  int iSize; 
  int iSrc; 
  ll* arr; 

  ll getNearestPower(ll a){
    ll power = 2; 
    while(1){
      if((power - a) <= 0){
        return power; 
      }
      power = power << 1; 
    }
  }

public: 
  SegTree(int length, ll* src){

    iSize = getNearestPower(length); 
    iSrc = iSize / 2; 
    arr = new ll[iSize]; 
    memcpy(arr + iSrc, src, length);

    for(int i = iSize-1; i >=(iSrc + length); i--){
      arr[i] = 0; 
    }  

    for(int i = iSrc; i >= 1; i--){
      arr[i] = arr[2*i] + arr[2*i + 1];  
    }
  }
}; 

int main(){
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, M, K; 
  cin >> N >> M >> K; 

  ll arr[100'001]; 
  for(int i = 0; i < N; i++){
    cin >> arr[i]; 
  }

  return 0; 
}