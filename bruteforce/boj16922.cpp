#include <iostream> 
#include <set> 
#include <cstring> 
using namespace std; 

set<int> storage;
bool visit[25][1005];  
int N; 

void findNext(int space, int num, int max){
  if(space == N){
    storage.insert(num); 
    return; 
  }
  
  if(visit[space][num]) 
    return;  
  visit[space][num] = true; 

  findNext(space + 1, num + 1, max); 

  if(max >= 5){
    findNext(space + 1, num + 5, 5); 
  }

  if(max >= 10){
    findNext(space + 1, num + 10, 10); 
  }

  if(max >= 50){
    findNext(space + 1, num + 50, 50); 
  }
}

int main(){
  cin >> N; 

  for(int i = 0; i <= N; i++){
    memset(visit[i], 0, sizeof(visit[i])); 
  }
  findNext(0, 0, 50); 
  cout << storage.size() << endl; 
  return 0; 
}
