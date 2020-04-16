#include <iostream>
using namespace std;

char board[51][51];
int n;

void update(int line, bool is_row, int& max){
    int tmp = 1;
    for(int i = 0; i < n; i++){
        if(is_row){
            if(i!=n-1 && board[line][i]==board[line][i+1]) tmp++;
            else {
                if(tmp > max) max =tmp;
                tmp = 1;
            }
        }
        else{
            if(i!=n-1 && board[i][line]==board[i+1][line]) tmp++;
            else{
                if(tmp > max) max = tmp;
                tmp = 1;
            }
        }
    }
    return;
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            cin >> board[i][j];
    }

    int max = 1;
    for(int i = 0; i < n; i++){
        update(i, true, max);
        update(i, false, max);
    }

    for(int i = 0; i < n-2; i++){
        for(int j = 0; j < n-2; j++){
            swap(board[i][j], board[i][j+1]);
            update(i, true, max);
            update(j, false, max);
            update(j+1, false, max);
            swap(board[i][j], board[i][j+1]);

            swap(board[i+1][j], board[i][j]);
            update(i, true, max);
            update(i+1, true, max);
            update(j, false, max);
            swap(board[i+1][j], board[i][j]);
        }
    }

    swap(board[n-1][n-1], board[n-1][n-2]);
        update(n-1, true, max);
        update(n-1, false, max);
        update(n-2, false, max);
    swap(board[n-1][n-1], board[n-1][n-2]);

    swap(board[n-1][n-1], board[n-2][n-1]);
        update(n-1, true, max);
        update(n-2, true, max);
        update(n-1, false, max);
    cout << max << endl;
    return 0;
}
