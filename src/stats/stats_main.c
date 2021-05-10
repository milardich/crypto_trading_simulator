#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

#include "../../tools/general_tools/general_tools.h"
#include "stats_header.h"


int main(){
    system("cls");
    printf("STATS WINDOW\n\n");

    srand((unsigned)time(NULL));

    int isCryptoGenerated = 0;
    int numberOfCurrencies = 5;


    //read from txt file and store that value to isCryptoGenerated
    isCryptoGenerated = _IsCurrencyGenerated();


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
        
    }else{
        printf("\nAlready generated\n");
    }
    
    
    //stats loop
    while(1){
        _InitializeCurrencies(currency);
        _DisplayCurrencies(currency);
        //Initialize cryptocurrencies from files
        //display stats of every currency
        //currency values change every few secs
        //graphs
        break;
    }

    
    _FreeMemory(currency);
    currency = NULL;
    //system("PAUSE");
    return 0;
}