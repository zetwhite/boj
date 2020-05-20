#include <iostream> 
using namespace std; 
typedef long long ll; 
const ll DIV = 1000000007;  //111011100110101100101000000111
const int LEN = 30; 

ll n_fact[4000001] = {0, }; 
ll n_iv_fact[4000001] = {0, }; 
int idx = 1; 
int iv_idx = 1; 

bool bin[64]; 
int bin_size; 

void init_bin(int a){
    bin_size = 0; 
    while(a > 0){
        if(a % 2)
            bin[bin_size] = 1;
        else
            bin[bin_size] = 0;
        bin_size++; 
        a = a/2;
    }
}

//FIT : a^(p-1) = 1 (mod p)
//a^(-1) = a^(p-2)
ll get_power(int n){
    int i = bin_size - 2;
    ll res = n; 
    while(i >= 0){
        res = (res * res) % DIV; 
        //cout << "[" << i << "], res = " << res << " (sqaure)" << endl; 
        if(bin[i]){
            res = (res * n) % DIV; 
            //cout << "[" << i << "], res = " << res << " (multiply)" << endl;
        }
        i--;
    }
    return res;
}

void fill_fact(int n){
    for(int i = idx + 1; i <= n; i++){
        n_fact[i] = (n_fact[i-1] * i)% DIV;
    }
    idx = n;
}

void fill_iv_fact(int n){
    for(int i = iv_idx + 1; i <= n; i++){
        n_iv_fact[i] = (n_iv_fact[i-1] * get_power(i)) % DIV; 
      //cout << "iv_fact[" << i << "] = " << n_iv_fact[i] << endl;
    }
    iv_idx = n; 
}

ll getFact(int n){
    if(n > idx){
        fill_fact(n);
    }
    return n_fact[n]; 
}

ll getInvFact(int n){
    if(n > iv_idx)
        fill_iv_fact(n);
    return n_iv_fact[n]; 
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init_bin(DIV-2); 
    int m; 
    cin >> m; 
    n_fact[0] = 1; 
    n_fact[1] = 1;
    n_iv_fact[0] = 1;
    n_iv_fact[1] = 1; 
    for(int i = 0; i < m; i++){
        int n, k; 
        cin >> n >> k;
        ll res = getFact(n); 
        res *= getInvFact(n-k);
        res %= DIV; 
        res *= getInvFact(k);   
        res %= DIV;
        cout << res << "\n";
    }
    return 0; 
}