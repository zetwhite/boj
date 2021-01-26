#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Node{
public :
  int charIdx; 
  int endCnt; 
  Node* parent; 
  Node* children[26];
  Node(Node* p, int c, int cnt = 0){
    charIdx = c; 
    parent = p; 
    endCnt = cnt; 
    for(int i = 0; i < 26; i++)
      children[i] = nullptr; 
  } 
}; 

class Trie{
public: 
  Node root; 

  Trie():root(nullptr, -1, 1){}

  void add(string s){
    Node* here = &root; 
    for(int i = 0; i < s.size(); i++){
      int charIdx = s[i] - 'a'; 
      if(here->children[charIdx] == nullptr){
        here->children[charIdx] = new Node(here, charIdx, 0); 
      }
      here = here->children[charIdx]; 
      //cout << "successfully add " << s[i] << endl; 
    }
    here->endCnt++; 
  }

  bool remove(string s){
    Node* here = &root; 
    for(int i = 0; i < s.size(); i++){
      int charIdx = s[i] - 'a'; 
      if(here->children[charIdx] == nullptr){
        return false; 
      }
      here = here->children[charIdx]; 
    }
    //cout << "successuffly reach at " << char(here->charIdx+'a') << endl; 

    here->endCnt--; 
    
    while(here->endCnt == 0){
      Node* tmpPtr = here; 
      int tmpIdx = here->charIdx; 
      here = here->parent; 
      here->children[tmpIdx ]= nullptr;  
      //delete tmpPtr; 
    }
    return true; 
  }

  string getLast(){
    //cout << "getLast!" << endl; 
    string res;
    Node* here = &root; 
    while(here->endCnt == 0 || here->parent == nullptr){
      for(int i = 0; i < 26; i++){
        if(here->children[i] != nullptr){
          res.push_back(static_cast<char>(i + 'a')); 
          //cout << "find " << static_cast<char>(i + 'a') << endl; 
          here = here->children[i]; 
          break; 
        }
      }
    }
    return res; 
  }
}; 

string solution(vector<string> participant, vector<string> completion) {
  Trie trie; 
  for(int i = 0;i < participant.size(); i++){
    trie.add(participant[i]); 
  }  
  for(int i = 0; i < completion.size(); i++){
    trie.remove(completion[i]); 
  }
  string answer = trie.getLast(); 
  return answer;
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