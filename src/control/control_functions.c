#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "control_header.h"
#include "transaction_header.h"

void _DisplayCommands(){
    printf("   ____ ___  __  __ __  __    _    _   _ ____  ____  \n");
    printf("  / ___/ _ \\|  \\/  |  \\/  |  / \\  | \\ | |  _ \\/ ___| \n");
    printf(" | |  | | | | |\\/| | |\\/| | / _ \\ |  \\| | | | \\___ \\ \n");
    printf(" | |__| |_| | |  | | |  | |/ ___ \\| |\\  | |_| |___) |\n");
    printf("  \\____\\___/|_|  |_|_|  |_/_/   \\_\\_| \\_|____/|____/ \n");
    printf("\n");
    printf(" ----------------\n");
    printf(" -> buy\n");
    printf(" -> sell\n");
    printf(" -> transactions\n");
    printf(" -> track\n");
    printf(" ----------------\n");
}





//============================
//  commands
//============================

//track command
void _TrackCurrency(char currencyChoice[3]){
    FILE * track_file = fopen("files/track_file.txt", "w");
    if(track_file == NULL){
        printf("\nERROR: %s\n", track_file);
        return;
    }
    fprintf(track_file, "%s", currencyChoice);
    printf("Tracking: %s", currencyChoice);
    fclose(track_file);
}

int _IsCommandValid(char inputCommand[20]){
    
    if(
        strcmp(inputCommand, BUY_COMMAND) == 0 ||
        strcmp(inputCommand, SELL_COMMAND) == 0 ||
        strcmp(inputCommand, TRACK_COMMAND) == 0 ||
        strcmp(inputCommand, TRANSACTIONS_COMMAND) == 0
    ){

        //printf("\nvalid commands\n");
        return 1;
    }else{
        printf("\nERROR: invalid command\n");
        return 0;
    }
}

void _CommandInput(char input[20]){
    do{
        printf(":> ");
        scanf("%s", input);
    }while(_IsCommandValid(input) != 1);
}

void _ProcessCommand(char command[20]){
    int currencyExists = 1;

    char currencyChoice[3];
    float amount;

    int method = 0;

    //buy
    if(strcmp(command, BUY_COMMAND) == 0){
        printf("\n Choose a currency you want to buy (currency->amount->method)\n");
        
        //keep entering again if it doesnt exist
        do{
            printf(":> currency: ");
            scanf("%s", currencyChoice);
            printf(":> amount: ");
            scanf("%f", &amount);
            //currencyExists = _CurrencyExists(currencyChoice);
        }while(currencyExists == 1);
        
        //purchase method
        printf("\n 1. Buy %f %s\n", amount, currencyChoice);
        printf(" 2. Buy %f worth of %s\n", amount, currencyChoice);
        printf(" 3. Buy MAX amount of %s", currencyChoice);
        do{
            printf("\n:> method: ");
            scanf("%d", &method);
        }while(method != 1 && method != 2);

        //buy the currency
        _BuyCurrency(currencyChoice, amount, method);

    }else if(strcmp(command, SELL_COMMAND) == 0){
        printf("\n Choose a currency you want to sell (currency->amount->method)\n");

        //keep entering again if it doesnt exist
        do{
            printf(":> currency: ");
            scanf("%s", currencyChoice);
            printf(":> amount: ");
            scanf("%f", &amount);
            //currencyExists = _CurrencyExists(currencyChoice);
        }while(currencyExists == 1);
        
        //sell method
        printf("\n 1. Sell %f %s\n", amount, currencyChoice);
        printf(" 2. Sell %f worth of %s\n", amount, currencyChoice);
        printf(" 3. Sell all %s\n", currencyChoice);
        do{
            printf("\n:> method: ");
            scanf("%d", &method);
        }while(method != 1 && method != 2 && method != 3);

        //sell the currency
        _SellCurrency(currencyChoice, amount, method);

    }else if(strcmp(command, TRACK_COMMAND) == 0){
        printf("\n Choose a currency you want to track\n");

        //keep entering again if it doesnt exist
        do{
            printf(":> currency: ");
            scanf("%s", currencyChoice);
            //currencyExists = _CurrencyExists(currencyChoice);
        }while(currencyExists == 1);
        _TrackCurrency(currencyChoice);

    }else if(strcmp(command, TRANSACTIONS_COMMAND) == 0){
        //printf("\ntransactions\n");
        _DisplayTransactions();

    }
    else{
        printf("\nERROR: Unknown command\n");
    }
}

