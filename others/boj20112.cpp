#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h> 

int main(){
    int n; 
    scanf("%d", &n); 
    getchar(); 

    char** arr; 
    arr = (char**)malloc(sizeof(char*)* n); 
    for(int i = 0; i < n; i++){
        arr[i] = (char*)malloc(sizeof(char)*n); 
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            //printf("%d %d\n", i, j); 
            arr[i][j] = getchar(); 
        }
        getchar(); 
    }

    bool success = true; 
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= i; j++){
            if(arr[i][j] != arr[j][i]){
                success = false; 
                break; 
            }
            if(success == false)
                break; 
        }
    }
    
    /*
    bool success = true; 
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(arr[i][j] != arr[j][i]){
                success = false; 
                break; 
            } 
        }
        if(success == false)
            break; 
    }  */

    if(success)
        printf("YES");
    else 
        printf("NO"); 
    return 0; 
}