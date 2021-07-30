#include <iostream> 
#include <vector> 
#include <algorithm>
#include <queue> 
using namespace std; 

typedef pair<int, int> pii; 

int N, M; 
int dest, src; 
vector<pii>* tmps; 
vector<pii>* nexts; 

int* weights; 

struct compare{
  bool operator()(pii& a, pii& b){
    return a.second < b.second; 
  }
}; 

priority_queue<pii, vector<pii>, compare> dijk_next; 

ostream& operator<<(ostream& os, const pii& i ){
    os << "(" <<  i.first << ", " << i.second << ")"; 
    return os;
}

bool cmp(pii& a, pii& b){
  if(a.first == b.first)
    return a.second > b.second; 
  return a.first < b.first; 
}

void getInput(){
  cin >> N >> M; 
  tmps = new vector<pii>[N+1]; 
  nexts = new vector<pii>[N+1]; 
  weights = new int [N+1]; 
  for(int i = 0; i <= N; i++){
    weights[i] = 0; 
    //nexts[i].reserve(M); 
    //tmps[i].reserve(M); 
  }
  pii con; 
  int _dest; 
  int a, b, c; 
  for(int i = 0; i < M; i++){
    cin >> a >> b >> c; 
    tmps[a].emplace_back(b, c); 
    tmps[b].emplace_back(a, c); 
  }
  for(int i = 1; i <= N; i++){
    if(tmps[i].size() == 0)
      continue; 
    //cout << "at round " << i << endl; 
    sort(tmps[i].begin(), tmps[i].end(), cmp); 
    auto it = tmps[i].begin();     
    nexts[i].push_back(*it); 

    it = next(it, 1); 
    while(it != tmps[i].end()){
      
      if(it->first != nexts[i].back().first){
        nexts[i].push_back(*it); 
        //cout << "push back" << *it << endl; 
      }

      it++; 
    }
  }

  cin >> src >> dest; 
}


int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  getInput(); 
  /*debug getInput 
  for(int i = 1; i <= N; i++){
    for(auto &i : nexts[i]){
      cout << i << ", "; 
    }
    cout << endl; 
  }*/


  weights[src] = 2'000'000'000; 
  for(auto& it: nexts[src]){
    //cout << "push " << it << endl;
    weights[it.first] = it.second;
    dijk_next.push(it); 
  }

  while(!dijk_next.empty()){
    pii here = dijk_next.top(); 
    dijk_next.pop(); 
    //cout << "=====================" << endl; 
    //cout << "here = " << here << endl; 
    for(auto& it: nexts[here.first]){
      pii t = it; 
      t.second = min(weights[here.first], it.second); 

        //cout << it << ", " << "weight = " << weights[it.first] << endl; 
      if(weights[t.first] < t.second) {
          //cout << "push " << t << endl;
        weights[t.first] = t.second; 
        dijk_next.push(t); 
      }
    }

  }

  cout << weights[dest] << endl; 
  return 0; 
}