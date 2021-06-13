#include<stdio.h>
#include<windows.h>
#include "menu_header.h"

int main(){
    system("cls");

    int menuStatus = 1;
    int menuchoice = 0;
    

    while(menuStatus == 1){
        system("cls");
        printf("Crypto Buying/Selling simulator by smilardic");
        printf("\n\n");
        printf("1. Start\n");
        printf("2. Reset game\n");
        printf("\n");
        printf("-------------------\n");
        printf("3. EXIT\n");
        
        printf("\n>");
        scanf("%d", &menuchoice);

        switch(menuchoice){

            case 1:
                printf("Start gamae");
                Sleep(1000);
                system("cd ../out");
                system("start control.exe");
                system("start stats.exe");
                system("start portfolio.exe");
                menuStatus = 0;
            break;

            case 2:
                menuStatus = _ResetGame();
                printf("\nReset game: %d\n", menuStatus);
                system("pause");
            break;

            case 3:
                printf("Exitin da game");
                menuStatus = 0;
            break;

            default: printf("\nERROR: invalid command");    
        }
    }


    printf("\n\n");
    //system("PAUSE");
    return 0;
}