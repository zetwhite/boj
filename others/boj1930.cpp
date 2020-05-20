#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; 

class Tetrahedron{
public: 
    int down; 
    int upper;
    int right; 
    int left; 
    void mov_upper_left(){
        int _down = upper; 
        int _upper = right; 
        int _right = down; 
        down = _down;
        upper = _upper;
        right = _right;
    }
    void rotate(){
        int _upper = left;
        int _right = upper;
        int _left = right; 
        upper = _upper;
        right = _right;
        left = _left;
    }
};

void fill_tet(vector<int>& input, Tetrahedron& t){
    t.down = input[0];
    t.upper = input[1];
    t.right = input[2]; 
    t.left = input[3]; 
}

bool check_same(vector<int> f, vector<int> s){
    sort(f.begin(), f.end());
    sort(s.begin(), s.end()); 
    for(int i = 0; i < 4; i++){
        if(f[i] != s[i])
            return false; 
    }
    return true;
}

bool operator == (Tetrahedron& a, Tetrahedron& b){
    if(a.down != b.down)
        return false; 
    if(a.upper != b.upper)
        return false; 
    if(a.left != b.left)
        return false; 
    if(a.right != b.right)
        return false;
    return true;
}

int main(){
    int t; 
    cin >> t;
    Tetrahedron first, second;  
    vector<int> f_input, s_input;
    for(int i = 0; i < t; i++){
        f_input.clear();
        s_input.clear(); 
        for(int j = 0; j < 4; j++){
            int n; 
            cin >> n; 
            f_input.push_back(n); 
        }
        for(int j = 0; j < 4; j++){
            int n; 
            cin >> n; 
            s_input.push_back(n);
        }
        fill_tet(f_input, first); 
        fill_tet(s_input, second); 
        if(check_same(f_input, s_input) == false){
            cout << 0 << endl; 
            continue; 
        }
        bool success = false;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                second.rotate(); 
                if(first == second){
                    success = true;
                    break;
                }
            }
            if(success)
                break;
            second.mov_upper_left();
        }
        if(success == false){
            second.rotate(); 
            second.mov_upper_left(); 
            for(int j = 0; j < 3; j++){
                second.rotate();
                if(first == second){
                    success = true;
                    break; 
                }
            }
        }
        if(success)
            cout << 1 << endl;
        else
            cout << 0 << endl;        
    }
    return 0;
}