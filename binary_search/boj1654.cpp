#include <iostream> 
#include <vector> 
#include <climits> 
using namespace std;

int K, N; 
vector<int> kArray; 

long long getCount(long long n){
  long long res = 0; 
  for(auto& itr : kArray){
    res += (static_cast<long long>(itr) / n); 
  }
  return res; 
}

long long biSearch(long long min, long long max, int targetValue){
  cout << "( " << min << ", " << max << ") search" << endl; 
  if(min == max){
    return min; 
  }
  if(min + 1 == max){
    return min; 
  }

  long long minCnt = getCount(min); 
  long long maxCnt = getCount(max); 
  long long middle = (min+max+1)/2; 
  long long midCnt = getCount(middle); 


  if(midCnt < targetValue && targetValue <= minCnt)
    return biSearch(min, middle, targetValue); 
  else //(maxCnt <= targetValue && targetValue <= midCnt)
    return biSearch(middle, max, targetValue); 
}

int main(){
  cin >> K >> N;

  kArray.reserve(K);
  int tmp;  
  for(int i = 0; i < K; i++){
    cin >> tmp; 
    kArray.push_back(tmp); 
  }

  long long minValue = 1; 
  long long maxValue = static_cast<long long>(INT_MAX) + 1;  

  cout << biSearch(minValue, maxValue, N) << endl; 

  return 0;
}