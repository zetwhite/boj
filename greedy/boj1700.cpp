#include <iostream> 
#include <vector>
#include <list> 
#include <queue>
using namespace std;

int find(int* current, int n, int number){
    for(int i = 0; i < n; i++){
        if(number == current[i])
            return i; 
    }
    return -1; 
}

int find_less(int* current, int n, queue<int>* next_list){
    int less_idx = -1; 
    int less_punch = 101;
    int front = -1; 
    for(int i = 0; i < n; i++){
        int c = current[i]; 
        if(next_list[c].empty())
            return i; 
        if(next_list[c].front() > front){
            front = next_list[c].front(); 
            less_idx = i; 
        }
    }
    return less_idx; 
}

void print_current(int* current, int n){
    cout << "current : "; 
    for(int i = 0; i < n; i++)
        cout << current[i] << " "; 
    cout <<endl; 
}


int main(){
    int n, k;
    cin >> n >> k; 
    vector<int> seq;
    queue<int> next_list[k+1]; 
    for(int i = 0; i < k; i++){
        int tmp; 
        cin >> tmp; 
        seq.emplace_back(tmp); 
        next_list[tmp].push(i); 
    }
    int res = 0;
    int* current = new int[n](); 
    for(int i = 0; i < k; i++){
      //  cout << "=============================" << endl; 
      //  cout << "seq = " << seq[i] << endl;
      //  print_current(current, n); 

        int idx = find(current, n, seq[i]); 
        if(idx != -1){
            next_list[current[idx]].pop(); 
            continue; 
        }
        idx = find(current, n, 0); 
        if(idx != -1){
            current[idx] = seq[i]; 
            next_list[current[idx]].pop(); 
            continue; 
        }
        idx = find_less(current, n, next_list); 
        current[idx] = seq[i];
        next_list[current[idx]].pop(); 
        res++; 
    }
    cout << res << endl;
    return 0; 
}