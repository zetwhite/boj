#include <iostream>
#include <algorithm>
#include <cstring>
#include <list>
#include <fstream>
#include <iomanip>
using namespace std;
#define IP pair<int, int>
#define N 100

IP operator+ (const IP& l, const IP& r){
    return {l.first + r.first, l.second + r.second};
}

short board[N+2][N+2];

void init_board(int n){
    for(int i = 0; i < N+1; i++){
        memset(board+i, 0, sizeof(short)*(N+1));
    }
    for(int i = 0; i <= n+1; i++){
        board[0][i] = -1;
        board[n+1][i] = -1;
    }
    for(int i = 0; i <=n+1; i++){
        board[i][0] = -1;
        board[i][n+1] = -1;
    }
}

inline void check_invalid(IP s){
    board[s.first][s.second] = -1;
}

inline void check_valid(IP s){
    board[s.first][s.second] = 0;
}

bool is_conflict(IP s){
    if(board[s.first][s.second] == -1)
        return true;
    return false;
}

bool is_apple(IP s){
    if(board[s.first][s.second] == 1){
        return true;
    }
    return false;
}

class Snake{
private:
    list<IP> s;
    IP dir;
public:
    Snake()
        :dir(0, 1){
        s.emplace_back(1, 1);
    }
    bool move(){
        IP head = s.back();
        head = head + dir;
        s.push_back(head);
        if(is_conflict(head))
            return false;
        if(is_apple(head)){
            check_invalid(head);
            return true;
        }
        IP tail = s.front();
        check_invalid(head);
        check_valid(tail);
        s.pop_front();
        return true;
    }
    bool rotate(char d){
        int x = dir.second;
        int y = dir.first;
        dir = make_pair(x, y);
        if(d == 'L')
            dir.first *= -1;
        else
            dir.second *= -1;
        return true;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    init_board(n);
    board[1][1] = -1;
    int a_count, r_count;
    cin >> a_count;
    for(int i = 0; i < a_count; i++){
        int x, y;
        cin >> x >> y;
        board[x][y] = 1;
    }

    cin >> r_count;
    char* controls = new char[10001];
    memset(controls, 0, sizeof(char)*(10001));
    for(int i = 0; i < r_count; i++){
        int x;
        cin >> x;
        cin >> controls[x];
    }

    Snake snake;
    int i = 1;
    while(true){
        if(snake.move() == false)
            break;
       // print_b(n);
        if(i<=10000 && controls[i] != '\0')
            snake.rotate(controls[i]);
        i++;
    }
    cout << i << endl;
}
