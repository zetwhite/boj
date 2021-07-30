#include <iostream> 
#include <vector> 
#include <climits> 
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

int getValue(vector<char> ops, vector<int> nums, vector<bool> seq){
  int done = 0; 
  for(int i = 0; i < seq.size(); i++){
    if(seq[i] == true){
      doCalc(ops, nums, i - done); 
      done++; 
    }
  }
  while(ops.size() != 0){
    doCalc(ops, nums, 0); 
  }
  return nums[0]; 
}


void getOpSequence(int opSize, int index, vector<bool> seq, vector<vector<bool>>& res){
  if(index == opSize){
    res.push_back(seq); 
    return; 
  }
  if(index == 0){
    for(int i = 0; i < opSize; i++)
      seq.push_back(false);
    getOpSequence(opSize, index + 1, seq, res); 

    seq[0] = true; 
    getOpSequence(opSize, index + 1, seq, res); 
  }
  else if(seq[index - 1] == false){
    getOpSequence(opSize, index + 1, seq, res);
    seq[index] = true; 
    getOpSequence(opSize, index+1, seq, res);     
  }
  else if(seq[index -1] == true){
    getOpSequence(opSize, index+1, seq, res); 
  }
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
  vector<bool> seq; 
  vector<vector<bool>> res;
  getOpSequence(ops.size(), 0, seq, res); 

  int max = INT_MIN; 
  for(int i = 0; i < res.size(); i++){
    /*for(int j = 0;j < res[i].size(); j++){
      cout << res[i][j] << " ";
    }
    cout << endl;*/   
    int _max = getValue(ops, nums, res[i]); 
    //cout << " => vlaue => " << _max << endl; 
    if(_max > max)
      max = _max; 
  }
  cout << max << endl; 
  return 0; 
}