#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long outer(int p1_x, int p1_y, int p2_x, int p2_y){
    long long px = p2_x - p1_x;
    long long py = p2_y - p1_y;
    return p1_x*py - p1_y*px;
}

int main(){
    int n;
    scanf("%d", &n);
    int* x_coo = (int*)malloc(sizeof(int)*n);
    int* y_coo = (int*)malloc(sizeof(int)*n);
    for(int i = 0; i < n; i++){
        scanf("%d", x_coo+i);
        scanf("%d", y_coo+i);
    }

    long long res = 0;
    for(int i = 0; i < n-1; i++)
        res += outer(x_coo[i], y_coo[i], x_coo[i+1], y_coo[i+1]);
    res += outer(x_coo[n-1], y_coo[n-1], x_coo[0], y_coo[0]);

    double result = fabs(res);
    result = round(result/2 * 10)/10;
    printf("%.1f\n", result);
    return 0;
}
