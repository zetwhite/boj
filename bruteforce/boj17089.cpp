#include <iostream> 
#include <set> 
#include <climits> 
using namespace std; 

int findThree(int N, set<int>* frs, int me){
  if(frs[me].size() < 2)
    return INT_MAX; 
  int cnt = INT_MAX; 

  int _cnt = 0; 
  set<int>::iterator i, j; 

  for(i = frs[me].begin(); i != frs[me].end(); i++){
    if(*i < me)
      continue;
    for(j = next(i); j != frs[me].end(); j++){
      if(i == j)
        continue; 

      bool check1 = (frs[*i].find(*j) != frs[*i].end()); 
      bool check2 = (frs[*j].find(*i) != frs[*j].end()); 

      if(check1 && check2){
        //cout << "find set(" << me << ", " << *i << ", " << *j << endl; 
        _cnt = frs[me].size() + frs[*i].size() + frs[*j].size() - 6; 
        //cout << _cnt << endl;
        if(cnt > _cnt)
          cnt = _cnt; 
      }

    }
  }
  return cnt; 
}

int main(){
  int N, M; 
  cin >> N >> M; 
  set<int>* friends = new set<int>[N+1]; 

  int a, b; 
  for(int i = 0; i < M; i++){
    cin >> a >> b; 
    friends[a].insert(b); 
    friends[b].insert(a); 
  }

  int res = INT_MAX; 
  for(int i = 1; i <= N; i++){
    int _res = findThree(N, friends, i); 
    if(res > _res)
      res = _res; 
  }
  if(res == INT_MAX)
    cout << -1 << endl; 
  else 
    cout << res << endl; 
  return 0; 
}