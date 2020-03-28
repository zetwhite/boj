#include <bits/stdc++.h>
using namespace std;
#define MAX 50
#define IP pair<int, int>
#define G 0b100
#define R 0b1000
#define F 0b10000
#define D 0b100000

int n, m;
int garden[MAX+2][MAX+2];
int test[MAX+2][MAX+2];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
//0- 호수, 1-배양액 뿌릴 수 없는 땅, 2-배양액 가능 4-green, 8-red, 16-flower

inline bool go_further(int x, int y, bool is_green){
    if(test[x][y]==0 || test[x][y]&0b110000)
        return false;
    if(is_green){//green
        if(test[x][y]&R){//meet red
            test[x][y] <<= 1;
            return false;
        }
        if(!(test[x][y]&G)){//get new land
            test[x][y] = G;
            return true;
        }
        return false; //already green is there
    }
    else{
        if(test[x][y]&G){ //meet green
            test[x][y] <<= 2;
            return false;
        }
        if(!(test[x][y]&R)){
            test[x][y] = R;
            return true;
        }
        return false;
    }
}

void make_done(list<IP>& q){
    list<IP>::iterator it;
    for(it = q.begin(); it != q.end(); it++){
        IP tmp = *it;
        if(!(test[tmp.first][tmp.second] & F))
            test[tmp.first][tmp.second] = D;
    }
}

void expand(list<IP>& q, bool is_green){
    int sz = q.size();
    for(int i = 0; i < sz; i++){
        IP here = q.front();
        q.pop_front();
        if(test[here.first][here.second] & F)
            continue;
        for(int i = 0; i < 4; i++){
            if(go_further(here.first+dx[i], here.second+dy[i], is_green))
                q.emplace_back(here.first+dx[i], here.second+dy[i]);
        }
    }
}

void combination(vector<vector<int>>& com, vector<int> tmp, int n, int r){
    if(r == 0){
        com.push_back(tmp);
        return;
    }
    else if(n < r){
        return;
    }
    else{
        tmp.push_back(n-1);
        combination(com, tmp, n-1, r-1);
        tmp.pop_back();
        combination(com, tmp, n-1, r);
    }
}

void copy_array(int src[MAX+2][MAX+2], int dest[MAX+2][MAX+2], int n, int m){
    for(int x = 0; x <= n+1; x++)
        memcpy(dest[x], src[x], sizeof(int)*(m+2));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m, g, r;
    cin >> n >> m >> g >> r;
    vector<IP> starter;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> garden[i][j];
            if(garden[i][j] == 2)
                starter.push_back(make_pair(i, j));
        }
    }
    for(int i = 0; i <= m+1; i++){
        garden[0][i] = 0;
        garden[n+1][i] = 0;
    }
    for(int i =1; i <= n+1; i++){
        garden[i][0] = 0;
        garden[i][m+1] = 0;
    }

    int st_sz = starter.size();
    vector<vector<int>> green_st;
    vector<int> temp;
    combination(green_st, temp, st_sz, g+r);
    vector<vector<int>> red_st;
    combination(red_st, temp, g+r, r);
    bool *used = new bool[st_sz];

    int max_count = 0;
    for(int i = 0; i < green_st.size(); i++){
        list<IP> green_pos, red_pos;
        for(int j = 0; j < red_st.size(); j++){
            copy_array(garden, test, n, m);
            memset(used, 0, sizeof(bool)*st_sz);
            for(int l = 0; l < red_st[j].size(); l++){ //make red_pos
                IP tmp = starter.at(green_st[i][red_st[j][l]]);
                red_pos.push_back(tmp);
                used[green_st[i][red_st[j][l]]] = true;
            }
            for(int k = 0; k < g+r; k++){ //make green_pos
                if(used[green_st[i][k]] == false){
                    IP tmp = starter.at(green_st[i][k]);
                    green_pos.push_back(tmp);
                }
            }

            while((!green_pos.empty()) || (!red_pos.empty())){
                make_done(green_pos);
                make_done(red_pos);
                expand(green_pos, true);
                expand(red_pos, false);
            }
            while(!green_pos.empty())
                expand(green_pos, true);
            while(!red_pos.empty())
                expand(red_pos, false);

            int cnt = 0;
            for(int x = 1; x <= n; x++)
                for(int y = 1; y <= m; y++)
                    if(test[x][y] & F)
                        cnt++;
            if(max_count < cnt)
                max_count = cnt;
        }
    }
    cout << max_count << endl;
    return 0;
}
