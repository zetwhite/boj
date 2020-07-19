#include <iostream> 
#include <cmath> 
#include <cstdlib> 
#include <algorithm> 
using namespace std; 

class TeamInfo{
public : 
    int cnt; 
    int Da; 
    int Db;
    int Diff; 
}; 

istream& operator>> (istream& is, TeamInfo& b){
    is >> b.cnt >> b.Da >> b.Db; 
    b.Diff = abs(b.Da - b.Db);
    return is; 
}

ostream& operator << (ostream& os, TeamInfo& b){
    os << "( cnt = " << b.cnt << ", Da = " << b.Da << ", Db = " << b.Db << ", Diff = " << b.Diff << ")"; 
    return os; 
}

bool cmp (TeamInfo& left, TeamInfo& right){
    if(left.Diff > right.Diff )
        return true; 
    return false; 
}

int main(){
    int n, A, B;
    while(1){
        cin >> n >> A >> B; 
        if(n == 0 && A == 0 && B == 0) 
            break; 
        TeamInfo teams[n];  
        for(int i = 0; i < n; i++)
            cin >> teams[i]; 
        sort(teams, teams + n, cmp);

        int result = 0; 
        for(int i = 0; i < n; i++){
            int fromA = 0, fromB = 0; 
            if( A <= 0 ){ 
                fromB = teams[i].cnt; 
            }
            else if( B <= 0){
                fromA = teams[i].cnt;  
            }
            else{ 
                if(teams[i].Da < teams[i].Db){ 
                    int diff= A - teams[i].cnt; 
                    if( diff >= 0) 
                        fromA = teams[i].cnt; 
                    else{ 
                        fromA = (teams[i].cnt + diff); 
                        fromB = abs(diff); 
                    }
                } 
                else{ 
                    int diff = B - teams[i].cnt; 
                    if(diff >= 0)
                        fromB = teams[i].cnt; 
                    else{ 
                        fromB = (teams[i].cnt + diff); 
                        fromA = abs(diff); 
                    }    
                }
            }
            A -= fromA;  
            B -= fromB; 
            result += fromA * teams[i].Da + fromB * teams[i].Db;  
        }
        cout << result << endl; 
    }
    return 0; 
}