#include <iostream> 
#include <vector> 
#include <cmath> 
#include <algorithm>
using namespace std; 

bool checkPossible(vector<int>& As, int B){
  int number = 0; 
  int n_cnt = 0; 
  int start = 0; 
  int cnt = 0; 
  for(int i = As.size()-1; i >= 0; i--){
    if(As[i] == 0)
      cnt++; 
    if(start == 0)
      start = As[i];
    else { 
      number = number * 10 + As[i]; 
      n_cnt++; 
    }
  }
  int res = start * pow(10, cnt); 
  res = res * pow(10, n_cnt) + number; 
  //number = number * pow(10, cnt);
  //cout << "low limit : "  << res << endl; 
  if(res <= B)
    return true; 
  return false; 
}

int findMaxNumber(int cnt, int number, vector<int> As, vector<bool> used, int B){
  if(cnt == As.size()){
    //cout << "try number : " << number << endl; 
    if(number <= B)
      return number;
    else 
      return -1;  
  }
  for(int i = 0; i < As.size(); i++){
    vector<bool> newUsed = used; 
    if(newUsed[i] == true)
      continue; 
    newUsed[i] = true; 
    int newNumber = number * 10 + As[i]; 
    int res = findMaxNumber(cnt + 1, newNumber, As, newUsed, B);
    if(res != -1)
      return res; 
  }
  return -1; 
}

int main(){
  vector<int> As; 
  int A, B; 
  cin >> A >> B; 

  while( A > 0){
    int a = A % 10; 
    As.push_back(a); 
    A = A / 10; 
  }
  sort(As.begin(), As.end(), greater<int>()); 

  bool res = checkPossible(As, B); 
  if(res == false){
    cout << "-1" << endl; 
    return 0; 
  }
  vector<bool> used; 
  for(int i = 0; i < As.size(); i++)
    used.push_back(false); 
  
  int resNumber = findMaxNumber(0, 0, As, used, B); 
  cout << resNumber << endl; 

  return 0; 
}

