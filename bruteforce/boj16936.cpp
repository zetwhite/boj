#include <iostream> 
#include <map> 
#include <vector> 
using namespace std;

typedef long long ll; 

map<ll, ll> setting;  
ll N; 

bool findWay(ll here, ll count, map<ll, ll> visit, vector<ll>& log){
  //cout << "try " <<  here << endl; 
  if(count == N)
    return true; 
  
  if(here%3 == 0){
    auto it1 = setting.find(here/3);
    if(it1 != setting.end()){
      auto it2 = visit.find(here/3);  
      if(it2 == visit.end()){
        visit.insert({here/3, 1}); 
        log.push_back(here/3); 
        bool res = findWay(here/3, count+1, visit, log); 
        if(res == true)
          return true; 
      }
      else if(it1->second >= it2->second){
        it2->second ++; 
        log.push_back(here/3); 
        bool res = findWay(here/3, count+1, visit, log); 
        if(res == true)
          return res; 
      }
    
      log.pop_back(); 
      if( visit[here/3] == 1 )
        visit.erase(here/3); 
      else
        visit[here/3] = visit[here/3] - 1;
    }
  }

  auto it1 = setting.find(here * 2); 
  if(it1 != setting.end()){
    auto it2 = visit.find(here * 2); 
    if(it2 == visit.end()){
      visit.insert({here*2, 1}); 
      log.push_back(here*2); 
      bool res = findWay(here*2, count+1, visit, log); 
      if(res == true)
        return true;
    }
    else if(it1->second >= it2-> second){
      it2->second++; 
      log.push_back(here*2); 
      bool res = findWay(here*2, count + 1, visit, log); 
      if(res == true)
        return res; 
    }
  }

  log.pop_back(); 
  return false; 
}

int main(){
  cin >> N; 
  long long tmp; 
  for(ll i = 0; i < N; i++){
    cin >> tmp; 
    auto it = setting.find(tmp); 
    if( it != setting.end()){
      it->second++; 
    }
    else{
      setting.insert({tmp, 1}); 
    }
  }
  
  vector<ll> way; 
  map<ll, ll> :: iterator it; 
  for(it = setting.begin(); it != setting.end(); it++){
    map<ll, ll> visit; 
    way.push_back(it->first); 
    visit[it->first] = 1; 
    bool res = findWay(it->first, 1, visit, way); 
    if(res == true){
      break; 
    }
    way.clear(); 
  }
  
  for(ll i = 0; i < N; i++)
    cout <<way[i] << " "; 

  return 0; 
}