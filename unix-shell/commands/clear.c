#include <stdio.h>

void clear(void){
    printf("\033[H\033[2J\033[3J");
    fflush(stdout);
}