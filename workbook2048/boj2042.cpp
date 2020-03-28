#include <bits/stdc++.h>

using namespace std;

class Segtree{
private:
    int half;
    int length;
    long long *arr;
    int get_power_two(int a){
        int res = 1;
        while(a > res)
            res = res << 1;
        return res;
    }
    void check_pos(long long *sum, int pos, int pos_r1, int pos_r2, int r1, int r2){
        if(r1 <= pos_r1 && pos_r2 <= r2)
            *sum += arr[pos];
        else if(r2 < pos_r1 || pos_r2 < r1)
            return;
        else{
            check_pos(sum, pos<<1, pos_r1, (pos_r1 + pos_r2)>>1, r1, r2);
            check_pos(sum, (pos<<1) +1, ((pos_r1+pos_r2)>>1)+1, pos_r2, r1, r2);
        }
    }

public:
    Segtree(int len, long long* src);
    ~Segtree(){
        delete [] arr;
    }
    long long get_sum(int start, int end);
    void change_value (int pos, long long value);
};

Segtree::Segtree(int l, long long* src){
        half = get_power_two(l);
        length = half<<1;
        arr = new long long [length];
        memcpy(arr+half, src, l<<3);
        for(int i = 0; i < half - l; i++)
            arr[length-1-i] = 0;

        int cursor = half - 1;
        while(cursor > 0){
            arr[cursor] = arr[cursor<<1] + arr[(cursor<<1) + 1];
            cursor--;
        }
}

long long Segtree::get_sum(int start, int end){
    long long res = 0;
    check_pos(&res, 1, half, length-1, half+start-1, half+end-1);
    return res;
}

void Segtree::change_value(int pos, long long value){
    int cursor = half + pos -1;
    long long diff = value - arr[cursor];
    while(cursor > 0){
        arr[cursor] += diff;
        cursor = cursor>>1;
    }
}


int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    long long *tmp;
    tmp = new long long[n];
    for(int i = 0; i < n; i++)
        cin >> tmp[i];

    Segtree t(n, tmp);
    for(int i = 0; i < m+k; i++){
        int a, b;
        long long c;
        cin >> a >> b >> c;
        if(a == 1)
            t.change_value(b, c);
        if(a == 2)
            cout << t.get_sum(b, c) << endl;
    }
    return 0;
}