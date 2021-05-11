#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

#include "../../tools/general_tools/general_tools.h"
#include "stats_header.h"


int main(){
    system("cls");
    printf("STATS\n\n");

    srand((unsigned)time(NULL));

    int isCryptoGenerated = 0;
    int numberOfCurrencies = 5;
    int isStatsRunning = 0;

    //read value from txt file (0 or 1) and store that value to isCryptoGenerated
    isCryptoGenerated = _IsCurrencyGenerated();
    isStatsRunning = isCryptoGenerated;

    //memory allocation
    CRYPTOCURRENCY *currency;
    currency = _Allocate(numberOfCurrencies);
    if(currency == NULL){
        printf("\nERROR: Memory allocation failed\n");
        return 1;
    }
    

    //check if crypto is already generated (if its not generated (0), generate currencies)
    if(isCryptoGenerated == 0){
        //Generate number of different cryptocurrencies and store them and their properties in da files
        _GenerateCurrencies(currency);
        _SaveCurrenciesToFiles(currency);
        _DisplayCurrencies(currency);

        //write char '1' to file (if currencies are already generated, there is no need to generate them again)
        FILE *checkFile = fopen("../out/files/cryptogeneratedstatus.txt", "w");
        if(checkFile == NULL){
            printf("\nERROR: openning file isCryptoGenerated.txt\n");
            return 1;
        }
        _WriteCharToFile(checkFile, '1');
        fclose(checkFile);
        checkFile = NULL;

        isCryptoGenerated = _IsCurrencyGenerated();
        isStatsRunning = isCryptoGenerated; //set isStatsRunning  to 1

        printf("\nCurrencies generated\n");
        Sleep(1000);
    }else{
        printf("\nCurrencies already generated. \nInitializing currencies from files\n");
        //Initialize cryptocurrencies from files
        _InitializeCurrencies(currency);
        Sleep(1000);
    }
    
    system("cls");
    //stats loop
    while(isStatsRunning == 1){
        _setCursorPosition();
        

        printf("STATS\n\n");

        //display stats of every currency
        _DisplayCurrencies(currency);
        Sleep(1000);
        
        //randomly change currency values and save those values to files
        _ValueChange(currency);
        _SaveCurrenciesToFiles(currency);

        //currency values change every few secs

        //graphs
        //break;
        
    }

    
    _FreeMemory(currency);
    currency = NULL;
    printf("\n\n\n");
    //system("PAUSE");
    return 0;
}