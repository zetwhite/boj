#include <iostream> 
#include <vector> 

using namespace std; 

const int MOD = 1'000'000'007; 
typedef long long ll; 

class SegTree{
private :
    const int initValue = 1; 
    int size; 
    int* data;

    void print(){
        for(int i = 1; i < size; i++){
            cout << data[i] << " "; 
        }
        cout << endl; 
    }

    int calSize(int n){
        int m = 1; 
        n = n - 1;
        while(n > 0){
            m = m << 1; 
            n = n >> 1; 
        }
        return m * 2; 
    }
public : 
    SegTree(vector<int>& values){
        size = calSize(values.size());  
        data = new int[size];

        for(int i = 0; i < values.size(); i++){
            data[size/2 + i] = values[i]; 
        } 
        for(int i = size/2 + values.size(); i < size; i++){
            data[i] = initValue; 
        }

        for(int i = size/2 - 1; i > 0; i--){
            data[i] = ((ll)data[i*2] * (ll)data[i*2 + 1]) % MOD; 
        }
    }

    void update(int index, int newValue){
        int realIndex = size/2 + index;
        data[realIndex] = newValue; 
        realIndex = realIndex / 2; 
        while (realIndex > 0){
            data[realIndex] = ((ll)data[realIndex*2] * (ll)data[realIndex*2 + 1]) % MOD; 
            realIndex = realIndex / 2; 
        }
    }

    int select(int start, int end, int rLeft = -1, int rRight = -1){
        if(rLeft == -1){
            rLeft = size / 2; 
            start = rLeft + start; 
        }
        if(rRight == - 1){
            rRight = size - 1; 
            end = rLeft + end; 
        }
        if(end < rLeft || rRight < start){
            return 1;
        }
        if(start <= rLeft && rRight <= end){
            int gap = rRight - rLeft; 
            int index = rLeft; 
            while(gap > 0){
                gap = gap >> 1; 
                index = index >> 1; 
            }
            return data[index];
        }
        int mid = (rLeft + rRight) / 2; 
        return ((ll)select(start, end, rLeft, mid) * (ll)select(start, end, mid+1, rRight)) % MOD;  
    }
}; 

int main(){
    int a, b, c; 
    cin >> a >> b >> c; 

    int n;
    vector<int> nums; 
    int tmp; 
    for(int i = 0; i < a; i++){
        cin >> tmp; 
        nums.push_back(tmp); 
    }

    SegTree tree(nums); 
    int q, w, e; 
    for(int i = 0; i < b + c; i++){
        cin >> q >> w >> e; 
        if(q == 1){
            tree.update(w-1, e); 
        }
        else if(q == 2){
            cout << tree.select(w-1, e-1) << "\n"; 
        }
    }
    return 0; 
}