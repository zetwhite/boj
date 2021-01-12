#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <cstring> 

using namespace std;
typedef pair<int, int> coo; 

int plates[51][51]; //i번째 원판, j번째 값
int turn[51][3]; //xi, di, ki
int N, M, K; 

void print(){
  cout << "====================================" << endl; 
  for(int i = 0; i < N; i++){
    for(int j = 0 ;j < M; j++){
      cout << plates[i][j] << "\t"; 
    }
    cout << endl; 
  }
}

//x번째 원판을 d방향으로 k만큼 회전시키는 함수 
void do_turn(int x, int d, int k){
  int tmp[51]; 
  if(d == 0){ //시계방향 
    for(int i = 0; i < M; i++)
      tmp[(i+k)%M] = plates[x][i]; 
  }
  else{ //반 시계 방향
    for(int i = 0; i < M; i++)
      tmp[(i-k+M)%M] = plates[x][i]; 
  }
  memcpy(plates[x], tmp, sizeof(int)*M); 
  //print(); 
}

//인접한 수를 지우는 함수, 지운 것이 하나라도 있으면 true 반환 
bool removeDup(){
  vector<coo> res;  //바로 지우지 않고 지울 위치를 res에 우선 저장 
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(plates[i][j] == -1)
        continue; 
      if(plates[i][j] == plates[i][(j+1) % M]){ //좌우가 같은 경우 res에 넣기 
        res.emplace_back(i, j); 
        res.emplace_back(i, (j+1) % M); 
      }
      if(plates[i][j] == plates[(i+1) % N][j] && i != N-1){ //상하가 같은 경우 res에 넣기, 단 0번째 원판이랑 N-1번째 원판은 비교에서 제외 
        res.emplace_back(i, j); 
        res.emplace_back((i+1) % N, j); 
      }
    }
  }

  if(res.size() == 0) //지울것이 없음으로 false반환 
    return false; 

  for(int i = 0; i < res.size(); i++){ //-1을 대입하여 삭제 
    coo here = res[i]; 
    plates[here.first][here.second] = -1; 
  }
  return true; 
}

//전체 원판의 합과 갯수를 계산하는 함수 
void getSum(int& sum, int& cnt){
  sum = 0;  
  cnt = 0; 
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(plates[i][j] == -1)
        continue; 
      sum += plates[i][j]; 
      cnt++; 
    }
  }
}

//평균값을 기준으로 -1, +1 계산해주는 함수 
void toMinValue(){
  int sum, cnt; 
  getSum(sum, cnt);
  if(cnt == 0)
    return; 
  double avg = ((double)sum) / cnt;  // 평균 계산 
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(plates[i][j] == -1) 
        continue; 
      if(plates[i][j] > avg) //평균보다 크면 -1 
        plates[i][j] -= 1; 
      else if(plates[i][j] < avg) //평균보다 작으면 +1
        plates[i][j] += 1; 
    }
  }
}

int main(){
  cin >> N >> M >> K;
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      cin >> plates[i][j]; 
    }
  }

  for(int i = 0; i < K; i++){
    cin >> turn[i][0] >> turn[i][1] >> turn[i][2]; 
  }

  //print(); 

  for(int i = 0; i < K; i++){
    int x = turn[i][0]; 
    //원판 돌리기 
    int realx = x; 
    while(realx <= M){
      do_turn(realx - 1, turn[i][1], turn[i][2]); 
      realx += x; 
    }
    //cout << "=> after turn"; 
    //print(); 
    //인접한 수 삭제 
    if(removeDup() == false){  
      //삭제할 것이 없으면 평균에 대하여 +1, -1 계산 
      toMinValue(); 
    }
    //cout << "=> after remove"; 
    //print(); 
  }

  //sum 출력
  int sum, cnt; 
  getSum(sum, cnt);
  cout << sum << endl; 
  return 0; 
}