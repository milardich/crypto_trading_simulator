#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../stats/stats_header.h"

void _BuyCurrency(char currencyChoice[3], float amount, int method){

    float wallet_amount = 0;
    float full_currency_price = 0;
    int i = 0;
    int success = 0;

    //initialize currencies
    CRYPTOCURRENCY *currency;
    currency = _Allocate(5);
    if(currency == NULL){
        printf("\nERROR: Memory allocation failed\n");
        return;
    }

    _InitializeCurrencies(currency);

    //select currency with matching name
    for(i = 0; i < 5; i++){
        if(strcmp((currency + i)->name, currencyChoice) == 0){
            break;
        }
    }



    //initialize user fiat currency amound in wallet
    FILE *wallet = fopen("../out/files/fiat_wallet.txt", "r");
    if(wallet == NULL){
        return;
    }

    fscanf(wallet, "%f", &wallet_amount);
    printf("\nOld wallet balance: %f\n", wallet_amount);
    fclose(wallet);

    //logic 
    if(method == 1){
        //1. Buy 32.513000 BTC
        full_currency_price = (currency + i)->startValue * amount;
    }else{
        //2. Buy 32.513000 worth of BTC
        full_currency_price = amount / (currency + i)->startValue;
    }

    
    //substract price from wallet
    wallet = fopen("../out/files/fiat_wallet.txt", "w");
    if(wallet == NULL){
        return;
    }

    if(full_currency_price <= wallet_amount){
        wallet_amount -= full_currency_price;
        fprintf(wallet, "%f", wallet_amount);
    }else{
        printf("\nERROR: not enough fiat money in the wallet\n");
    }
    fclose(wallet);

    //add amount of new currency to portfolio



    printf("TRANSACTION COMPLETE: ");
    if(method == 1){
        printf("Bought %.2f of %s", amount, currencyChoice);
    }else{
        printf("Bought %.2f worth of %s", amount, currencyChoice);
    }
    printf("\nNew wallet balance: %f", wallet_amount);

    free(currency);
    
}