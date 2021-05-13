#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include "control_header.h"

int main(){
    /*
    FILE * userMoneyAmount = fopen("../out/files/usermoney.txt", "w");
    if(userMoneyAmount == NULL){
        printf("Could not open usermoney.txt file");
        return 1;
    }
    fclose(userMoneyAmount);
    */

    //

    char input[10];


    printf("COMMAND WINDOW\n\n");

    while(1){
        system("cls");

        //show commands 
        _DisplayCommands();

        //input commands
        _CommandInput(input);
        _ProcessCommand(input);
        
        printf("\n\n");
        system("pause");
    }
    


    //system("PAUSE");
    return 0;
}