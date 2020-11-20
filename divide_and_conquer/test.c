#include <stdio.h> 

int main(){
    int c = 0; 
    int noc = 0; 
    int nol = 0; 

    int tokens = 0; 
    int cnt = 0; 
    while((c = getchar()) != EOF){
        if(c == '\n') {
            if(cnt != 0){
                tokens++;
                cnt = 0;
            }
            //printf("tokens = %d\n", tokens);
            continue; 
        }

        if(c == '('){
            tokens++; 
            if(cnt != 0)
                tokens++;
            cnt = 0; 
        }
        else if( c == ')'){
            tokens++; 
            if(cnt != 0)
                tokens++; 
            cnt = 0; 
        }
        else if (c == ' '){
            if(cnt != 0){
                cnt = 0; 
                tokens++; 
            }
        }
        else{
            cnt++; 
        }
    }

    printf("%d\n", tokens); 
    return 0; 
}