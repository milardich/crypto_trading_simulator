#include<stdio.h>

int main(){
    FILE * file = fopen("dat.txt", "r");
    if(file == NULL){
        return 1;
    }

    int broj = 0;
    broj = fgetc(file) - 48;
    printf("\nbroj: %d", broj);
    return 0;
}