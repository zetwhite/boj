#include <bits/stdc++.h>
using namespace std;
#define MAX 1000
#define IP pair<int, int>
char building[MAX+2][MAX+2];

void clear_q(queue<IP>& q){
    while(!q.empty())
        q.pop();
}

inline bool check_go(queue<IP>& next, int x, int y, bool is_fire){
    if(is_fire == false){
        if(building[x][y]=='.'){
            next.emplace(x, y);
            building[x][y]='@';
            return false;
        }
        else if(building[x][y]=='0'){
            return true;
        }
        return false;
    }
    else{
        if(building[x][y]=='.'|| building[x][y]=='@'){
            next.emplace(x, y);
            building[x][y] = '*';
            return false;
        }
        return false;
    }
}



int do_bfs(queue<IP>& next, bool is_fire){
    int sz = next.size();
    if(is_fire == false && sz == 0)
        return -1; //fail
    while(sz > 0){
        IP h= next.front();
        next.pop();
        sz--;
        if(check_go(next, h.first+1, h.second, is_fire))
            return 1; //escape
        if(check_go(next, h.first-1, h.second, is_fire))
            return 1;
        if(check_go(next, h.first, h.second+1, is_fire))
            return 1;
        if(check_go(next, h.first, h.second-1, is_fire))
            return 1;
    }
    return 0; //keep going
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    queue<IP> next;
    queue<IP> fire;
    for(int i = 0; i < t; i++){
        int h, w;
        cin >> w >> h;
        for(int j = 1; j <= h; j++){
            for(int k = 1; k <= w; k++){
                cin >> building[j][k];
                if(building[j][k] == '@')
                    next.emplace(j, k);
                else if(building[j][k] == '*')
                    fire.emplace(j, k);
            }
        }
        for(int _h = 0; _h <= h+1; _h++){
            building[_h][0] = '0';
            building[_h][w+1] = '0';
        }
        for(int _w = 0; _w <= w+1; _w++){
            building[0][_w] = '0';
            building[h+1][_w] = '0';
        }

        int res = 0;
        int count = 0;
        while(1){
            count++;
            do_bfs(fire, true);
            res = do_bfs(next, false);
            if(res != 0)
                break;
        }
        if(res == 1)
            cout << count << endl;
        else
            cout << "IMPOSSIBLE" << endl;
        clear_q(next);
        clear_q(fire);
    }
    return 0;
}
