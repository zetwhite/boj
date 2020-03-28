#include <bits/stdc++.h>

using namespace std;

inline int find_root(int n, int* parents){
    int root = n;
    stack<int> tmp;
    while(parents[root] >= 0){
        tmp.push(root);
        root = parents[root];
    }
    while(!tmp.empty()){
        parents[tmp.top()] = root;
        tmp.pop();
    }
    return root;
}

inline bool is_same_group(int a, int b, int* parents){
    int a_root = find_root(a, parents);
    int b_root = find_root(b, parents);
    if( a_root != b_root )
        return false;
    else
        return true;
}

inline void do_union(int a, int b, int* parents){
    int a_root = find_root(a, parents);
    int b_root = find_root(b, parents);
    if( a_root == b_root )
        return;
    parents[b_root] = a_root;
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    int* parents;
    cin >> n >> m;
    parents = new int[n+1];
    memset(parents, -1, sizeof(int)*(n+1));

    int type, a, b;
    for(int j = 0; j < m; j++){
        cin >> type >> a >> b;
        if(!type)
            do_union(a, b, parents);
        else{
            if(is_same_group(a, b, parents))
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }
    return 0;
}
