#include<iostream>
using namespace std;

void print(int** table, int n, int m){
    for(int i = 0; i< n+2; i++){
        for(int j = 0; j < m+2; j++)
            cout << table[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    int sz = 0;
    cin >> n >> m;
    int** table = new int*[n+2];
    for(int i = 0; i < n+2; i++)
        table[i] = new int[m+2];
    for(int j = 0; j < m+2; j++){
        table[0][j] = 0;
        table[n+1][j] = 0;
    }

    char* tmp = new char[m];
    for(int i = 1; i < n+1; i++){
        table[i][0] = 0;
        cin >> tmp;
        for(int j = 0; j < m; j++){
            table[i][j+1] = tmp[j]-'0';
        }
        table[i][m+1] = 0;
    }

    int x = n;
    int y = m;
    while(x > 0){
        y = m;
        while(y > 0){
            if(table[x][y]){
                int min = table[x][y+1];
                if(min > table[x+1][y]) min = table[x+1][y];
                if(min > table[x+1][y+1]) min = table[x+1][y+1];
                table[x][y] = ++min;
                if(sz < table[x][y]) sz = table[x][y];
            }
            y--;
        }
        x--;
    }
    cout << sz*sz <<"\n";
    return 0;
}
