#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include "portfolio_header.h"
//#include "../stats/stats_header.h"

int main(){
    printf("PORTFOLIO WINDOW\n\n");
    
    //initialize portfolio
    CRYPTOCURRENCY *currency;
    currency = _Allocate(5);
    if(currency == NULL){
        printf("\nERROR: Memory allocation failed\n");
        return 1;
    }

    _InitializeCurrencies(currency);
    _InitializePortfolio(currency);

    //read amount of owned currency



    free(currency);
    currency = NULL;
    //system("PAUSE");
    return 0;
}