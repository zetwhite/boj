#include <string>
#include <vector>
#include <queue>
#include <algorithm> 
#include <iostream> 
using namespace std;
typedef pair<int ,int> coo; 

bool cmp(vector<int>& left, vector<int>& right){
    return left[0] < right[0]; 
}

struct myComp { 
    constexpr bool operator()( 
        pair<int, int> const& c1, 
        pair<int, int> const& c2) 
        const noexcept 
    { 
      if(c1.second == c2.second)
        return c1.first < c2.first; 
      return c1.second > c2.second; 
    } 
}; 

void updateReq(int time, int& idx, vector<vector<int>>& jobs, priority_queue <coo, vector<coo>, myComp>& req){
    if(jobs.size() <= idx)
        return; 
    //cout << "time = " << time << endl; 
    //cout << "req start " << jobs[idx][0] << endl; 
    while(jobs[idx][0] <= time){
        //cout << jobs[idx][0] << ", " << jobs[idx][1] << endl; 
        req.push({jobs[idx][0], jobs[idx][1]}); 
        idx++; 
        if(jobs.size() <= idx)
          break; 
    }
}

int solution(vector<vector<int>> jobs) {
    int answer = 0;
    
    sort(jobs.begin(), jobs.end(), cmp);
    
    for(auto i : jobs){
      //cout << i[0] << ", " << i[1] << endl; 
    }
    int idx = 0; 
    int time = jobs[0][0]; 
    priority_queue <coo, vector<coo>, myComp> req; 
    updateReq(time, idx, jobs, req); 

    int responseTime = 0; 
    while(req.empty() == false){
      coo task = req.top();
      req.pop(); 
      //cout << "time = " << time << endl; 
      //cout << "picked task (" << task.first << ", " << task.second << ")" << endl ; 
      time = time + task.second;  
      //cout << "updated time = " << time << endl; 
      //cout << "========================" << endl; 
      responseTime += (time - task.first); 
      updateReq(time, idx, jobs, req);

      if(req.size() == 0 && idx < jobs.size()){
        time = jobs[idx][0]; 
        updateReq(time, idx, jobs, req);
      }
    }
    return responseTime/jobs.size(); 
}

int main(){
  vector<vector<int>> jobs; 
  int n; 
  cin >> n; 
  for(int i = 0; i < n; i++){
    int a, b; 
    cin >> a >> b; 
    vector<int> tmp = {a, b}; 
    jobs.push_back(tmp); 
  }

  //cout << solution(jobs) << endl;  
  return 0; 
}