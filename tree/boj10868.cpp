#include <iostream> 
#include <vector> 
using namespace std; 

class SegTree{
private :
    static const int MAX = 1'000'000'005; 
    int size; 
    int* data; 
    void setSize(int n){  
        int power = 1; 
        while(n > 0){
            n = n >> 1; 
            power = power << 1; 
        } 
        size = power * 2;
    }

    int getValue(int start, int end){
        int gap = end - start + 1; 
        int index = start; 
        while(gap > 1){
            gap = gap >> 1; 
            index = index >> 1; 
        }
        //cout << "( start = " << start - size/2 + 1 << ", end = " << end - size/2 + 1 << ") = " << data[index] << endl;  
        return data[index]; 
    }
public: 
    SegTree(int n, vector<int>& inputs){
        setSize(n); 
        data = new int[size];
        int start = size/2;  
        for(int i = 0; i < inputs.size(); i++){
            data[size/2 + i] = inputs[i]; 
        }
        for(int i = size/2 + inputs.size(); i < size; i++){
            data[i] = MAX; 
        }
        for(int i = size/2 - 1; i > 0; i--){
            data[i] = min(data[i*2], data[i*2 + 1]); 
        }
    }

    int select(int start, int end, int rLeft = -1, int rRight = -1){
        if(rLeft == -1){
            rLeft = size/2;
            start = rLeft + start - 1; 
            end = rLeft + end - 1; 
        }  
        if(rRight == -1)
            rRight = size - 1;

        if(start <= rLeft && rRight <= end){
            return getValue(rLeft, rRight); 
        }
        if(rRight < start || rLeft > end) {
            return MAX; 
        }
        else{
            int mid = (rLeft + rRight) / 2; 
            return min(select(start, end, rLeft, mid), select(start, end, mid+1, rRight)); 
        }
    }
}; 

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 

    int n, m; 
    vector<int> in;
    int tmp;  
    
    cin >> n >> m; 
    for(int i = 0; i < n; i++){
        cin >> tmp; 
        in.push_back(tmp); 
    }
    SegTree tree(n, in);
    int a, b; 
    for(int i = 0; i < m; i++){
        cin >> a >> b; 
        cout << tree.select(a, b) << "\n";  
    }
    return 0; 
}