#include <string>
#include <vector>
#include <algorithm> 
#include <iostream> 

using namespace std;

const int MAX = 1000'000'000; 

class Rock{
public: 
    int index;  
    int location; 
    int left_dist; 
    int right_dist; 
    Rock(int i, int loc, int l, int r)
    : index(i), location(loc), 
    left_dist(l), 
    right_dist(r){}
    Rock(){}
    bool operator< (Rock& other) {
        int minThis = min(left_dist, right_dist); 
        int minOther = min(other.left_dist, other.right_dist); 
        if(minThis == minOther){
            int sumThis = left_dist + right_dist; 
            int sumOther = other.left_dist + other.right_dist; 
            return sumThis < sumOther; 
        }
        return minThis < minOther; 
    }
}; 

ostream& operator<< (ostream& os, Rock& r){
  os << r.location << ", " << r.left_dist << ", " << r.right_dist; 
  return os; 
}

bool cmp(Rock* right, Rock* left){
  //return *right < *left; 
  return *left < *right; 
}

int toGetMin(Rock* rockInfo, int sz, int minDistance){
    vector<Rock*> rockPtr; 
    rockPtr.reserve(sz); 
    for(int i = 0; i < sz; i++){
      rockPtr.push_back(&(rockInfo[i])); 
    }
    int deleteCount = 0; 
    while(1){
      int last = rockPtr.size()-1; 
      int answer = min(rockPtr[0]->left_dist, rockPtr[0]->right_dist); 
      if(answer <= minDistance )
        break; 
      deleteCount++; 
      sort(rockPtr.begin(), rockPtr.end(), cmp); 
      /*for(int i = 0; i < sz; i++){
        cout << *(rockPtr[i]) << endl; 
      }*/
      last = rockPtr.size() - 1; 
      Rock* delRock = rockPtr[last];  
      rockPtr.pop_back(); 
      int index = delRock->index; 
      int newWeight = delRock->left_dist + delRock->right_dist; 
      if(index != 0){
        rockInfo[index-1].right_dist = newWeight; 
      }
      if(index != sz - 1){
        rockInfo[index+1].left_dist = newWeight; 
      }
    }
    return deleteCount; 
}

int solution(int distance, vector<int> rocks, int n) {
    sort(rocks.begin(), rocks.end()); 
    int sz = rocks.size(); 
    Rock rockInfo[sz];  
    rockInfo[0] = Rock(0, rocks[0], rocks[0],  rocks[1] - rocks[0]); 
    for(int i = 1; i < sz-1; i++){
        rockInfo[i] = Rock(i, rocks[i], rocks[i] - rocks[i-1], rocks[i+1] - rocks[i]); 
    }
    rockInfo[sz-1] = Rock(sz-1, rocks[sz-1], rocks[sz-1] - rocks[sz-2], distance - rocks[sz-1]); 
    
    int left = 0; 
    int right = distance; 
    int mid = 0; 
    while(left < right){
      mid = (left + right)/2; 
      int del = toGetMin(rockInfo, sz, mid); 
      if(del > n){
        right = mid; 
      }
      else{
        left = mid+1; 
      }
    }
    return mid; 
}

int main(){
  int dist; 
  cin >> dist;
  vector<int> v; 
  int r_sz; 
  cin >> r_sz; 
  for(int i = 0; i < r_sz; i++){
    int t; 
    cin >> t; 
    v.push_back(t); 
  }
  int del ; 
  cin >> del ; 
  cout << solution(dist, v, del); 
  return 0; 
}