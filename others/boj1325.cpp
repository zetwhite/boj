#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int>* connections = new vector<int>[n+1];
    int* count = new int[n+1];
    bool* visited = new bool[n+1];
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        connections[b].push_back(a);
    }

    int max = 0;
    for(int i = 1; i <= n; i++){
        memset(visited, 0, n+1);
        int local_max = 0;
        stack<int> next;
        next.push(i);
        visited[i] = true;
        while(!next.empty()){
            int here = next.top();
            next.pop();
            local_max++;
            for(int j = 0; j < connections[here].size(); j++){
                int tmp = connections[here][j];
                if(visited[tmp] == false){
                    next.push(tmp);
                    visited[tmp] = true;
                }
            }
        }
        count[i] = local_max;
        if(local_max > max) max = local_max;
    }
    for(int i = 1; i <= n; i++)
        if(max == count[i])
            cout << i <<" ";
    return 0;
}
