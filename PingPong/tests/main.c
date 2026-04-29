#include <stdio.h>

int
main(void){
    int x = 0;
    for(int i=0; i < 10; i++){
        if(x == 0){
            printf("X == 0 TRUE\n");
            x = 1;
        } else if(x == 1){
            printf("X == 1 TRUE\n");
            x = 0;
        }
    }
}
