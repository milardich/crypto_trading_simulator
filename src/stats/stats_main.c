#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

#include "../../tools/general_tools/general_tools.h"
#include "stats_header.h"


int main(){
    srand((unsigned)time(NULL));

    int isCryptoGenerated = 0;
    int numberOfCurrencies = 5;

    //check if crypto is alreadys generated
    FILE * checkFile = fopen("../out/files/cryptogeneratedstatus.txt", "r");
    if(checkFile == NULL){
        printf("\nERROR: openning file isCryptoGenerated.txt\n");
        return 1;
    }
    isCryptoGenerated = _CheckCurrenciesGenerated(checkFile);
    //printf("\nisCryptoGenerated: %d\n", isCryptoGenerated);
    fclose(checkFile);


    //memory allocation
    CRYPTOCURRENCY *currency;
    currency = _Allocate(numberOfCurrencies);
    if(currency == NULL){
        printf("\nERROR: Memory allocation failed\n");
        return 1;
    }
    

    printf("\nSTATS WINDOW\n\n");


    if(isCryptoGenerated == 0){
        //Generate number of different cryptocurrencies and store them and their properties in da files
        _GenerateCurrencies(currency);
        _SaveCurrenciesToFiles(currency);
        _DisplayCurrencies(currency);

        //write char '1' to file (if currencies are already generated, there is no need to generate them again)
        checkFile = fopen("../out/files/cryptogeneratedstatus.txt", "w");
        if(checkFile == NULL){
            printf("\nERROR: openning file isCryptoGenerated.txt\n");
            return 1;
        }

        _WriteCharToFile(checkFile, '1');
        fclose(checkFile);
        checkFile = NULL;
        
    }else{
        printf("\nAlready generated\n");
    }
    
    
    //stats loop
    while(1){
        //printf("\nisCryptoGenerated: %c\n", isCryptoGenerated);
        //display stats of every currency
        //change values every few secs
        //graphs
        //printf("\nloop");
        break;
    }

    
    _FreeMemory(currency);
    currency = NULL;
    //system("PAUSE");
    return 0;
}