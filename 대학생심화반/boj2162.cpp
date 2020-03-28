#include <bits/stdc++.h>

using namespace std;

class Vec{
public:
    int x;
    int y;
    Vec(int _x, int _y):x(_x), y(_y){}
    Vec(){}
    Vec operator - (Vec const& a){
        Vec res;
        res.x = x - a.x;
        res.y = y - a.y;
        return res;
    }
    bool operator < (Vec const& a){
        if(x == a.x)
            return y < a.y;
        return x < a.x;
    }
};

inline int outer(Vec v1, Vec v2){
    return v1.x*v2.y - v1.y*v2.x;
}

inline void swap(Vec& v1, Vec& v2){
    int tmp_x = v1.x;
    int tmp_y = v1.y;
    v1.x = v2.x; v1.y = v2.y;
    v2.x = tmp_x; v2.y = tmp_y;
}

bool segment_intersect(Vec a1, Vec a2, Vec b1, Vec b2){
    long long res1 = 1ll*outer(a2-a1, a2-b1) * outer(a2-a1, a2-b2);
    long long res2 = 1ll*outer(b2-b1, b2-a1) * outer(b2-b1, b2-a2);
    if(res1 == 0 && res2 == 0){
        if(a2 < a1) swap(a1, a2);
        if(b2 < b1) swap(b1, b2);
        return !(a2 < b1 || b2 < a1);
    }
    else
        return (res1 <= 0  &&  res2 <= 0);
}

int find_root(int* group_pointer, int n){
    while(group_pointer[n]!=n){
        n = group_pointer[n];
    }
    return n;
}

void union_new(int* group_pointer, int* group_size, int old, int n){ //a < b
    int old_root = find_root(group_pointer, old);
    int n_root = find_root(group_pointer, n);
    group_pointer[n_root] = old_root;
    group_size[old_root] += group_size[n_root];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    Vec* starts = new Vec[n];
    Vec* ends = new Vec[n];
    int* group_pointer = new int[n];
    int* group_size = new int[n];
    for(int i = 0; i < n; i++)
        group_pointer[i] = i;
    for(int i = 0; i < n; i++)
        group_size[i] = 1;
    for(int i = 0; i < n; i++){
        cin >> starts[i].x >> starts[i].y >> ends[i].x >> ends[i].y;
    }

    for(int i = 1; i < n; i++){
        for(int j = i-1; j >=0; j--){
            if(find_root(group_pointer, i) == find_root(group_pointer, j))
                continue;
            if(segment_intersect(starts[i], ends[i], starts[j], ends[j]))
                union_new(group_pointer, group_size, j, i);
        }
    }

    int count = 0;
    int max_size = 0;
    for(int i = 0; i < n; i++){
        if(group_pointer[i] == i){
            count++;
            if(max_size < group_size[i]) max_size = group_size[i];
        }
    }
    cout << count << endl;
    cout << max_size << endl;
    return 0;
}
