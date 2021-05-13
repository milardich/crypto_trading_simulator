#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
int main(){
    int c;
    int temp;

    
    while(1){
        FILE *file = fopen("../dat.txt", "r");
        if(file == NULL){
            printf("Could not open da file");
            return 1;
        }
        c = fgetc(file) - '0';
        temp = c;
        if(c == '\n'){
            c = temp;
        }
        printf("\rchar: %d", c);
        Sleep(1);
        fclose(file);
    }
    
}