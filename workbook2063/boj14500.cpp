#include <iostream>
#include <cstring>
using namespace std;

struct Tetromino{
    int height;
    int width;
    int block[4][4];
    void print(){
        cout << "height : " << height << endl;
        cout << "width : " << width << endl;
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                cout << block[i][j] << ' ';
            }
            cout << endl;
        }
    }
};

class Board{
public:
    int** board;
    int height;
    int width;
    Board(int n, int m):height(n), width(m){
        board = new int*[height];
        for(int i = 0; i < height; i++){
            board[i] = new int[width];
        }
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                cin >> board[i][j];
            }
        }
    }
    int upload_tet(struct Tetromino& t){
        int max = 0;
        int sum = 0;
        for(int i = 0; i <= (height - t.height); i++){
            for(int j = 0; j <= (width - t.width); j++){
                sum = 0;
                for(int h = 0; h < t.height; h++){
                    for(int w = 0; w < t.width; w++){
                        sum += board[i+h][j+w] * t.block[h][w];
                    }
                }
                if(max < sum) max = sum;
            }
        }
        return max;
    }
    ~Board(){
        for(int i = 0; i < height; i++){
            delete[] board[i];
        }
    }
};

void rotate(struct Tetromino& t){
    struct Tetromino tmp;
    tmp.width = t.height;
    tmp.height = t.width;
    for(int i = 0; i < t.height; i++){
        for(int j = 0; j < t.width; j++){
            tmp.block[t.width - j -1][i] = t.block[i][j];
        }
    }
    memcpy(&t, &tmp, sizeof(struct Tetromino));
    return;
}

int main(){
    struct Tetromino tet[7];
    tet[0] = {1, 4, {{1, 1, 1, 1}}};
    tet[1] = {2, 2, {{1, 1}, {1, 1}}};
    tet[2] = {3, 2, {{1, 0}, {1, 0}, {1, 1}}};
    tet[3] = {3, 2, {{1, 0}, {1, 1}, {0, 1}}};
    tet[4] = {2, 3, {{1, 1, 1}, {0, 1, 0}}};
    tet[5] = {3, 2, {{0, 1}, {0, 1}, {1, 1}}};
    tet[6] = {3, 2, {{0, 1}, {1, 1}, {1, 0}}};

    int n, m;
    cin >> n >> m;
    Board b(n, m);

    int max = 0;
    int sum = 0;

    for(int i = 0 ; i < 2; i++){
        sum = b.upload_tet(tet[0]);
        rotate(tet[i]);
        if(sum > max)  max = sum;
    }
    sum = b.upload_tet(tet[1]);
    if(sum > max) max = sum;
    for(int i = 2; i < 7; i++){
        for(int j = 0; j < 4; j++){
            sum = b.upload_tet(tet[i]);
            if(sum > max) max = sum;
            rotate(tet[i]);
        }
    }
    cout << max << endl;
    return 0;
}
