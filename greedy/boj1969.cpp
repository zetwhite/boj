#include <iostream>
#include <vector>
using namespace std; 

int getIndex(char c){
    if(c == 'A')
        return 0; 
    else if(c == 'C')
        return 1; 
    else if(c == 'G')
        return 2; 
    else 
        return 3;
}

string getChar(int i){
    if(i == 0)
        return "A"; 
    else if (i == 1)
        return "C";
    else if (i == 2)
        return "G"; 
    else 
        return "T"; 
}

int main(void){
    int n, m; 
    cin >> n >> m; 
    vector<string> DNAs;
    for(int i = 0; i < n; i++){
        string s; 
        cin >> s; 
        DNAs.push_back(s); 
    }

    string res;
    int hamming_distance = 0; 
    for(int i = 0; i < m; i++){
        int count[4] = {0, }; 
        for(int j = 0; j < n; j++){
            count[getIndex(DNAs[j][i])]++; 
        }
        int max = count[0]; 
        int res_idx = 0; 
        for(int k = 1; k < 4; k++){
            if(count[k] > max){
                max = count[k]; 
                res_idx = k;
            }
        }
        hamming_distance += (n - max);
        res.append(getChar(res_idx)); 
    }
    cout << res << endl;
    cout << hamming_distance << endl;
    return 0;
}