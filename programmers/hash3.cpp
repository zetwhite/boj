#include <string>
#include <vector>
#include <unordered_map> 
#include <iostream> 
#include <cmath> 
#include <algorithm> 

using namespace std;

vector<vector<int>> combination(int total, int m){
  vector<vector<int>> result; 
  vector<int> ind; 
  for(int i = 0; i < (total - m); i++)
    ind.push_back(0); 
  for(int i = 0; i < m; i++)
    ind.push_back(1); 
  do{
    result.push_back(ind); 
  }
  while(next_permutation(ind.begin(), ind.end())); 
  return result; 
}

int pickMatching(vector<int>& pickidx, vector<string>& idx_type, unordered_map<string, int>& cottage){
  int match = 1; 
  for(int i = 0; i < pickidx.size(); i++){
    if(pickidx[i] == 0)
      continue; 
    string ctype = idx_type[i]; 
    auto it = cottage.find(ctype); 
    match *= it->second; 
  }
  return match; 
}

int solution(vector<vector<string>> clothes) {

    vector<string> type; 
    unordered_map<string, int> cottage; 

    for(int i = 0; i < clothes.size(); i++){
      auto it = cottage.find(clothes[i][1]); 
      if(it == cottage.end()){
        cottage.insert({clothes[i][1], 1}); 
        type.push_back(clothes[i][1]); 
      }
      else{
        it->second++; 
      }
    }

    if(type.size() == 30){
      return pow(2, 30) - 1; 
    }

    int count = clothes.size(); 
    int n = type.size();
    if(type.size() != 1) {
      int all = 1; 
      for(int i = 0; i < type.size(); i++){
        all *= cottage[type[i]]; 
      }
      count += all;
    } 
    vector<int> picks;
    for(int k = 2; k < n; k++){
      //combination(n, k, 0, picks, res); 
      //cout << "combination n = " << n << ", k = " << k << endl; 
      vector<vector<int>> res = combination(n, k); 
      //cout << res.size() << endl; 
      for(int j = 0; j < res.size(); j++){
        count += pickMatching(res[j], type, cottage); 
      }
    }
    return count; 
}

int main(){
  vector<vector<string>> clothes; 
  int n; 
  cin >> n; 
  for(int i = 0; i < n; i++){
    string s1, s2 ;
    cin >> s1 >> s2; 
    vector<string> tmp;
    tmp.push_back(s1); 
    tmp.push_back(s2); 
    clothes.push_back(tmp); 
  }
  cout << solution(clothes) << endl;  
  return 0;
}