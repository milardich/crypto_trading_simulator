#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../stats/stats_header.h"
#include "../portfolio/portfolio_header.h"
#include "../../tools/StringConcat/string_functions.h"

void _LogTransaction(int typeOfTransaction, char currencyChoice[3], float full_currency_price, int transactionComplete, float wallet_amount, float amount_of_currency){

    //write transaction to file    
    FILE * transaction_file = fopen("../out/files/transactions.txt", "a");
    if(transaction_file == NULL){
        printf("\nERROR: could not open transactions.txt file\n");
    }
    


    //output transaction
    if(transactionComplete == 1){
        printf("\nTRANSACTION COMPLETE\n");
        if(typeOfTransaction == 1){
            fprintf(transaction_file, "Transaction %d: (BUY)Exchanged %.5f of FIAT currency for %.5f %s\n", 0, full_currency_price, amount_of_currency, currencyChoice);
            printf("\nBought %.5f worth of %s (%.5f)", full_currency_price, currencyChoice, amount_of_currency);
        }else{
            fprintf(transaction_file, "Transaction %d: (SELL)Exchanged %.5f of FIAT currency for %.5f %s\n", 0, full_currency_price, amount_of_currency, currencyChoice);
            printf("\nSold %.5f worth of %s (%.5f)", full_currency_price, currencyChoice, amount_of_currency);
        }
        
    }else{
        if(typeOfTransaction == 1){
            printf("\nInsufficient amount of fiat currency in the wallet\n");
        }else if(typeOfTransaction == 2){
            printf("\nInsufficient amount of crypto currency in portfolio\n");
        }else{
            printf("\nTRANSACTION ERROR\n");
        }
        
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
    int typeOfTransaction = 1;

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
    

    /*
    printf("\n\n->>>>>>>>>FULL CURRENCY PRICE: %.5f", full_currency_price);
    printf("\n->>>>>>>>>AMOUNT OF CURRENCY BOUGHT: %.5f\n\n", amount_of_currency);
    */
    
    //subtract price from wallet
    wallet = fopen("../out/files/fiat_wallet.txt", "w");
    if(wallet == NULL){
        return;
    }

    if(full_currency_price <= wallet_amount){
        transactionComplete = 1;
        wallet_amount -= full_currency_price;
        _AddAmountToPortfolio(currency, currencyChoice, amount_of_currency);
        fprintf(wallet, "%f", wallet_amount);
    }else{
        transactionComplete = 0;
        fprintf(wallet, "%f", wallet_amount);
        //printf("\nERROR: not enough fiat money in the wallet\n");
    }
    fclose(wallet);


    //log transactions
    _LogTransaction(typeOfTransaction, currencyChoice, full_currency_price, transactionComplete, wallet_amount, amount_of_currency);


    free(currency);
    currency = NULL;
}

void _SellCurrency(char currencyChoice[3], float amount, int method){

    float wallet_amount = 0;
    float full_currency_price = 0;
    int i = 0;
    int success = 0;
    float amount_of_currency = 0;
    int transactionComplete = 0;
    int typeOfTransaction = 2;

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
        //1. Sell 32.513000 BTC
        full_currency_price = (currency + i)->startValue * amount;
        amount_of_currency = amount;
    }else{
        //2. Sell 32.513000 worth of BTC
        full_currency_price = amount;
        amount_of_currency = amount / (currency + i)->startValue;
    }
    

    
    printf("\n\n->>>>>>>>>FULL CURRENCY PRICE: %.5f", full_currency_price);
    printf("\n->>>>>>>>>AMOUNT OF CURRENCY TO BE SOLD: %.5f\n\n", amount_of_currency);
    
    
    //subtract money from fiat wallet
    //read from wallet
    wallet = fopen("../out/files/fiat_wallet.txt", "r");
    if(wallet == NULL){
        return;
    }
    fscanf(wallet, "%f", &wallet_amount);
    fclose(wallet);

    

    //get file name for chosen currency
    float oldAmount = 0;
    float newAmount = 0;

    char *filename = concat(3, "portfolio/", currencyChoice, "_amount.txt");
    if(filename == NULL){
        printf("\nFile %s doesnt exist\n", currencyChoice);
    }
    FILE *portfolio_amount_file = fopen(filename, "r");
    if(portfolio_amount_file == NULL){
        printf("\nERROR: couldnt open file %s\n", filename);
        return;
    }
    fscanf(portfolio_amount_file, "%f", &oldAmount);
    fclose(portfolio_amount_file);

    newAmount = oldAmount - amount_of_currency;

    if(amount_of_currency > 0 && amount_of_currency <= oldAmount){
        //open wallet for writing
        wallet = fopen("../out/files/fiat_wallet.txt", "w");
        if(wallet == NULL){
            return;
        }
        transactionComplete = 1;
        wallet_amount += full_currency_price;
        _SubtractAmountFromPortfolio(currency, currencyChoice, amount_of_currency);
        fprintf(wallet, "%f", wallet_amount);
        fclose(wallet);
    }else{
        printf("\nERROR: you do not own %.5f of %s\n", amount_of_currency, currencyChoice);
    }    

    


    //log transactions
    _LogTransaction(typeOfTransaction, currencyChoice, full_currency_price, transactionComplete, wallet_amount, amount_of_currency);


    free(currency);
    currency = NULL;    
}

