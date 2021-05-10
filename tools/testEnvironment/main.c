#include<stdio.h>

int main(){
    FILE * file = fopen("dat.txt", "r");
    if(file == NULL){
        return 1;
    }

    float broj = 0.0f;
    fscanf(file, "%f", &broj);
    printf("\nbroj: %f", broj);
    fclose(file);
    return 0;
}