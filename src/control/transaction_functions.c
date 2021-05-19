#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../stats/stats_header.h"

void _LogTransaction(char currencyChoice[3], float full_currency_price, int transactionComplete, float wallet_amount, float amount_of_currency){
    /*
    if(method == 1){
        printf("Bought %.2f of %s (%.5f)", amount, currencyChoice, full_currency_price);
    }else{
        printf("Bought %.2f worth of %s (%.5f)", amount, currencyChoice, amount_of_currency);
    }
    */

    //write transaction to file    
    FILE * transaction_file = fopen("../out/files/transactions.txt", "a");
    if(transaction_file == NULL){
        printf("\nERROR: could not open transactions.txt file\n");
    }
    fprintf(transaction_file, "Transaction %d: Exchanged %.5f of FIAT currency for %.5f %s\n", 0, full_currency_price, amount_of_currency, currencyChoice);


    //output transaction
    if(transactionComplete == 1){
        printf("\nTRANSACTION COMPLETE\n");
        printf("\nBought %.5f worth of %s (%.5f)", full_currency_price, currencyChoice, amount_of_currency);
    }else{
        printf("\nInsufficient amount of fiat currency in the wallet\n");
    }

    printf("\n\nNew wallet balance: %f\n", wallet_amount);
    fclose(transaction_file);
}

void _BuyCurrency(char currencyChoice[3], float amount, int method){

    float wallet_amount = 0;
    float full_currency_price = 0;
    int i = 0;
    int success = 0;
    float amount_of_currency = 0;
    int transactionComplete = 0;

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



    //initialize user fiat currency amount from da wallet
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
        amount_of_currency = amount;
    }else{
        //2. Buy 32.513000 worth of BTC
        full_currency_price = amount;
        amount_of_currency = amount / (currency + i)->startValue;
    }
    

    printf("\n\n->>>>>>>>>FULL CURRENCY PRICE: %.5f", full_currency_price);
    printf("\n->>>>>>>>>AMOUNT OF CURRENCY BOUGHT: %.5f\n\n", amount_of_currency);

    
    //subtract price from wallet
    wallet = fopen("../out/files/fiat_wallet.txt", "w");
    if(wallet == NULL){
        return;
    }

    if(full_currency_price <= wallet_amount){
        transactionComplete = 1;
        wallet_amount -= full_currency_price;
        fprintf(wallet, "%f", wallet_amount);
    }else{
        transactionComplete = 0;
        printf("\nERROR: not enough fiat money in the wallet\n");
    }
    fclose(wallet);


    //log transactions
    _LogTransaction(currencyChoice, full_currency_price, transactionComplete, wallet_amount, amount_of_currency);

    //add amount of new currency to portfolio
    
    


    //printf("TRANSACTION COMPLETE: ");
    /*
    if(method == 1){
        printf("Bought %.2f of %s (%.5f)", amount, currencyChoice, full_currency_price);
    }else{
        printf("Bought %.2f worth of %s (%.5f)", amount, currencyChoice, amount_of_currency);
    }
    */
    //printf("\nBought %.5f worth of %s", full_currency_price, currencyChoice);
    //printf("\nNew wallet balance: %f\n", wallet_amount);

    free(currency);
    currency = NULL;
}


