#include <string>
#include <vector>
#include <iostream>
#include <unordered_map> 

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
  unordered_multimap <string, int> mm; 
  for(int i = 0;i < participant.size(); i++)
    mm.insert({participant[i], i});

  for(int i = 0; i < completion.size(); i++){
    auto range = mm.equal_range(completion[i]); 
    mm.erase(range.first); 
  }
  
  vector<string> res; 
  for(auto it = mm.begin(); it != mm.end(); it++){
    res.push_back(it->first); 
  }
  return res[0]; 
}

int main(){
  vector<string> ps; 
  vector<string> cs; 

  int n; 
  cin >> n;
  string s;  
  for(int i = 0; i < n; i++){
    cin >> s; 
    ps.push_back(s); 
  }

  cin >> n; 
  for(int i =0 ; i < n; i++){
    cin >> s; 
    cs.push_back(s); 
  }

  cout << solution(ps, cs) << endl; 

  return 0; 
}