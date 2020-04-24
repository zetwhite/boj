//76% wrong.... WHY?!
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
#define IP pair<int, int>
#define PX first
#define PY second

class Ladder{
public:
    int n, m;
    int ** board;
    int crossCnt;
    Ladder(int _n, int _m)
    :n(_n), m(_m), crossCnt(0){
        board = new int*[n+2];
        for(int i = 0; i <= n+1; i++){
            board[i] = new int[m+2];
            memset(board[i], 0, sizeof(int)*(m+2));
        }
        for(int i = 0; i <= n+1; i++){
            board[i][0] = -1;
            board[i][m+1] = -1;
        }
        for(int i = 0; i <= m+1; i++){
            board[0][i] = -1;
            board[n+1][i] = -1;
        }
    }
    bool addCross(IP a, IP b){
        if(board[a.PX][a.PY] != 0 || board[b.PX][b.PY] != 0)
            return false;
        crossCnt++;
        board[a.PX][a.PY] = crossCnt;
        board[b.PX][b.PY] = crossCnt;
        return true;
    }
    void print(){
        cout << "===========================" <<endl;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
    }
    void removeCross(){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m-1; j++){
                if(board[i][j] == crossCnt){
                    board[i][j] = 0;
                    board[i][j+1] = 0;
                    crossCnt--;
                    return;
                }
            }
        }
    }
    int go(int line){
        if(line <= 0 || line >= m+1)
            abort();
        int height = 1;
        while(height != n+1){
            if(board[height][line] != 0){
                if(board[height][line] == board[height][line+1])
                    line++;
                else if(board[height][line] == board[height][line-1])
                    line--;
            }
            height++;
        }
        return line;
    }
};

bool success(Ladder& l){
    l.print();
    for(int i = 1; i <= l.m; i++ ){
        if(l.go(i) != i)
            return false;
    }
    return true;
}

bool addLines(Ladder& l, int lineCnt, IP last){
    if(lineCnt == 0)
        return success(l);
    for(int i = last.PX; i <= l.n; i++){
        int j;
        if(i == last.PX)
            j = last.PY + 1;
        else
            j = 1;
        for(; j <= l.m-1; j++){
            if(l.addCross({i, j}, {i, j+1})){
                if(addLines(l, lineCnt-1, {i, j+1}))
                    return true;
                l.removeCross();
            }
        }
    }
    return false;
}

int main(){
    int w, crossCnt, h;
    cin >> w >> crossCnt >> h;
    Ladder ladder(h, w);
    for(int i = 0; i < crossCnt; i++){
        int a, b;
        cin >> a >> b;
        ladder.addCross({a, b}, {a, b+1});
    }
    for(int i = 0; i < 4; i++){
        if(addLines(ladder, i, {1, 1})){
            cout << i << endl;
            return 0;
        }
    }
    cout << "-1" << endl;
    return 0;
}
