#include <iostream> 
#include <vector> 
using namespace std; 

void doCalc(vector<char>& ops, vector<int>& nums, int idx){
  char _op = ops[idx]; 
  int value = 0; 
  if(_op == '+'){
    value = nums[idx] + nums[idx + 1]; 
  }
  else if(_op == '-'){
    value = nums[idx] - nums[idx + 1]; 
  }
  else if( _op == '*'){
    value = nums[idx] * nums[idx + 1]; 
  }
  ops.erase(next(ops.begin(), idx)); 
  nums.erase(next(nums.begin(), idx));
  nums[idx] = value;  
}

int maxValue(vector<char> ops, vector<int> nums){
  if(ops.size() == 0)
    return nums[0]; 
  
  int max = 0; 
  for(int i = 0; i < ops.size(); i++){
    vector<char> newOps = ops; 
    vector<int> newNums = nums; 
    doCalc(newOps, newNums, i); 
    int _max = maxValue(newOps, newNums);
    if(_max > max)
      max = _max;  
  }
  return max; 
}


int main(){
  int N; 
  cin >> N; 
  vector<char> ops; 
  vector<int> nums;
  char c;  
  for(int i = 0; i < N/2 + 1; i++){
    cin >> c; 
    nums.push_back(c - '0'); 
    if(i != N/2){
      cin >> c; 
      ops.push_back(c); 
    }
  }

  cout << maxValue(ops, nums) << endl; 
  return 0; 
}