#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define IP pair<int, int>

IP DIR[4] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

IP operator + (const IP& lhs, const IP& rhs){
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}

ostream& operator << (ostream& os, const IP& a){
    os << "(" << a.first << ", " << a.second << ")";
    return os;
}

const int B = 0;
const int N = 1;
const int E = 2;
const int W = 3;
const int S = 4;
const int T = 5;

class Die{
public:
    int location[6];//down1, north2, east3, west4, south5, top6
    int numStorage[6];
    int next[4][6];
    Die():
        next{
        {E, N, T, B, S, W},//1 move east
        {W, N, B, T, S, E},//2 move west
        {N, T, E, W, B, S},//3 move north
        {S, B, E, W, T, N},//4 move south
        }
        , numStorage{0,0,0,0,0}
        , location{1,2,3,4,5,6}
        {}

    int getNext(int dir){
        int tmplocation[6];
        for(int i = 0; i < 6; i++){
            tmplocation[i] = location[next[dir][i]];
        }
        memcpy(location, tmplocation, sizeof(int)*6);
        return numStorage[location[5]-1];
    }

    void set(int newValue){
        numStorage[location[0]-1] = newValue;
    }

    void print(){
        cout << "down\t:" << location[0] << "=> " << numStorage[location[0]-1] << endl;
        cout << "north\t:" << location[1] << "=> " << numStorage[location[1]-1] << endl;
        cout << "east\t:" << location[2] << "=> " << numStorage[location[2]-1] << endl;
        cout << "west\t:" << location[3] << "=> " << numStorage[location[3]-1] << endl;
        cout << "south\t:" << location[4] << "=> " << numStorage[location[4]-1] << endl;
        cout << "top\t:" << location[5] << "=> " << numStorage[location[5]-1] << endl;
    }

    int getDown() const{
        return numStorage[location[0]-1];
    }
};

class Board{
public:
    int mBoard[22][22];
    const int mN;
    const int mM;
    IP mDieCo;
    Die die;

    Board(int n, int m, int x, int y):mN(n), mM(m), mDieCo(x, y){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++)
                cin >> mBoard[i][j];
        }
        for(int i =0; i <=n+1; i++){
            mBoard[i][0] = -1;
            mBoard[i][m+1] = -1;
        }
        for(int j = 0; j <= m+1; j++){
            mBoard[0][j] = -1;
            mBoard[n+1][j] = -1;
        }
    }

    void writeBoard(IP coo, int value){
        mBoard[coo.first][coo.second] = value;
    }

    int readBoard(IP coo) const{
       return mBoard[coo.first][coo.second];
    }

    int movDie(int dir){
        IP tmp = mDieCo + DIR[dir];
        int tmpValue = readBoard(tmp);
        int res = -1;
        if(tmpValue == -1)
            return res;

        res = die.getNext(dir);
        if(tmpValue == 0){
            writeBoard(tmp, die.getDown());
        }
        else{
            die.set(tmpValue);
            writeBoard(tmp, 0);
        }
        mDieCo = tmp;
        return res;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, x, y, k;
    cin >> n >> m >> x >> y >> k;
    Board b(n, m, x+1, y+1);
    for(int i = 0; i < k; i++){
        int a;
        cin >> a;
        int res = b.movDie(a-1);
        if(res != -1)
            cout << res << endl;
    }
    return 0;
}
