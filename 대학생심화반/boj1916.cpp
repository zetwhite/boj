#include <bits/stdc++.h>
#define pi pair<int,int>
#define INF 1000000000
using namespace std;

struct custom_compare{
    bool operator()(const pi& a, const pi& b){
        if(a.second == b.second)
            return a.first > b.first;
        return a.second > b.second;
    }
};

ostream& operator << (ostream& os, pi& a){
    os << "(" << a.first << ", " << a.second <<")";
    return os;
}

class City{
public:
    vector<pi> next;
    int exp;
    City():exp(INF){}
};

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
        citys[a].next.push_back(make_pair(b, c));
    }

    int st, end;
    cin >> st >> end;
    priority_queue<pi, vector<pi>, custom_compare> pq;
    citys[st].exp = 0;
    pq.emplace(st, 0);
    while(!pq.empty()){
        pi here = pq.top();
        pq.pop();
        int c = here.first;
        int old_exp = citys[c].exp;
        for(int i = 0; i < citys[c].next.size(); i++){
            pi tmp = citys[c].next[i];
            if(citys[tmp.first].exp > tmp.second + old_exp){
                citys[tmp.first].exp = tmp.second + old_exp;
                pq.emplace(tmp.first, tmp.second + old_exp);
            }
        }
    }
    cout << citys[end].exp << endl;
}
