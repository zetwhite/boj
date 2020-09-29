#include <iostream> 
#include <queue> 
#include <algorithm> 
using namespace std; 

int original[21][21];
//int making[21][21]; 
int answer[21][21]; 
int n; 

const int MAX = 10'101; 

void print(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << answer[i][j] << "\t"; 
        }
        cout << endl; 
    }
}

pair<int, int> findMin(){
    int value = MAX; 
    pair<int, int> min = make_pair(-1, -1); 
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(i == j)
                continue; 
            if(original[i][j] == answer[i][j])
                continue; 
            if(value > original[i][j]) {
                min = make_pair(i, j);
                value = original[i][j]; 
            } 
        }
    }
    return min; 
}

void update(int updateX, int updateY){
    queue<pair<int,int>> next; 
    next.emplace(updateX, updateY); 
    next.emplace(updateY, updateX); 
    while(next.empty() == false){
        int a = next.front().first; 
        int b = next.front().second; 
        next.pop(); 
        for(int i = 0;i < n; i++){
            if(a == i)
                continue; 
            int exp = answer[a][b] + answer[b][i]; 
            if(answer[a][i] > exp){
                //cout << "update (" << a << ", " << i << ") = " << exp << endl; 
                answer[a][i] = exp; 
                answer[i][a] = exp; 
                next.emplace(i, a); 
                next.emplace(a, i); 
            }
        }
    }
}

bool floyd(){
    for(int k = 0; k < n; k++){ //middle node 
        for(int i = 0; i < n; i++){ //start node 
            for(int j = i+1; j < n; j++){ //end node
                int exp = original[i][k] + original[k][j]; 
                if(original[i][j] > exp){
                    return false; 
                    original[i][j] = exp; 
                    original[j][i] = exp; 
                } 
            }
        }
    }
    return true; 
}

int main(){
    ios_base :: sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    cin >> n; 
    int tmp; 
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> tmp; 
            original[i][j] = tmp;  
            if(i == j) 
                answer[i][j] = 0; 
            else 
                answer[i][j] = MAX; 
        }
    }

    bool check = floyd(); 
    if(check == false){
        cout << "-1" << endl; 
        return 0; 
    }

    int total = 0; 
    while(1){
        pair<int, int> needed = findMin(); 
        if(needed.first == -1)
            break; 
        int value = original[needed.first][needed.second]; 
        answer[needed.first][needed.second] = value; 
        answer[needed.second][needed.first] = value; 
        total += value; 
        update(needed.first, needed.second); 
        //cout << "===============================================" << endl; 
        //cout << "(" << needed.first << ", " << needed.second << "), value = " << value << endl; 
        //print(); 
    }

    cout << total << endl; 
    return 0; 
}