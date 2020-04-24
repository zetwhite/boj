#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;
#define IP pair<int, int>

IP DIR[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int board[10][10];
void init_board(int n, int m){
    for(int i = 0; i <= n+1; i++){
        board[i][0] = 6;
        board[i][m+1] = 6;
    }
    for(int i = 0; i <= m+1; i++){
        board[0][i] = 6;
        board[n+1][i] = 6;
    }
}

IP operator + (IP& lhs, IP& rhs){
    return {lhs.first + rhs.first , lhs.second + rhs.second};
}

class Camera{
public:
    IP location;
    int dirSize;
    int* directions;
    void rotate(){
        for(int i = 0; i< dirSize; i++){
            directions[i] = (directions[i]+1)%4;
        }
    }
    Camera(bool _dir[4], int x, int y){
        location = {x, y};
        dirSize = 0;
        for(int i = 0; i < 4; i++)
            if(_dir[i]) dirSize++;
        directions = new int[dirSize];
        int idx = 0;
        for(int i = 0; i < 4; i++){
            if(_dir[i]){
                directions[idx] = i;
                idx++;
            }
        }
    }
    void turnOn(){
        for(int i = 0 ; i < dirSize; i++){
            IP next = location + DIR[directions[i]];
            while(board[next.first][next.second] != 6){
                if(board[next.first][next.second] <= 0)
                    board[next.first][next.second]-=1;
                next = next + DIR[directions[i]];
            }
        }
    }
    void turnOff(){
        for(int i = 0; i < dirSize; i++){
            IP next = location + DIR[directions[i]];
            while(board[next.first][next.second]!=6){
                if( board[next.first][next.second] <= 0)
                    board[next.first][next.second] += 1;
                next = next + DIR[directions[i]];
            }
        }
    }
};

int getArea(int n, int m){
    int cnt = 0;
    for(int i = 1; i <= n; i++){
        for(int j =1; j <=m; j++){
            if(board[i][j]==0)
                cnt++;
        }
    }
    return cnt;
}

void print(int n, int m){
    cout <<"====================================" << endl;
    for(int i = 1; i <= n; i++){
        for(int j = 1;j <= m; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

int cams_start(vector<Camera>& cams, int pivot, int n, int m){
    if(pivot == cams.size()){
        //print(n, m);
        return getArea(n, m);
    }
    int min = INT_MAX;
    for(int i = 0; i < 4; i++){
        cams[pivot].rotate();
        cams[pivot].turnOn();
        int res = cams_start(cams, pivot+1, n, m);
        cams[pivot].turnOff();
        if(res < min) min = res;
    }
    return min;
}

int main(){
    bool cam[5][4] = {
        {1, 0, 0, 0},
        {1, 0, 1, 0},
        {1, 0, 0, 1},
        {1, 0, 1, 1},
        {1, 1, 1, 1},
    };

    int n, m;
    cin >> n >> m;
    init_board(n, m);

    vector<Camera> cams;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            int in;
            cin >> in;
            board[i][j] = in;
            if(in!=0 && in!= 6)
                cams.emplace_back(cam[in-1], i, j);
        }
    }
    cout << cams_start(cams, 0, n, m) << endl;
    return 0;
}
