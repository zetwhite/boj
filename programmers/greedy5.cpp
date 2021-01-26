#include <string>
#include <vector>
#include <algorithm> 
#include <iostream> 

using namespace std;

class Union{
public: 
  Union(int n){
    arr = new int[n]; 
    for(int i = 0; i < n; i++)
      arr[i] = i; 
  }
  int* arr; 

  int getTop(int idx){
    int before = idx;
    while(arr[idx] != idx){
      idx = arr[idx]; 
    }
    arr[before] = idx; 
    return idx; 
  }

  bool sameGroup(int i1, int i2){
    int top1 = getTop(i1); 
    int top2 = getTop(i2); 
    return top1 == top2; 
  }

  void merge(int i1, int i2){
    int top1 = getTop(i1); 
    int top2 = getTop(i2); 
    arr[i2] = top1; 
    arr[top2] = top1; 
  }
}; 

bool cmp(vector<int>& v1, vector<int>& v2){
  return v1[2] <= v2[2]; 
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;

    Union uni(n); 

    sort(costs.begin(), costs.end(), cmp); 

    for(auto c : costs){
      if(uni.sameGroup(c[0], c[1]))
        continue; 
      uni.merge(c[0], c[1]); 
      answer+= c[2]; 
    }

    return answer;
}

int main(){
  int n; 
  cin >> n; 

  int m; 
  cin >> m; 
  vector<vector<int>> all; 
  for(int i = 0; i < m; i++){
    int a, b, c; 
    cin >> a >> b >> c; 
    vector<int> tmp; 
    tmp.push_back(a); 
    tmp.push_back(b); 
    tmp.push_back(c); 
    all.push_back(tmp); 
  }
  cout << solution(n, all); 
  return 0; 
}