#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

bool find(int element, vector<int>& v){
    for(int i = 0; i < v.size(); i++){
        if(v[i] == element)
            return true;
    }
    return false;
}

bool findWay(int a, bool** adj, int* visited, int n, vector<int>& ancestor){
    for(int i = 0; i < n; i++){
        if(adj[a][i] == false || find(visited[i], ancestor))
            continue;

        ancestor.push_back(a);
        if(visited[i]==-1||findWay(visited[i], adj, visited, n, ancestor)){
            visited[i] = a;
            return true;
        }
    }
    return false;
}

void biMatch(bool** adj, int* visited, int n){
    for(int i = 0; i < n; i++){
        vector<int> history;
        findWay(i, adj, visited, n, history);
    }
    return;
}

int main(){
    int n, m;
    cin >> n >> m;
    bool** adj = new bool*[n];
    int* visited = new int[n];
    memset(visited, -1, sizeof(int)*n);
    for(int i = 0; i < n; i++){
        adj[i] = new bool[n];
        memset(adj[i], 0, sizeof(bool)*n);
    }
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        adj[a-1][b-1] = true;
    }

    biMatch(adj, visited, n);
    int match = 0;
    for(int i = 0; i < n; i++){
        if(visited[i] != -1)
            match++;
    }
    cout << match << endl;
    return 0;
}
