#include <iostream>
#include <algorithm>
using namespace std;
#define IP pair<int, int>

IP DIR[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

IP operator+ (const IP& a, const IP& b){
    return {a.first + b.first, a.second + b.second};
}

bool no_way(int board[52][52], IP here){
    bool res = true;
    for(int i = 0; i < 4; i++){
       IP tmp = here+DIR[i];
       if(board[tmp.first][tmp.second] == 0){
            res = false;
            break;
       }
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    int r, c, dir;
    cin >> r >> c >> dir;
    IP here = make_pair(r+1, c+1);

    int board[52][52];
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <=m; j++){
            cin >> board[i][j];
        }
    }

    int count = 0;
    while(1){
        board[here.first][here.second] = 2;
        if(no_way(board, here)){
            int back_dir = dir - 2;
            if(back_dir < 0) back_dir += 4;
            IP back = here + DIR[back_dir];
            if(board[back.first][back.second] == 1)
                break;
            else{
                here = back;
                continue;
            }
        }
        dir -= 1;
        if(dir < 0)
            dir += 4;
        IP tmp = here + DIR[dir];
        if(board[tmp.first][tmp.second] == 0){
            here = tmp;
            continue;
        }
        else{
            continue;
        }
    }

    int clean = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(board[i][j] == 2)
                clean++;
        }
    }

    cout << clean << endl;
    return 0;
}
