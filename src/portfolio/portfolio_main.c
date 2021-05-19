#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include "portfolio_header.h"
//#include "../../tools/general_tools/general_tools.h"

int main(){
    system("cls");
    printf("PORTFOLIO WINDOW\n\n");
    
    //initialize portfolio
    CRYPTOCURRENCY *currency;
    currency = _Allocate(5);
    if(currency == NULL){
        printf("\nERROR: Memory allocation failed\n");
        return 1;
    }

    _InitializeCurrencies(currency);

    float currencyAmountInPortfolio[5] = {0};
    _InitializePortfolio(currency, currencyAmountInPortfolio);

    while(1){
        _setCursorPosition();

        //read amount of owned currency
        _DisplayPortfolio(currency, currencyAmountInPortfolio);
        Sleep(1000);
    }
    


    free(currency);
    currency = NULL;
    //system("PAUSE");
    return 0;
}