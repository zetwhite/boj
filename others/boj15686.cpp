#include <iostream> 
#include <vector> 
#include <queue> 
#include <algorithm> 
using namespace std;


vector<vector<int>> pickChicks(int total, int m){
  vector<vector<int>> result; 
  vector<int> ind; 
  for(int i = 0; i < m; i++)
    ind.push_back(1); 
  for(int i = 0; i < (total - m); i++)
    ind.push_back(0); 
  sort(ind.begin(), ind.end()); 
  do{
    result.push_back(ind); 
  }
  while(next_permutation(ind.begin(), ind.end())); 
  return result; 
}

int getDistance(vector<pair<int, int>>& chicks, pair<int, int> home){
  int mindistacne = 10000; 
  for(int i = 0; i < chicks.size(); i++){
    int newDistacne = abs(chicks[i].first - home.first); 
    newDistacne += abs(chicks[i].second - home.second); 
    if(newDistacne <  mindistacne) 
      mindistacne = newDistacne; 
  }
  return mindistacne; 
}

int calcChickDistance(vector<pair<int, int>>& chicks, vector<pair<int, int>>& home){
  int distance = 0; 
  for(int i = 0; i < home.size(); i++){
    distance += getDistance(chicks, home[i]); 
  }
  return distance; 
}

int main(){
  int N, M; 
  vector<pair<int, int>> chicks; 
  vector<pair<int, int>> homes; 

  cin >> N >> M;
  int tmp; 
  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
      cin >> tmp; 
      if(tmp == 2)
        chicks.emplace_back(i, j); 
      else if(tmp == 1)
        homes.emplace_back(i, j); 
    }
  }

  int minDist = 100000; 
  vector<vector<int>> picks = pickChicks(chicks.size(), M); 
  for(int i = 0; i < picks.size(); i++){
    vector<pair<int, int>>  newChicks; 
    
    for(int j = 0; j < picks[i].size(); j++ ){
      if(picks[i][j] == 1)
        newChicks.push_back(chicks[j]); 
    }
    int newDist = calcChickDistance(newChicks, homes); 
    if(minDist > newDist)
      minDist = newDist; 
  }

  cout << minDist << endl; 
  return 0; 
}