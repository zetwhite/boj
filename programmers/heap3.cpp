#include <string>
#include <vector>
#include <sstream>
#include <deque>
#include <algorithm> 
#include <iostream> 

using namespace std;

void print(deque<int>& a){
  for(int n : a){
    cout << n << "\t";
  }
  cout << endl; 
}

vector<int> solution(vector<string> operations) {
    vector<int> answer;
    deque<int> sortedArr; 
    
    string alpha; 
    int value; 
    for(auto op : operations){
      stringstream ss; 
      ss << op; 
      ss >> alpha >> value; 
      if(alpha == "I"){
        sortedArr.push_back(value); 
        sort(sortedArr.begin(), sortedArr.end()); 
      }
      else if(alpha == "D"){
        if(!sortedArr.empty()){
          if(value == 1){
            sortedArr.pop_back(); 
          }
          else{
            sortedArr.pop_front(); 
          }
        }
      }
      cout << "=======" << endl; 
      cout << op << endl; 
      print(sortedArr); 
    }
    if(sortedArr.empty()){
      answer.push_back(0); 
      answer.push_back(0); 
    }
    else{
      answer.push_back(sortedArr.back()); 
      answer.push_back(sortedArr.front()); 
    }
    return answer;
}

int main(){
  vector<string> s; 
  int n; 
  cin >> n; 
  for(int i = 0; i < n; i++){
    string alpha; 
    string value;  
    cin >> alpha >> value; 
    s.push_back(alpha + " " + value); 
  }
  solution(s); 
  return 0; 
}