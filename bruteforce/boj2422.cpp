#include <iostream> 
#include <vector> 
using namespace std; 

int N, M; 
vector<int> hateRelation[201];

void findCombi(int index, int count, vector<bool> block, int& res){
  if(count == 3){
    res++; 
    /*for(int i = 0; i < resArr.size(); i++)
      cout << resArr[i] << " "; 
    cout << endl;*/ 
    return; 
  }
  if(index > N){
    return; 
  }
  //go without select nothing 
  findCombi(index+1, count, block, res); 
  //go with selecte indexed.. 
  if(block[index] == false){
    for(int i = 0; i < hateRelation[index].size(); i++){
      block[hateRelation[index][i]] = true; 
    }
    //resArr.push_back(index); 
    findCombi(index+1, count+1, block, res); 
  }
}

int main(){
  cin >> N >> M; 
  
  int a, b; 
  for(int i = 0; i < M; i++){
    cin >> a >> b; 
    hateRelation[a].push_back(b); 
    hateRelation[b].push_back(a); 
  }

  vector<bool> block; 
  block.reserve(N+1); 
  for(int i = 0; i <= N+1; i++){
    block.emplace_back(false); 
  }
  vector<int> resArr; 
  int res; 
  findCombi(1, 0, block, res); 
  cout << res << endl; 
  return 0; 
}