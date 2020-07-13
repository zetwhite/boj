#include <iostream> 
#include <stdexcept> 
#include <algorithm>
#include <cstring>
using namespace std;

inline int STR2NUM(char x) {
    if(x < 'A')
        return static_cast<int>(x-'0'); 
    else 
        return static_cast<int>(x-'A'+10); 
}

inline char NUM2STR(int x){
    if(x < 10)
        return static_cast<char>('0' + x); 
    else
        return static_cast<char>(x - 10 +'A'); 
}

inline int max_int(int a, int b){
    if(a > b)
        return a; 
    return b; 
}

class Hexatri{
public:
    static const int max = 52; 
    char value[max]; 
    int len; 
    bool checker[36]; 

    Hexatri(string str){
        int v_idx = max -1; 
        for(int i = str.size()-1; i>= 0; i--){
            value[v_idx] = str[i]; 
            v_idx--; 
            checker[STR2NUM(str[i])] = true; 
        }
        len = str.size(); 
        for(int i = v_idx; i>= 0; i--)
            value[i] = '0';
    }

    Hexatri(){
        for(int i = max-1; i >= 0; i--)
            value[i] = '0'; 
        len = 0; 
    }

    char& operator[] (int index){
        if(index >= 52 || index < 0){
            throw out_of_range("index error Hexatri"); 
        }
        return value[index]; 
    }

    Hexatri operator+ (const Hexatri& another){
        Hexatri new_hextri;
        int from_last = 0; 
        int max_len = max_int(len, another.len); 
        for(int i = 1; i <= max_len; i++){
            int res = STR2NUM(value[max-i]) + STR2NUM(another.value[max-i]) + from_last; 
            from_last = res / 36 ; 
            new_hextri[max - i] = NUM2STR(res % 36);
        }
        if(from_last != 0){
            new_hextri[max - max_len - 1] = NUM2STR(from_last); 
            new_hextri.len = max_len + 1; 
        }
        else{
            new_hextri.len = max_len;
        }
        return new_hextri; 
    }

    Hexatri operator= (const Hexatri& another){
        memcpy(value, another.value, max);
        this->len = another.len; 
        return *this; 
    }
}; 

bool operator< (const Hexatri& right, const Hexatri& left){
    for(int i = 0; i < right.max; i++){
        if(right.value[i] < left.value[i])
            return true; 
        else if(right.value[i] > left.value[i])
            return false; 
    }
    return false; 
}

Hexatri get_diff_by_alpha(Hexatri& h, char alpha){
    Hexatri new_hexatri; 
    int diff = STR2NUM('Z') - STR2NUM(alpha); 
    for(int i = 1; i <= h.len; i++){
        if(h[h.max - i] == alpha){
            new_hexatri[h.max - i] = NUM2STR(diff); 
        }
    }
    new_hexatri.len = h.len; 
    return new_hexatri; 
}


ostream& operator<< (ostream& os, Hexatri& h){
    for(int i = 0; i < h.len; i++)
        cout << h[h.max - h.len + i]; 
    return os; 
}

int main(){
    Hexatri diff_by_alpha[36]; 
    bool checker[36] = {false, }; 

    int n; 
    cin >> n; 
    Hexatri* ht[n];   
    for(int i = 0; i < n; i++){
        string s; 
        cin >> s; 
        ht[i] = new Hexatri(s); 
        for(int j = 0; j < s.length(); j++)
            checker[STR2NUM(s[j])] = true; 
    }

    for(int k = 0; k < 36; k++){
        if(checker[k] == 0)
            continue; 
        for(int i = 0; i < n; i++){
            if(ht[i]->checker[k] == 0)
                continue; 
            Hexatri tmp = get_diff_by_alpha((*ht[i]), NUM2STR(k)); 
            diff_by_alpha[k] = diff_by_alpha[k] + tmp; 
        }
    }

    for(int i = 35; i > 0; i--){
        for(int j = 0; j < i; j++) {
            if(diff_by_alpha[j] < diff_by_alpha[i]){
                Hexatri tmp = diff_by_alpha[j]; 
                diff_by_alpha[j] = diff_by_alpha[i]; 
                diff_by_alpha[i] = tmp; 
            }
        }
    }

    Hexatri result; 
    for(int i = 0; i < n; i++)
        result = result + (*ht[i]); 
    int k; 
    cin >> k; 
    for(int i = 0; i < k; i++)
        result = result + diff_by_alpha[i]; 
    cout << result << endl; 
    return 0; 
}
