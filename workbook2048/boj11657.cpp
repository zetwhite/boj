#include<bits/stdc++.h>
#define INF 2000000000

using namespace std;

typedef pair<int, int> int_pair; //cost, city

class City{
public:
    vector<int_pair> next;
    int cost;
    City(): cost(INF){};
    void add_next(int time, int city){
        int i = 0;
        for( ; i < next.size(); i++){
            if(next.at(i).second == city) {
                if(next.at(i).first > time)
                    next.at(i) = make_pair(time, city);
                break;
            }
        }
        if(i == next.size())
            next.emplace_back(time, city);
    }
    void print_cost(){
        if(cost == INF)
            cout <<"-1\n";
        else
            cout << cost << "\n";
    }
};

inline bool relax_edge( City* cs, int num, bool is_last){
    for(int i = 0; i < cs[num].next.size(); i++){
        int_pair tmp = cs[num].next.at(i);
        if(cs[num].cost != INF && cs[tmp.second].cost > tmp.first + cs[num].cost){
            if(!is_last)
                cs[tmp.second].cost = tmp.first + cs[num].cost;
            else
                return false;
        }
    }
    return true;
}

bool bellman_ford( City* cs, int n, bool is_last){
    bool no_negative_loop = true;
    for(int i = 1; i < n+1; i++){
        if(!(no_negative_loop = relax_edge(cs, i, is_last)))
            break;
    }
    return no_negative_loop;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    City* citys = new City[n+1];
    for(int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        citys[a].add_next(c, b);
    }

    citys[1].cost = 0;
    for(int i = 0; i < n-1; i++)
        bellman_ford(citys, n, false);

    int res = bellman_ford(citys, n, true);
    if(!res){
        cout << "-1\n";
    }
    else{
        for(int i = 2; i < n+1; i++)
            citys[i].print_cost();
    }

    return 0;
};
