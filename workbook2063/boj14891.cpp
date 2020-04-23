#include <iostream>
#include <list>
#include <cstring>
#include <string>
using namespace std;

class Gear{
public:
    list<int> sense;
    bool right;
    bool left;
    Gear(){};
    void reset_right(){
        list<int>::iterator it = sense.begin();
        advance(it, 2);
        right = *it;
    }
    void reset_left(){
        list<int>::reverse_iterator rit = sense.rend();
        advance(rit, 2);
        left = *rit;
    }
    void move(bool is_clockwise){
        if(is_clockwise){
            int last = sense.back();
            sense.pop_back();
            sense.push_front(last);
        }
        else{
            int first = sense.front();
            sense.pop_front();
            sense.push_back(first);
        }
        reset_left();
        reset_right();
    }
    void print(){
        list<int>::iterator it = sense.begin();
        for(; it!=sense.end(); it++)
            cout << *it;
        cout << endl;
    }
};


istream& operator >> (istream& is, Gear& g){
    string s;
    is >> s;
    for(int i = 0; i < 8; i++){
        bool a = s[i] - '0';
        g.sense.push_back(a);
        if(i == 2){
            g.right = a;
        }
        if(i == 6){
            g.left = a;
        }
    }
    return is;
}

void chaining_move(bool* visited, Gear *gears, int idx, int dir){
    if(idx+1 < 4 && !visited[idx+1]){
        visited[idx+1] = true;
        if(gears[idx].right != gears[idx+1].left)
            chaining_move(visited, gears, idx+1, !dir);
    }
    if(idx-1 >= 0 && !visited[idx-1]){
        visited[idx-1] = true;
        if(gears[idx].left != gears[idx-1].right)
            chaining_move(visited, gears, idx-1, !dir);
    }
    gears[idx].move(dir);
}

void gear_print(Gear* g){
    for(int i = 0; i < 4; i++)
        g[i].print();
}

int main(){
    Gear gears[4];
    bool visited[4];
    for(int i = 0; i < 4; i++)
        cin >> gears[i];
    int m;
    cin >> m;
    for(int i = 0; i < m; i++){
        int idx, dir;
        cin >> idx >> dir;
        if(dir == -1) dir = 0;
        memset(visited, 0, sizeof(bool)*4);
        visited[idx-1] = true;
        chaining_move(visited, gears, idx-1, dir);
    }

    int res = 0;
    int pivot = 1;
    for(int i = 0; i < 4; i++){
        if(gears[i].sense.front() == 1){
            res += pivot;
        }
        pivot *= 2;
    }
    cout << res << endl;

    return 0;
}
