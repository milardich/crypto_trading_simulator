#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include "stats_header.h"


int main(){
    srand((unsigned)time(NULL));

    int isCryptoGenerated = 0;
    int numberOfCurrencies = 5;

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
    }

    //stats loop
    while(1){
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