#include<stdio.h>
#include<windows.h>
int main(){
    system("cls");

    int menuchoice = 0;
    printf("Crypto Buying/Selling simulator by smilardic");
    printf("\n\n");
    printf("1. Start\n");
    printf("2. Options\n");
    printf("\n");
    printf("3. Transactions\n");
    printf("-------------------\n");
    printf("4. EXIT\n");
    
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
        break;

        case 2:
            printf("Neki opsnsi");
        break;

        case 3:
            printf("List of transactions");
        break;

        case 4:
            printf("Exitin da game");
        break;

        default: printf("\nerror\n");    
    }

    printf("\n\n");
    //system("PAUSE");
    return 0;
}