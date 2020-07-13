#include <iostream> 
#include <vector> 
typedef long long ll; 
using namespace std;

bool adj[10][10] = {0};
char Num[10][5][4] ={ {
    "###", 
    "#.#", 
    "#.#", 
    "#.#", 
    "###"
},{
    "..#", 
    "..#", 
    "..#", 
    "..#", 
    "..#"
}, {
    "###", 
    "..#", 
    "###", 
    "#..", 
    "###"
}, {
    "###", 
    "..#", 
    "###", 
    "..#", 
    "###"
}, {
    "#.#", 
    "#.#", 
    "###", 
    "..#", 
    "..#"
},{
    "###", 
    "#..", 
    "###", 
    "..#", 
    "###"
},{
    "###", 
    "#..", 
    "###", 
    "#.#", 
    "###"
}, {
    "###", 
    "..#", 
    "..#", 
    "..#", 
    "..#"
}, {
    "###", 
    "#.#", 
    "###", 
    "#.#", 
    "###", 
}, {
    "###", 
    "#.#", 
    "###", 
    "..#", 
    "###"
}
}; 

void settingAdj(const int start, const vector<int>& next){
    for(int i = 0; i < next.size(); i++){
        adj[start][next.at(i)] = true; 
    }
    return; 
}

void getInput(char** p, int n){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 4*n - 1; j++){
            cin >> p[i][j]; 
        }
    }
}

int findNumber(char **p, int n){
    bool fail = false; 
    int k = 0; 
    for(int k = 0; k < 10; k++){
        cout << "check Number " << k << endl;  
        fail = false;     
        for(int i = 0; i < 5; i ++){
            for(int j = 0; j < 3; j++){
                if(Num[k][i][j] != p[i][n*4 + j]){
                    fail = true; 
                    break; 
                }
            }
            if(fail) break; 
        }
        if(fail) continue; 
        else   
            return k; 
    }
    return -1; 
}

void getPosNumber(int num, int* posNumber, int* posNumCounter){
    if(posNumber[num] == 1)
        return; 
    else{
        posNumber[num] = 1; 
        (*posNumCounter) ++; 
        for(int i = 0; i < 10; i++){
            if(adj[num][i])
                getPosNumber(i, posNumber, posNumCounter); 
        }
    }  
}

void getNumber(int last, int idx, int num, int** possNumber, vector<int>& res){
    if(last == idx){
        res.push_back(num); 
        return; 
    }
    for(int i = 0; i < 10; i ++){
        if(possNumber[idx][i]){
            getNumber(last, idx+1, num*10 + i, possNumber, res); 
        }
    }
}

int main(){

    int n; 
    cin >> n; 
    vector<int> chain[10] = {{8}, {0, 7, 4, 6}, {8}, {9}, {9}, {8}, {5}, {3}, {}, {8}};  
    for(int i = 0; i < 10; i++)
        settingAdj(i, chain[i]); 

    int** possNumber = new int*[n];
    int* possNumCounter = new int[n](); 
    for(int i = 0; i < n; i++){
        possNumber[i] = new int[10](); 
    } 

    char** painting = new char*[5]; 
    for(int i = 0; i < 5; i++)
        painting[i] = new char[4*n]; 
    getInput(painting, n); 

    for(int i = 0; i < n; i++){
        int n = findNumber(painting, i);  
        getPosNumber(n, possNumber[i], &(possNumCounter[i])); 
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 10; j++){
            if(possNumber[i][j])
                cout << j << ", "; 
        }
        cout << endl;
    }

    vector<int> results; 
    long long res = 0; 
    getNumber(n, 0, 0, possNumber, results); 
    for(int i = 0; i < results.size(); i++){
        cout << results[i] << endl; 
        cout << res << endl; 
    }
    
    
    return 0; 
}