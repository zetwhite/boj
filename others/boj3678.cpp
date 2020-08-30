#include <iostream> 
#include <vector>
#include <cstring> 

using namespace std; 

int count[6];
int min;  

int gStart = 8; 
int gEnd = 19; 
int gGap = 12; 
int gLayer = 2; 

void getNextLayer(){
    gGap = gGap + 6; 
    gStart = gEnd + 1;
    gEnd = gEnd + gGap; 
    gLayer++; 
}

vector<int> getNeighbor(int index){
    vector<int> result; 
    int front = index - 1; 
    if(front < gStart) 
        front = gEnd; 
    int back = index + 1; 
    if(back > gEnd) 
        back = gStart; 
    result.push_back(front); 
    result.push_back(back);

    int localGap = gEnd - index; 
    int inner = index - (gGap - (localGap/gLayer));

    int beforeStart = gStart - gGap + 6; 
    if(inner < beforeStart)
        result.push_back(gStart - 1); 
    else
        result.push_back(inner); 

    if(localGap % gLayer != 0)
        result.push_back(inner + 1); 
    
    return result; 
}


int main(){
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    
    int c; 
    cin >> c;
    int max = 7; 
    vector<int> query;
    query.reserve(c);  
    for(int i = 0; i < c; i++){
        int tmp; 
        cin >> tmp; 
        query.push_back(tmp); 
        if(max < tmp) 
            max = tmp; 
    }
 
    int hexNums[max+1]; 
    for(int i = 1; i <= 5; i++)
        hexNums[i] = i; 
    hexNums[6] = 2; 
    hexNums[7] = 3; 
    count[1] = 1; 
    count[2] = 2; 
    count[3] = 2; 
    count[4] = 1; 
    count[5] = 1;  

    bool check[6]; 

    for(int i = 8; i <= max; i++){
        if(i > gEnd)
            getNextLayer(); 
        memset(check, 0, sizeof(bool)*6); 
        vector<int> nei = getNeighbor(i); 
        for(int j = 0; j < nei.size(); j++){
            if(nei[j] < i)
                check[hexNums[nei[j]]] = true; 
        }
        
        int minIndex = -1; 
        int minValue = 10001; 
        for(int j = 1; j <= 5; j++){
            if(check[j] == false && minValue > count[j]){
                minIndex = j; 
                minValue = count[j]; 
           }
        }
        hexNums[i] = minIndex; 
        count[minIndex] ++; 
    }

    for(int i = 0; i < query.size(); i++){
        cout << hexNums[query[i]] << endl; 
    }

    return 0; 
}