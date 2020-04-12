#include <iostream>
#include <cstring>
#include <algorithm>
#include <iomanip>
using namespace std;
#define IP pair<int, int>

IP DIR[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

IP operator + (const IP& lhs, const IP& rhs){
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}

ostream& operator << (ostream& os, const IP& a){
    os << "(" << a.first << ", " << a.second << ")";
    return os;
}

class Board{
public:
    const int n;
    int board[22][22];
    bool combined[22][22];
    Board(int _n):n(_n){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                cin >> board[i][j];
            }
        }
        for(int i = 0; i <= n+1; i++){
            board[0][i] = 3;
            board[n+1][i] = 3;
        }
        for(int i = 0; i <= n+1; i++){
            board[i][0] = 3;
            board[i][n+1] = 3;
        }
    }
    int getBoard(IP coo) const{
        return board[coo.first][coo.second];
    }
    void setBoard(IP coo, int value){
        board[coo.first][coo.second] = value;
    }
    void print(){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
               cout << setw(4) << board[i][j];
            }
            cout << endl;
        }
    }
    void initCombined(){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++)
                combined[i][j] = false;
        }
    }
    bool getCombined(IP coo) const{
        return combined[coo.first][coo.second];
    }
    void setCombined(IP coo){
        combined[coo.first][coo.second] = true;
    }
    int getMax(){
        int max = 0;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++)
                if(board[i][j] > max)
                    max = board[i][j];
        }
        return max;
    }
};

void combine(Board& b, IP coo, IP dir){
    while(1){
        IP next = coo + dir;
        int nextValue = b.getBoard(next);
        int cooValue = b.getBoard(coo);
        if(nextValue == 3 || cooValue == 3)
            return;
        if(b.getCombined(next) || b.getCombined(coo)){
            coo = next;
            continue;
        }
        if(nextValue == 0){
            b.setBoard(next, cooValue);
            b.setBoard(coo, 0);
        }
        else if(nextValue == cooValue){
            b.setBoard(next, cooValue*2);
            b.setCombined(next);
            b.setBoard(coo, 0);
        }
        else
            break;
        coo = next;
    }
}

void tip(Board& b, IP dir){
    b.initCombined();
    if(dir.first < 0 || dir.second < 0){
        for(int i = 1; i <= b.n; i++){
            for(int j = 1; j <= b.n; j ++){
                combine(b, {i, j}, dir);
            }
        }
    }
    else{
        for(int i = b.n; i >= 1; i--){
            for(int j = b.n; j >= 1; j --){
                combine(b, {i, j}, dir);
            }
        }
    }
}

int go_2048(Board b, int count, IP dir){
    int max = b.getMax();
    if(count > 5)
        return max;

    if(!(dir.first == 0 && dir.second == 0))
        tip(b, dir);
    count++;

    for(int i = 0; i < 4; i ++){
        int tmp = go_2048(b, count, DIR[i]);
        if(max < tmp) max = tmp;
    }
    return max;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    Board board(n);

    int res = go_2048(board, 0, {0, 0});
    cout << res << endl;
    return 0;
}
