#include<stdio.h>
#include<stdlib.h>
#include "../stats/stats_header.h"

void _BuyCurrency(char currencyChoice[3], float amount, int method){

    float wallet_amount = 0;

    //initialize currencies
    CRYPTOCURRENCY *currency;
    currency = _Allocate(5);
    if(currency == NULL){
        printf("\nERROR: Memory allocation failed\n");
        return;
    }

    _InitializeCurrencies(currency);


    //initialize user fiat currency amound in wallet
    FILE *wallet = fopen("../out/files/fiat_wallet.txt", "r+");
    if(wallet == NULL){
        return;
    }

    fscanf(wallet, "%f", &wallet_amount);

    printf("\nwallet amount: %f\n", wallet_amount);
    //logic (if user has enough money etc)
    

    //add amount of new currency to wallet, substract from fiat money etc

    printf("TRANSACTION COMPLETE: ");
    if(method == 1){
        printf("Bought %.2f of %s", amount, currencyChoice);
    }else{
        printf("Bought %.2f worth of %s", amount, currencyChoice);
    }
    free(currency);
    fclose(wallet);
}