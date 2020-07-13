#include <iostream> 
#include <vector> 
typedef long long ll; 
using namespace std;

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


void getInput(char** p, int n){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 4*n - 1; j++){
            cin >> p[i][j]; 
        }
    }
}

int findNumber(char **p, int n, vector<short>& res){
    bool fail = false; 
    int k = 0; 
    for(int k = 0; k < 10; k++){
        fail = false;     
        for(int i = 0; i < 5; i ++){
            for(int j = 0; j < 3; j++){
                if(Num[k][i][j] == '.' && p[i][n*4 + j] == '#'){
                    fail = true; 
                    break; 
                }
            }
            if(fail) 
                break; 
        }
        if(fail)
            continue;
        res.push_back(k); 
    }
    return -1; 
}

void makeNumber(int idx, int last, ll num, vector<short> (*ingredient), ll& result){
    if(idx == last){
        result += num; 
    }  
    else{
        for(int i = 0; i < ingredient[idx].size(); i++)
            makeNumber(idx + 1, last, num*10 + ingredient[idx].at(i), ingredient, result); 
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; 
    cin >> n; 

    char** painting = new char*[5]; 
    for(int i = 0; i < 5; i++)
        painting[i] = new char[4*n]; 
    getInput(painting, n); 
    
    vector<short> ingredient[n]; 
    for(int i = 0; i < n; i++){
        findNumber(painting, i, ingredient[i]); 
        if(ingredient[i].size() == 0){
            cout << "-1" << endl;
            return 0; 
        } 
    }

    //vector<int> results; 
    ll res = 0; 
    ll cnt = 1; 
    for(int i = 0; i < n; i++){
        cnt *= ingredient[i].size(); 
    }

    ll base = 1; 
    for(int i = n-1; i >= 0; i--){
        for(int j = 0; j < ingredient[i].size(); j++){
            //cout << base * ingredient[i][j]; 
            //cout << " * " << cnt / ingredient[i].size() << endl;  
            res += base * ingredient[i][j] *  cnt / ingredient[i].size(); 
        }
        base *= 10; 
    }
    cout << static_cast<double>(res) / cnt << endl; 

    return 0; 
}