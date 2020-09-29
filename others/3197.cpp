#include <iostream> 
#include <algorithm> 
#include <queue> 
using namespace std; 

const char ICE = 'X'; 
const char WATER = '.'; 
const char SWAN = 'L'; 
const char WALL = '|'; 
char map[1505][1505]; 
int R, C; 

pair<int, int> dir[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; 

pair<int, int> operator+ (pair<int, int> left, pair<int, int> right){
    return {left.first +  right.first , left.second + right.second}; 
}

queue<pair<int, int>> initQueue(pair<int,int> start, char filling){
    queue<pair<int, int>> boundary; 
    queue<pair<int, int>> next; 
    map[start.first][start.second] = filling; 
    next.push(start); 
    while(1){
        if(next.empty())
            break; 
        pair<int, int> here = next.front(); 
        next.pop(); 
        bool addHere = false; 
        for(int i = 0; i < 4; i++){
            pair<int, int> tmp = here + dir[i]; 
            char& tmpValue = map[tmp.first][tmp.second]; 
            if(tmpValue == ICE && addHere == false){
                boundary.push(here); 
                addHere = true; 
            }
            if(tmpValue == WATER || tmpValue == SWAN){
                tmpValue = filling; 
                next.push(tmp); 
            }
        }
    }
    return boundary; 
}

void MeltIce(queue<pair<int, int>>& next, char filling){
    int size = next.size(); 
    for(int i = 0; i < size; i++){
        pair<int, int> here = next.front();
        next.pop(); 
        for(int i = 0; i < 4; i++){
            pair<int, int> tmp = here + dir[i]; 
            char& tmpValue = map[tmp.first][tmp.second]; 
            if(tmpValue == ICE || tmpValue == WATER){
                tmpValue = filling; 
                next.push(tmp); 
            }
        }
    }
}

bool IsSwam(queue<pair<int, int>>& next, char counterpart){
    int size = next.size(); 
    for(int i = 0; i < size; i++){
        pair<int, int> here = next.front();
        next.pop(); 
        for(int i = 0; i < 4; i++){
            pair<int, int> tmp = here + dir[i]; 
            char& tmpValue = map[tmp.first][tmp.second]; 
            if(tmpValue == counterpart){
                //cout << tmp.first << ", " << tmp.second << endl; 
                return true; 
            }
        }
        next.push(here); 
    } 
    return false; 
}

void print(){
    for(int i = 1; i <= R; i++){
        for(int j = 1; j <= C; j++){
            cout << map[i][j] << " "; 
        }
        cout << endl; 
    }
}

int main(){
    pair<int, int> L1 = make_pair(-1, -1); 
    pair<int, int> L2 = make_pair(-1, -1); 
    cin >> R >> C; 
    for(int i = 0; i <= C; i++){
        map[0][i] = WALL;
        map[R+1][i] = WALL;  
    }
    for(int i = 1; i <= R; i++){
        map[i][0] = WALL; 
        for(int j = 1; j <= C; j++){
            cin >> map[i][j]; 
            if(map[i][j] == SWAN){
                if(L1.first == -1)
                    L1 = make_pair(i, j); 
                else 
                    L2 = make_pair(i, j); 
            }
        }
        map[i][C+1] = WALL; 
    }

    queue<pair<int, int>> boundary1 = initQueue(L1, '1');    
    if(map[L2.first][L2.second] == '1'){
        cout << "1" << endl; 
        return 0; 
    }
    queue<pair<int, int>> boundary2 = initQueue(L2, '2'); 

    print(); 
    int day = 1; 
    while(1){
        cout << "====== day " << day << "=====" << endl; 
        MeltIce(boundary1, '1'); 
        //cout << "after Expanding 1 :: " << endl; 
        //print(); 
        if(IsSwam(boundary1, '2'))
            break; 
        
        MeltIce(boundary2, '2');
        //cout << "after Expanding 2 :: " << endl; 
        //print(); 
        if(IsSwam(boundary2, '1'))
            break; 
        print(); 
        day++;
    }
    cout << day << endl; 
    return 0; 
}