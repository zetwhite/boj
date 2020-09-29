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
typedef pair<int, int> PI; 

PI dir[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; 

PI operator+ (PI left, PI right){
    return {left.first + right.first, left.second + right.second}; 
}

void print(){
    for(int i = 1; i <= R; i++){
        for(int j = 1; j <= C; j++){
            cout << map[i][j] << " "; 
        }
        cout << endl; 
    }
}

queue<PI> boundary; 
void MeltIce(){
    int size = boundary.size(); 
    for(int i = 0; i < size; i++){
        pair<int, int> here = boundary.front();
        boundary.pop(); 
        for(int i = 0; i < 4; i++){
            pair<int, int> tmp = here + dir[i]; 
            char& tmpValue = map[tmp.first][tmp.second]; 
            if(tmpValue == ICE || tmpValue == '*'){
                tmpValue = WATER; 
                boundary.push(tmp); 
            }
        }
    }
}

bool goSwam(queue<PI>& next, char filling, char counterpart){
    queue<PI> realNext;
    while(1){
        if(next.empty())
            break; 
        PI here = next.front(); 
        next.pop(); 
        for(int i = 0; i < 4; i++){
            PI tmp = here + dir[i]; 
            char& tmpValue = map[tmp.first][tmp.second]; 
            if(tmpValue == WATER){
                tmpValue = filling; 
                next.push(tmp); 
            }
            else if(tmpValue == ICE){
                tmpValue = '*'; 
                realNext.push(tmp); 
            }
            else if(tmpValue == counterpart)
                return true; 
        }
    }
    next = realNext; 
    return false; 
}


int main(){
    PI L1 = make_pair(-1, -1); 
    PI L2 = make_pair(-1, -1); 
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
                map[i][j] = WATER; 
            }
        }
        map[i][C+1] = WALL; 
    }

    for(int i = 1; i <= R; i++){
        for(int j = 1; j <= C; j++){
            PI here = {i, j}; 
            if(map[i][j] != WATER)
                continue; 
            for(int k = 0; k < 4; k++){
                PI neigh = here + dir[k]; 
                if(map[neigh.first][neigh.second] == ICE){
                    boundary.push(here); 
                    //cout << here.first << ", " << here.second << endl; 
                    break; 
                }
            }
        }
    }

    queue<PI> swam1; 
    map[L1.first][L1.second] = '1'; 
    swam1.push(L1); 
    map[L2.first][L2.second] = '2'; 

    int day = 0; 
    if(goSwam(swam1, '1', '2')){
        cout << day << endl; 
        return 0; 
    }
    //cout << "day ===== 0 " << endl; 
    //print(); 

    while(1){
        day++; 
        //cout << "day ===== " << day << endl; 
        MeltIce(); 
        if(goSwam(swam1, '1', '2')){
            cout << day << endl; 
            break; 
        }
        //print(); 
    }
    return 0; 
}