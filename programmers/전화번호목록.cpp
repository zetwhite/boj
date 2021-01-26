#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Node{
public :
  int charIdx; 
  int refcnt; 
  bool end; 
  Node* parent; 
  Node* children[10];
  Node(Node* p, int c, int cnt = 0){
    charIdx = c; 
    parent = p; 
    refcnt = cnt; 
    end = false; 
    for(int i = 0; i < 10; i++)
      children[i] = nullptr; 
  } 
}; 

class Trie{
public: 
  Node root; 

  Trie():root(nullptr, -1, 0){}

  bool add(string s){
    bool checkPre = false; 
    Node* here = &root; 
    for(int i = 0; i < s.size(); i++){

      if(here->end)
        checkPre = true; 

      int charIdx = s[i] - '0'; 
      if(here->children[charIdx] == nullptr){
        here->children[charIdx] = new Node(here, charIdx, 0); 
        here = here->children[charIdx]; 
      }
      else{
        here = here->children[charIdx]; 
        here->refcnt++; 
      }
      //cout << "successfully add " << s[i] << endl; 
    }
    here->end = true; 
    if(here->refcnt > 0)
      checkPre = true; 
    return checkPre; 
  }
}; 

bool solution(vector<string> phone_book) {
    Trie trie; 
    bool answer = true;
    for(int i = 0; i < phone_book.size(); i++){
      if(trie.add(phone_book[i]))
        answer = false; 
    }
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

  cout << solution(ps) << endl; 

  return 0; 
}