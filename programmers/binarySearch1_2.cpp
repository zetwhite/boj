#include <string>
#include <vector>
#include <queue> 
#include <algorithm> 
#include <iostream> 

using namespace std;

long long getMaxEnter(long long t, vector<int>& times){
  long long maxEnter = 0; 
  for(int i = 0; i < times.size(); i++)
    maxEnter += (t/times[i]); 
  return maxEnter; 
}

long long binarySearch(long long minTime, long long maxTime, long long n, vector<int>& times){
  if(minTime == maxTime)
    return minTime; 

  long long mid = (minTime + maxTime) / 2; 
  long long maxEnter = getMaxEnter(mid, times); 
  if(maxEnter >= n)
    return binarySearch(minTime, mid, n, times); 
  else
    return binarySearch(mid + 1, maxTime, n ,times); 
}

long long solution(int n, vector<int> times) {
  sort(times.begin(), times.end()); 
  int sz = times.size() - 1;
  long long minTime = times[0]; 
  long long maxTime = times[sz]*n; 
  return binarySearch( minTime, maxTime, n, times);  
}

int main(){
  int n; 
  int s; 
  cin >> n >> s;
  int t; 
  vector<int> ti; 
  for(int i = 0; i < s; i++){
    cin >> t; 
    ti.push_back(t); 
  }
  cout << solution(n, ti) << endl; 
  return 0; 
}

