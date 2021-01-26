#include <string>
#include <vector>
#include <algorithm> 
#include <unordered_map>
#include <iostream> 

using namespace std;

vector<int> maxPoint(unordered_map<int, pair<int, int>>& rr){
    vector<int> maxCross; 
    for(auto q = rr.begin(); q != rr.end(); q++){
        for(int z = 0; z <= 1; z++){
          vector<int> crs; 
          int point; 
          if(z == 1)
            point = q->second.first;  
          else 
            point = q->second.second; 

          for(auto it = rr.begin(); it != rr.end(); it++){
            pair<int, int> pd = it->second; 
            if( pd.first <= point && point <= pd.second)
              crs.push_back(it->first); 
          }
          if(maxCross.size() < crs.size()){
              maxCross = crs; 
          }
        }
    }
    return maxCross; 
}

int solution(vector<vector<int>> routes) {
    int answer = 0;
    unordered_map<int, pair<int, int>> rr; 
    for(int i = 0;i < routes.size(); i++){
        rr[i] = pair<int, int>(routes[i][0], routes[i][1]); 
    }
    
    while(!rr.empty()){
        vector<int> crs = maxPoint(rr); 
        for(int i = 0; i < crs.size(); i++){
            rr.erase(crs[i]); 
        }
        answer++; 
    }
    return answer;
}