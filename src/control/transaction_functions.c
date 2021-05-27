#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../stats/stats_header.h"
#include "../portfolio/portfolio_header.h"
#include "../../tools/StringConcat/string_functions.h"

void _LogTransaction(int typeOfTransaction, char currencyChoice[3], float full_currency_price, int transactionComplete, float wallet_amount, float amount_of_currency){

    //initialize and increment number of transactions 
    int numberOfTransactions = 0;
    FILE *number_of_transactions_file = fopen("files/number_of_transactions.txt", "r");
    if(number_of_transactions_file == NULL){
        printf("\nERROR: number of transactions file\n");
        return;
    }
    fscanf(number_of_transactions_file, "%d", &numberOfTransactions);
    fclose(number_of_transactions_file);

    numberOfTransactions++;
    number_of_transactions_file = fopen("files/number_of_transactions.txt", "w");
    if(number_of_transactions_file == NULL){
        printf("\nERROR: number of transactions file\n");
        return;
    }
    fprintf(number_of_transactions_file, "%d", numberOfTransactions);
    fclose(number_of_transactions_file);

    //write transaction to file    
    FILE * transaction_file = fopen("../out/files/transactions.txt", "a");
    if(transaction_file == NULL){
        printf("\nERROR: could not open transactions.txt file\n");
    }
    


    //output transaction
    if(transactionComplete == 1){
        printf("\nTRANSACTION COMPLETE\n");
        if(typeOfTransaction == 1){
            fprintf(transaction_file, "Transaction %d: (BUY)Exchanged %.5f of FIAT currency for %.5f %s\n", numberOfTransactions, full_currency_price, amount_of_currency, currencyChoice);
            printf("\nTransaction %d: Bought %.5f worth of %s (%.5f)",numberOfTransactions, full_currency_price, currencyChoice, amount_of_currency);
        }else{
            fprintf(transaction_file, "Transaction %d: (SELL)Exchanged %.5f of FIAT currency for %.5f %s\n", numberOfTransactions, full_currency_price, amount_of_currency, currencyChoice);
            printf("\nTransaction %d: Sold %.5f worth of %s (%.5f)",numberOfTransactions, full_currency_price, currencyChoice, amount_of_currency);
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

    printf("\nNew wallet balance: %f\n", wallet_amount);
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
    

    /*
    printf("\n\n->>>>>>>>>FULL CURRENCY PRICE: %.5f", full_currency_price);
    printf("\n->>>>>>>>>AMOUNT OF CURRENCY TO BE SOLD: %.5f\n\n", amount_of_currency);
    */
    
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

void _DisplayTransactions(){
    int character = -1;
    int numberOfCharacters = 0;
    char **transaction;
    int i = 0, j = 0, numberOfTransactions = 0;

    FILE *transactions_file = fopen("files/transactions.txt", "r");
    if(transactions_file == NULL){
        printf("\nERROR: transaction file");
        return;
    }

    //count number of characters 
    while((character = fgetc(transactions_file)) != EOF){
        numberOfCharacters++;
        if(character == '\n'){
            numberOfTransactions++;
        }
    }
    //printf("\nNumber of characters in transaction file: %d", numberOfCharacters);
    //printf("\nNumber of transactions: %d", numberOfTransactions);
    fclose(transactions_file);

    //allocate char memory
    transaction = (char**)calloc(numberOfTransactions, sizeof(char*));
    if(transaction == NULL){
        printf("\nERROR: transaction memory allocation\n");
        return;
    }

    for(i = 0; i < numberOfTransactions; i++){
        transaction[i] = (char*)calloc(numberOfCharacters + 1, sizeof(char));
        if(transaction[i] == NULL){
            printf("\nERROR: transaction memory allocation\n");
            return;
        }
    }
 
    transactions_file = fopen("files/transactions.txt", "r");
    if(transactions_file == NULL){
        printf("\nERROR: transaction file");
        return;
    }
    //initialize transactions from file
    i = 0;
    for(i = 0; i < numberOfTransactions; i++){
        while((character = fgetc(transactions_file)) != EOF){
            //printf("\nDEBUG: Character: %c", character);
            if(character == '\n'){
                break;
            }else{
                transaction[i][j] = character;
                j++;    
            }
        }
        j = 0;
    }
    
        

    //printf transactions
    for(i = 0; i < numberOfTransactions; i++){
        printf("\n%s", transaction[i]);
    }
    

    //free memory
    for(i = 0; i < numberOfTransactions; i++){
        free(transaction[i]);
    }
    free(transaction);
    transaction = NULL;

    fclose(transactions_file);
}