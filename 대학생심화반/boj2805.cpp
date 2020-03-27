#include <bits/stdc++.h>

using namespace std;

int *n_heights;

static inline long long get_meter(int height, int n){
    long long meter = 0;
    for(int i = 0; i < n; i++){
        if(height < n_heights[i]){
            meter += (n_heights[i] - height);
        }
    }
    return meter;
}

static int getsign(long long num){
    return (num > 0) - (num < 0);
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    int m;
    int max_height = 0;
    int min_height = 0;
    cin >> n >> m;
    n_heights = new int[n];
    for(int i = 0; i < n; i++){
        cin >> n_heights[i];
        if(max_height < n_heights[i])
            max_height = n_heights[i];
    }

    int start_ht = min_height;
    int end_ht = max_height;
    int cut_ht = (start_ht + end_ht) / 2;
    long long meter = get_meter(cut_ht, n);
    int difference = getsign(meter - m);

    while(difference != 0 && start_ht < end_ht){
        if(difference > 0){
            start_ht = cut_ht + 1;
            cut_ht = (start_ht + end_ht) / 2;
        }
        else{
            end_ht = cut_ht - 1;
            cut_ht = (start_ht + end_ht) / 2;
        }
        meter = get_meter(cut_ht, n);
        difference = getsign(meter - m);
    }

    if(difference < 0)
        cut_ht += difference;
    cout << cut_ht << endl;

    delete[] n_heights;
    return 0;
}
