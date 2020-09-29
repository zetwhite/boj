#include <iostream> 
#include <vector>
#include <algorithm> 
using namespace std; 

const int INVALID = 10'000'000; 

class DisjointSet{
public: 
    vector<int> parents; 
    vector<int> values; 
    DisjointSet(int n):
        parents(vector<int>(n+1)), 
        values(vector<int>(n+1,  0)){
        for(int i = 1; i <= n; i++){
            parents[i] = i; 
        }
    }

    pair<int, int> getRoot(int n){
        if(parents[n] != n){
            int next = parents[n];
            pair<int, int> res = getRoot(next); 
            parents[n] = res.first; // root 
            values[n] = res.second + values[n]; //update weight; 
            return make_pair(parents[n], values[n]); 
        }
        return make_pair(n, 0); 
    }

    void add(int a, int b, int w){
        int rootA = getRoot(a).first; 
        int rootB = getRoot(b).first;
        if(rootA == rootB){
            parents[a] = rootB; 
            values[a] = w + values[b]; 
        }
        else{
            int valueA2rootA = values[a]; 
            int valueA2rootB = values[b] + w; 
            parents[rootA] = rootB;
            values[rootA] = valueA2rootB - valueA2rootA; 
        }
    }

    int select(int a, int b){
        int rootA = getRoot(a).first; 
        int rootB = getRoot(b).first; 
        if(rootA != rootB)
            return INVALID;
        return values[a] - values[b];  
    }
}; 


int main(){
    /*ios::sync_with_stdio(false);
    cin.tie(NULL); 
    cout.tie(NULL);*/
    while(1){
        int n, m; 
        cin >> n >> m; 
        if(n == 0 && m == 0)
            break; 
        {
            DisjointSet dSet(n); 
            char op; 
            int a, b, w; 
            for(int i = 0;i < m; i++){
                cin >> op; 
                if(op == '!'){
                    cin >> a >> b >> w; 
                    dSet.add(a, b, w); 
                }
                if(op == '?'){
                    cin >> a >> b; 
                    int result = dSet.select(a, b); 
                    if(result == INVALID)
                        cout << "UNKNOWN" << "\n"; 
                    else 
                        cout << result << "\n"; 
                }
            }
        }
    }
    return 0; 
}