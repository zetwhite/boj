#include <iostream> 
#include <cstring>
using namespace std; 

void print(unsigned int& set){
    for(int i = 20; i >= 1; i--){
        unsigned int res = (set & (1 << (i-1))); 
        if(res) cout << "1";
        else cout << "0";        
    }
    cout << endl; 
}

inline void add (unsigned int& set){
    int x; 
    cin >> x; 
    set |= (1 << (x-1)); 
}

inline void remove(unsigned int& set){
    int x; 
    cin >> x; 
    set &= ~(1 << (x-1)); 
}

inline void check(unsigned int& set){
    int x; 
    cin >> x; 
    unsigned int res = (set & (1 << (x-1))); 
    if(res) cout << "1\n";
    else cout << "0\n"; 
}

void toggle(unsigned int& set){
    int x; 
    cin >> x; 
    set ^= (1 << (x-1));
}

void all(unsigned int& set){
    set = -1; 
}

void empty(unsigned int& set){
    set = 0; 
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    unsigned int set; 
    set = 0; 
    int m; 
    cin >> m; 
    for(int i = 0; i < m; i++){
        string s; 
        cin >> s;
        if(s == "add")
            add(set); 
        else if (s == "remove")
            remove(set); 
        else if(s == "check")
            check(set); 
        else if(s == "toggle")
            toggle(set); 
        else if(s == "all")
            all(set); 
        else if(s == "empty")
            empty(set);
      //  print(set);  
    }
    return 0;
}