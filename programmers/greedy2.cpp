#include <string>
#include <vector>
#include <iostream> 

using namespace std;

void findLongestAIndex(string name, int& start, int& size){
    int n = name.size(); 
    int idx = 0; 
    size = 0; 
    if(name[0] == 'A'){
        while(name[idx] == 'A'){
            idx = idx - 1; 
            if( idx == -1 ){
                idx = n - 1; 
            }
            if( idx == 0 ){
                size = n; 
                return; 
            }
        }
    }
    else{
        while(name[idx] != 'A'){
            idx = idx + 1; 
            if(idx == n)
                return; 
        }
    }
    int end = idx; 
    if(end < 0)
        end = n - 1;
    
    size = 0; 
    start = 0; 
    while(1){
        int loc_start = idx; 
        int loc_max = 0; 
        while(name[idx] == 'A'){
            idx = idx + 1; 
            if( idx == n )
                idx = 0; 
            loc_max++;  
        }
        if(loc_max > size ){
            size = loc_max; 
            start = loc_start; 
        }
        while(name[idx] != 'A'){
            idx++; 
            if(idx == n )
                idx = 0; 
            if(idx == end )
                return; 
        }
    }
}

int min(int a, int b){
    if(a > b)
        return b; 
    return a; 
}

int findMove(char dest){
    int way1 = abs(dest - 'A'); 
    int way2 = abs('Z' - dest) + 1;  
    cout << "to Dest "<< dest << " " << way1 << ", " << way2 << "is needed" << endl; 
    return min(way1, way2); 
}

int solution(string name) {
    int answer = 0;
    int index = 0; 
    int size = 0; 
    int n = name.size(); 
    findLongestAIndex(name, index, size); 
    cout << "index = " << index << endl; 
    cout << "size = " << size << endl; 
    if(size == n)
        return answer; 
    else if(size == 0){
        for(int i = 0; i < n; i++){
            answer += findMove(name[i]); 
            answer += 1; 
        }
        answer -= 1; 
        return answer; 
    }
    else if(index+size >= n){
        int fromBegin = (index + size) - n; 
        int fromEnd = n - index + 1; 
        if(fromBegin < fromEnd){
            answer += fromBegin; 
            for(int i = fromBegin; i < index; i++){
                answer += findMove(name[i]); 
                answer += 1; 
            }
            answer -= 1; 
        }
        else{
            answer += fromEnd; 
            for(int i = index - 1; i >= fromBegin; i--){
                answer += findMove(name[i]); 
                answer += 1; 
            }
            answer -= 1; 
        }
        return answer; 
    }
    else{
        int sz1 = index; 
        int sz2 = size; 
        int sz3 = n - (index + size); 
        
        if(sz1 > sz3){
            answer += 1; 
            for(int i = n-1; i >= index + size; i--){
                answer += findMove(name[i]); 
                answer += 1; 
            }
            answer -= 1; 
            
            //compare sz3 and sz2
            if((sz2+1) < sz3)
                answer += (sz2 + 1); 
            else
                answer += sz3; 
            for(int i = 0; i < index; i++){
                answer += findMove(name[i]); 
                answer += 1; 
            }
            answer -= 1; 
        }
        else{
            for(int i = 0; i < index; i++){
                answer += findMove(name[i]); 
                answer += 1; 
            }
            answer -= 1; 
        
            if(sz1 < (sz2 + 1))
                answer += sz1;
            else
                answer += (sz2 + 1); 
            for(int i = n-1; i >= index + size; i--){
                answer += findMove(name[i]); 
                answer += 1; 
            }
            int lastSec = 0; 
            for(int i = n - 1; i >= index + size; i--){
              if(name[i] != 'A')
                break; 
              lastSec++; 
            }
            answer -= 1; 
        }
        return answer; 
    }
    return answer;
}

int main(){
  string s; 
  cin >> s; 
  cout << solution(s) << endl; 
  return 0; 
}