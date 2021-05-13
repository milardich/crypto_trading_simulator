#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include "control_header.h"

int main(){

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