#include <iostream> 
#include <list> 
using namespace std; 
int N, K; 
int cSecurity[200]; 
bool isRobot[200]; 

class Robot{
public: 
  int location; 
  Robot():location(0){}
}; 
list<Robot> robots; 

void movContainers(){
  int end = cSecurity[2*N-1]; 
  for(int i = 2*N - 1; i >= 1; i--){
    cSecurity[i] = cSecurity[i-1]; 
  }
  cSecurity[0] = end; 

  bool rend = isRobot[2*N -1]; 
  for(int i = 2*N - 1; i >= 1; i--){
    isRobot[i] = isRobot[i-1]; 
  }
  isRobot[0] = rend; 
  isRobot[N-1] = false; 

  auto it = robots.begin(); 
  while(it != robots.end()){
    it->location++; 
    if(it->location == N-1){
      robots.erase(it++); 
    }
    else
      it++; 
  }
}

void movRobots(){
  auto it = robots.begin(); 
  while(it != robots.end()){
    int nextLoc = it->location + 1;

    if(cSecurity[nextLoc] > 0 && isRobot[nextLoc] == false){
      isRobot[it->location] = false; 
      isRobot[nextLoc] = true; 
      cSecurity[nextLoc]--; 
      it->location = nextLoc; 
    }

    if(it->location == N-1){
      robots.erase(it++); 
      isRobot[N-1] = false; 
    }
    else
      it++; 
  }
}

void upLoadRobot(){
  if(isRobot[0] == false && cSecurity[0] > 0) {
    robots.push_back(Robot()); 
    cSecurity[0]--; 
    isRobot[0] = true; 
  }
}

int checkSecurity(){
  int cnt = 0; 
  for(int i = 0; i < 2*N; i++){
    if(cSecurity[i] <= 0){
      cnt++; 
    }
  }
  return cnt; 
}

int main(){
  cin >> N >> K; 
  for(int i = 0; i < 2*N; i++){
    cin >> cSecurity[i]; 
    isRobot[i] = false; 
  }
  int stage = 1; 
  while(1){
    movContainers(); 
    movRobots();
    upLoadRobot(); 
    int cnt = checkSecurity(); 
    if(cnt >= K)
      break; 
    stage++; 
  }
  cout << stage << endl; 
  return 0; 
}