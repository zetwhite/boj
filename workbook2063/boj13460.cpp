#include <iostream>
#include <stack>
#include <algorithm>
#define MAX 10
using namespace std;
#define IP pair<int, int>
#define R 0b00000001
#define B 0b00000010
#define O 0b00000100
#define W 0b00001000


IP DIR[4] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};

IP operator + (const IP& lhs, const IP& rhs){
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}

IP operator - (const IP& lhs, const IP& rhs){
    return {lhs.first - rhs.first, lhs.second - rhs.second};
}

ostream& operator<< (ostream& os, const IP& a){
    os << "(" << a.first << ", " << a.second <<")";
    return os;
}

class Board{
public:
    int n, m;
    char board[MAX+1][MAX+1];
    IP red_cursor;
    IP blue_cursor;
    Board(int _n, int _m):
        n(_n), m(_m){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                char tmp;
                cin >> tmp;
                board[i][j] = convert(tmp);
                if(board[i][j] == R)
                    red_cursor = make_pair(i, j);
                else if(board[i][j] == B)
                    blue_cursor = make_pair(i, j);
            }
        }
    }
    Board(const Board& old){
        n = old.n;
        m = old.m;
        red_cursor = old.red_cursor;
        blue_cursor = old.blue_cursor;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                board[i][j] = old.board[i][j];
            }
        }
    }
    int getValue(IP a){
        return board[a.first][a.second];
    }
    void setCursor(bool is_red, IP v){
        if(is_red){
            if(red_cursor == v)
                return;
            board[red_cursor.first][red_cursor.second] &= ~R;
            board[v.first][v.second] |= R;
            red_cursor = v;
        }
        else{
            if(blue_cursor == v)
                return;
            board[blue_cursor.first][blue_cursor.second] &= ~B;
            board[v.first][v.second] |= B;
            blue_cursor = v;
        }
    }

private:
    int convert(char c){
        if(c == '#')
            return W;
        else if(c == 'R')
            return R;
        else if (c == 'B')
            return B;
        else if (c == 'O')
            return O;
        else
            return 0;
    }

};

int mov_dir(Board& b, IP dir){
    IP red, blue;
    int red_cnt = 0, blue_cnt = 0;
    red = b.red_cursor;
    blue = b.blue_cursor;
    bool red_success = false;
    bool blue_success = false;
    while(1){
        if(b.getValue(red+dir)&W)
            break;
        red_cnt++;
        red = red + dir;
        if(b.getValue(red)&O){
            b.setCursor(true, red);
            red_success = true;
            break;
        }
    }
    while(1){
        if(b.getValue(blue+dir)&W)
            break;
        blue_cnt++;
        blue = blue + dir;
        if(b.getValue(blue)&O){
            b.setCursor(false, blue);
            blue_success = true;
            break;
        }
    }
    if(blue_success)
        return -1;
    if(red_success)
        return 1;
    if(red_cnt > blue_cnt){ //mov blue first
        b.setCursor(false, blue);
        if(b.getValue(red) & B)
            b.setCursor(true, red-dir);
        else
            b.setCursor(true, red);
    }
    else{//mov red first
        b.setCursor(true, red);
        if(b.getValue(blue)&R)
            b.setCursor(false, blue-dir);
        else
            b.setCursor(false, blue);
    }
    return 0;
}

int find_way(Board b, int count);

int check_this_way(Board b, int count, IP dir){
    IP red = b.red_cursor;
    IP blue = b.blue_cursor;
    int mov_result = mov_dir(b, dir);
    if(red == b.red_cursor && blue == b.blue_cursor){
        return 20;
    }
    if(mov_result == 1){
        return count;
    }
    if(mov_result == 0){
        return find_way(b, count);
    }
    return 20;
}

int find_way(Board b, int count){
    int res = 20;
    if(count >= 10)
        return res;
    count++;
    for(int i = 0; i < 4; i++){
        int tmp = check_this_way(b, count, DIR[i]);
        if(res > tmp)
            res = tmp;
    }
    return res;
}

int main(){
    int n, m;
    cin >> n >> m;
    Board board(n, m);
    int res = find_way(board, 0);
    if(res == 20)
        cout << -1 << endl;
    else
        cout << res << endl;
    return 0;
}
