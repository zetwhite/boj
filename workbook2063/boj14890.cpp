#include <iostream>
#include <cstring>
using namespace std;

int n, l;
int map[101][101];
bool is_slope[101][101];

bool load_slope(bool is_col, int line, int st, int end){
    if(st < 0 || end >= n){
        return false;
    }
    for(int i = st; i <= end; i++){
        if(is_col){
            if(i!= end && map[i][line] != map[i+1][line])
                return false;
            if(is_slope[i][line])
                return false;
        }
        else{
            if(i!=end && map[line][i] != map[line][i+1])
                return false;
            if(is_slope[line][i])
                return false;
        }
    }
    for(int i = st; i <= end; i++){
        if(!is_col)
            is_slope[line][i]++;
        else
            is_slope[i][line]++;
    }
    return true;
}

bool is_way(bool is_col, int line){
    if(is_col){
        for(int i = 0; i < n-1; i++){
            if(map[i][line] == map[i+1][line])
                continue;
            else if(map[i][line]+1 == map[i+1][line]){
                if(!load_slope(is_col, line, i+1-l, i))
                    return false;
            }
            else if(map[i][line] == map[i+1][line]+1){
                if(!load_slope(is_col, line, i+1, i+l))
                    return false;
            }
            else
                return false;
        }
    }
    else{
        for(int i = 0; i < n-1; i++){
            if(map[line][i] == map[line][i+1])
                continue;
            else if(map[line][i]+1 == map[line][i+1]){
                if(!load_slope(is_col, line, i+1-l, i))
                    return false;
            }
            else if(map[line][i] == map[line][i+1]+1){
                if(!load_slope(is_col, line, i+1, i+l))
                    return false;
            }
            else
                return false;
        }
    }
    return true;
}

int main(){
    cin >> n >> l;
    for(int i = 0; i < n; i++)
        memset(is_slope, 0, sizeof(bool)*n);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> map[i][j];

    int cnt = 0;
    for(int i = 0; i < n; i++){
        if(is_way(true, i))
            cnt++;
        for(int j = 0; j < n; j++)
            is_slope[j][i] = false;
    }
    for(int i = 0; i < n; i++){
        if(is_way(false, i))
            cnt++;
        for(int j = 0; j < n; j++)
            is_slope[i][j] = false;
    }
    cout << cnt << endl;
    return 0;
}
