#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
#define IP pair<int, int>

IP dir[4] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};

IP operator+ (const IP& lhs, const IP& rhs){
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}

int go_virus(int map[10][10], int n, int m){
    int new_map[10][10];
    for(int i = 0; i <= n+1; i++){
        memcpy(new_map[i], map[i], sizeof(int)*(m+2));
    }
    queue<IP> next;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j++){
            if(new_map[i][j] == 2)
                next.emplace(i, j);
        }
    }
    while(!next.empty()){
        IP here = next.front();
        next.pop();
        for(int i = 0; i < 4; i++){
            IP tmp = here + dir[i];
            if(new_map[tmp.first][tmp.second] == 0){
                new_map[tmp.first][tmp.second] = 2;
                next.push(tmp);
            }
        }
    }
    int safe = 0;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= m; j++){
            if(new_map[i][j] == 0)
                safe++;
        }
    }
    return safe;
}

int main(){
    int map[10][10];
    int n, m;
    vector<IP> make_wall;
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> map[i][j];
            if(map[i][j] == 0)
                make_wall.emplace_back(i, j);
        }
    }
    for(int i = 0; i <= m+1; i++){
        map[0][i] = 1;
        map[n+1][i] = 1;
    }
    for(int i = 1; i <= n; i++){
        map[i][0] = 1;
        map[i][m+1] = 1;
    }

    int s_max = 0;
    int max = make_wall.size();
    for(int i = 0; i < max-2; i++){
        IP one = make_wall[i];
        map[one.first][one.second] = 1;
        for(int j = i+1; j < max-1; j++){
            IP two = make_wall[j];
            map[two.first][two.second] = 1;
            for(int k = j+1; k < max; k++){
                IP three = make_wall[k];
                map[three.first][three.second] = 1;
                int tmp = go_virus(map, n, m);
                if(tmp > s_max)
                    s_max = tmp;
                map[three.first][three.second] = 0;
            }
            map[two.first][two.second] = 0;
        }
        map[one.first][one.second] = 0;
    }
    cout << s_max << endl;
    return 0;
}
