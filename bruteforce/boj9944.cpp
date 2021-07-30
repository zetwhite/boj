#include <iostream> 
#include <algorithm> 
#include <climits> 
using namespace std;

#define WALL '*'
#define EMPTY '.'

pair<int, int> DIR[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; 


bool** copyVisit(bool** visit, int N, int M){
  bool** newVisit = new bool*[N+2]; 
  for(int i = 0; i < N+2; i++){
    newVisit[i] = new bool[M+2]; 
  }

  for(int i = 0; i < N+2; i++){
    for(int j = 0; j < M+2; j++){
      newVisit[i][j] = visit[i][j]; 
    }
  }
  return newVisit; 
}

void printVisit(bool** visit, int N, int M){
  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= M; j++){
      cout << visit[i][j] << "\t"; 
    }
    cout << endl; 
  }
}

bool checkProb(bool** visit, int N, int M, int r, int c){
  // cout << "=====================================" << endl; 
  // printVisit(visit, N, M); 
  int count = 0; 
  for(int i = 0; i < 4; i++){
    int newR = r + DIR[i].first; 
    int newC = c + DIR[i].second; 
    if(visit[newR][newC] == false)
      count++; 
  }
  if(count >= 2)
    return false; 
  return true; 
}

int findWayDFS(bool** visit, int N, int M, int r, int c, int count, const int emptycnt, int fillcnt){
  /*cout << "==== count = " << count << endl; 
  cout << "r = " << r << ", c = " << c << endl;
  cout << "emptycnt = " << emptycnt << ", fillcnt = " << fillcnt << endl;  
  printVisit(visit, N, M); 
  */

  if(emptycnt == fillcnt)
    return count; 

  /*  
  bool success = true; 
  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= M; j++){
      if(visit[i][j] == false){
        success = false;
        break; 
      } 
      if(success == false)
        break; 
    }
  }

  if(success == true){
    return count; 
  }
  */ 
  int totalCount = INT_MAX; 
  for(int i = 0; i < 4; i++){
    int newR = r + DIR[i].first; 
    int newC = c + DIR[i].second; 
    if( visit[newR][newC] == true )
      continue; 
    
    int _fillcnt = fillcnt; 
    bool** nextVisit = copyVisit(visit, N, M); 
    while(nextVisit[newR][newC] == false){
      nextVisit[newR][newC] = true;
      _fillcnt++; 
      newR = newR + DIR[i].first; 
      newC = newC + DIR[i].second;  
    }
    int befR = newR - DIR[i].first; 
    int befC = newC - DIR[i].second; 

    int newCount = findWayDFS(nextVisit, N, M, befR, befC, count+1, emptycnt, _fillcnt); 
    //cout << "newCount = " << newCount << endl; 
    if(newCount < totalCount)
      totalCount = newCount; 

    for(int t = 0; t < N+2; t++){
      delete[] nextVisit[t]; 
    }
    delete[] nextVisit; 
  }

  return totalCount; 
}


int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  char** arr; 
  bool** visit; 

  int CASE = 1; 
  while(1){
    int N, M; 
    cin >> N >> M;
    if(cin.eof() == true)
      break; 

    arr = new char*[N+2]; 
    for(int i = 0; i < N+2; i++)
      arr[i] = new char[M+2]; 

    visit = new bool*[N+2]; 
    for(int i = 0; i < N+2; i++)
      visit[i] = new bool[M+2]; 

    for(int i = 1; i < N+1; i++){
      for(int j = 1; j < M+1; j++){
        visit[i][j] = false; 
      }
    } 
    for(int i = 0; i < N+2; i++){
      visit[i][0] = true; 
      visit[i][M+1] = true; 
    }
    for(int i = 0; i < M+2; i++){
      visit[0][i] = true; 
      visit[N+1][i] = true; 
    }

    char in; 
    int emptycnt = 0; 
    for(int i = 1; i <= N; i++){
      for(int j = 1; j <= M; j++){
        cin >> in; 
        if(in == WALL)
          visit[i][j] = true; 
        else
          emptycnt++; 
      }
    }
    
    int count = INT_MAX; 
    for(int i = 1; i <= N; i++){
      for(int j = 1; j <= M; j++){
        if(visit[i][j] == false){
          visit[i][j] = true; 
          int _count = findWayDFS(visit, N, M, i, j, 0, emptycnt, 1); 
          visit[i][j] = false; 
          if(count > _count)
            count = _count; 
        }
      }
    }

    if(count == INT_MAX)
      count = -1;
    cout << "Case " << CASE << ": " << count << endl; 
    CASE++;

    for(int i = 0; i < N+2; i++){
      delete[] visit[i]; 
    }
    delete[] visit;
  }

  return 0; 
}