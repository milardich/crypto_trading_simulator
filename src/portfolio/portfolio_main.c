#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include "portfolio_header.h"
#include "../../tools/general_tools/general_tools.h"

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
    Sleep(2000);
    system("cls");

    while(1){
        _setCursorPosition();
        printf("  ____   ___  ____ _____ _____ ___  _     ___ ___  \n");
        printf(" |  _ \\ / _ \\|  _ \\_   _|  ___/ _ \\| |   |_ _/ _ \\ \n");
        printf(" | |_) | | | | |_) || | | |_ | | | | |    | | | | |\n");
        printf(" |  __/| |_| |  _ < | | |  _|| |_| | |___ | | |_| |\n");
        printf(" |_|    \\___/|_| \\_\\|_| |_|   \\___/|_____|___\\___/ \n\n");
        printf(" --------------------------------------------------\n");


        //show amount of FIAT currency from wallet
        _ShowFiatWalletAmount();

        //read amount of owned currency
        _ReadCurrencyAmounts(currency, currencyAmountInPortfolio);

        //display currencies
        _DisplayPortfolio(currency, currencyAmountInPortfolio);
        Sleep(1000);
    }
    


    free(currency);
    currency = NULL;
    //system("PAUSE");
    return 0;
}