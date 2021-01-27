//TLE at TC 6, 7 and 8

#include <string>
#include <vector>
#include <queue> 
#include <algorithm> 
#include <iostream> 

using namespace std;
typedef pair<long long, long long> coo; 

class Compare{
public: 
    bool operator() (const pair<long long, long long>& left, const pair<long long, long long>& right){
        return left.second > right.second; 
    }
}; 

long long gcd(long long a, long long b){
  while(b != 0){
    long long r = a % b; 
    a = b; 
    b = r; 
  }
  return a; 
}

long long getLCM(vector<int> times){
  if(times.size() == 1)
    return times[0]; 
  long long lcm = times[0]*times[1]/gcd(times[0], times[1]); 
  for(int i = 3; i < times.size()-2; i++){
    lcm = lcm * times[i] / gcd(lcm, times[i]); 
  }
  return lcm; 
}

long long solution(int n, vector<int> times) {
    priority_queue<coo, vector<coo>, Compare> pq; 
    
    for(int i = 0; i < times.size(); i++){
        pq.push({times[i], times[i]}); 
    }

    long long lcm = getLCM(times); 
    long long cnt = 0; 
    for(int i = 0; i < times.size(); i++){
      cnt += (lcm/times[i]); 
    }

    int q = n / cnt; 
    int r = n % cnt; 
    long long commonTime = q * lcm; 

    long long maxTime = 0; 
    for(int i = 0; i < r; i++){
      coo spend =  pq.top(); 
      if(maxTime < spend.second)
        maxTime = spend.second; 

      pq.pop(); 
      pq.push({spend.first, spend.first + spend.second}); 
    }
    
    return maxTime + commonTime; 
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

