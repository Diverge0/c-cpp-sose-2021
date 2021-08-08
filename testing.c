#include "atf.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    int min[] = {0, 0, 0};
    int c[] = {0, 0, 0};
    int max[] = {9, 9, 9};
    
    while(1){
        for(int i=0; i<3; i++){
            printf("%i ", c[i]);
        }
        printf(" --- %i\n", count_up(min, c, max, 2));
        usleep(100000);
    }


    return 0;
}