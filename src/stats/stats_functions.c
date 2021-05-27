#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include "stats_header.h"
#include "../../tools/StringConcat/string_functions.h"


void test_Stats(){
    printf("\n----\nSTATS FUNCTION TEST\n----\n");
}


//=====================================//
// Check if cryptos are already generated
//=====================================//

int _IsCurrencyGenerated(){
    
    FILE * checkFile = fopen("../out/files/cryptogeneratedstatus.txt", "r");
    if(checkFile == NULL){
        printf("\nERROR: openning file isCryptoGenerated.txt\n");
        return 1;
    }
    
    int c = 0;
    c = fgetc(checkFile);
    c = c - 48;
    fclose(checkFile);
    return c;
}










//=====================================//
// Memory allocation for currencies
//=====================================//

CRYPTOCURRENCY *_Allocate(int numberOfCurrencies){
    CRYPTOCURRENCY *currency;
    currency = (CRYPTOCURRENCY*)calloc(numberOfCurrencies, sizeof(CRYPTOCURRENCY));
    if(currency == NULL){
        return NULL;
    }
}

void _FreeMemory(CRYPTOCURRENCY *currency){
    free(currency);
    currency = NULL;
}





//=====================================//
// Currency generation
//=====================================//

void _GenerateCurrencies(CRYPTOCURRENCY *currency){
    //srand((unsigned)time(NULL));
    float lo = 0.1;
    float hi = 199.9;

    int i = 0, j = 0, k = 0;
    int currencyNameExists = 0;

    for(i = 0; i < 5; i++){
        
        //generate different names
        do{
            for(j = 0; j < 3; j++){
                //string of random 3 letters
                currency[i].name[j] = 65 + (float)rand() / RAND_MAX * (90 - 65);
            }

            if(i == 1){
                if((currency + i)->name == (currency + (i - 1))->name){
                    currencyNameExists = 1;
                }else{
                    currencyNameExists = 0;
                }
            }
        }while(currencyNameExists != 0);


        //random value of each currency
        (currency + i)->startValue = lo + (float)rand() / RAND_MAX * (hi - lo);
    }
}

void _DisplayCurrencies(CRYPTOCURRENCY *currency){
    int i = 0, j = 0;

    for(i = 0; i < 5; i++){
        printf("\n $%s: ", (currency + i)->name);
        printf("%.2f", (currency + i)->startValue);
    }
}

void _SaveCurrenciesToFiles(CRYPTOCURRENCY *currency){
    int i = 0;
    char *fileName;

    FILE *all_currencies_file;
    all_currencies_file = fopen("../out/files/currencies/all_currencies_file.txt", "w");
    if(all_currencies_file == NULL){
        printf("\nERROR: all_currencies_file could not open");
        return;
    }

    for(i = 0; i < 5; i++){
        fileName = concat(3, "../out/files/currencies/", (currency + i)->name, "_value.txt");
        //printf("\nDEBUG - fileName: %s", fileName);
        
        FILE * file;
        file = fopen(fileName, "w");
        if(file == NULL){
            printf("\nERROR: openning file\n");
            return;
        }
        fprintf(file, "%.2f", (currency + i)->startValue);
        //fprintf(file, "\n%s", (currency + i)->name);
        fclose(file);


        //write all curencies to all_currencies_file, so all currencies 
        //can be stored in a variable if they are already created
        fprintf(all_currencies_file, "%s\n", (currency + i)->name);
    }

    fclose(all_currencies_file);
    free(fileName); //needs to be freed because of concat() function
    fileName = NULL;
}




//=====================================//
// Initialization of already created currency
//=====================================//

void _InitializeCurrencies(CRYPTOCURRENCY *currency){

    int i = 0, j = 0;

    char *currencyFileName;

    FILE *allCurrenciesFile;
    allCurrenciesFile = fopen("../out/files/currencies/all_currencies_file.txt", "r");
    if(allCurrenciesFile == NULL){
        printf("\nERROR: all_currencies_file could not open");
        return;
    }

    for(i = 0; i < 5; i++){

        //read name of every currency (3 letters)
        int character = -1;
        while((character = fgetc(allCurrenciesFile)) != EOF){
            if(character == '\n'){
                break;
            }else{
                currency[i].name[j] = character;
                j++;    
            }
        }
        j = 0;



        //read value of every currency
        currencyFileName = concat(3, "../out/files/currencies/", (currency + i)->name, "_value.txt");
        //printf("\nDEBUG: filename: %s\n", currencyFileName);
        FILE * cryptoValueFile = fopen(currencyFileName, "r");
        if(cryptoValueFile == NULL){
            printf("ERROR: file %s could not be opened", currencyFileName);
            return;
        }
        //function for reading from file
        fscanf(cryptoValueFile, "%f", &(currency + i)->startValue);

        fclose(cryptoValueFile);
        free(currencyFileName);
    }
    
    //currencyFileName = NULL;
    fclose(allCurrenciesFile);
}





//=====================================//
// Random currency value change
//=====================================//
/*
TODO: value increment and decrement
 -increment/decrement gets random value
 -currency value + or - that increment/decrement
*/
void _ValueChange(CRYPTOCURRENCY *currency){
    int i = 0;

    float increment = 0;
    float decrement = 0;
    float change = 0;

    int randBool; 


    for(i = 0; i < 5; i++){

        randBool = rand() % 2;
        if(randBool == 1){
            increment = 1 + (float)rand() / RAND_MAX * (20 - 1);
            change = increment;
        }else{
            decrement = 1 + (float)rand() / RAND_MAX * (20 - 1);
            change = -decrement;
        }

        //(currency + i)->startValue = 1 + (float)rand() / RAND_MAX * (1000 - 300);
        (currency + i)->startValue += change;
        if((currency + i)->startValue <= 0){
            (currency + i)->startValue = 0.0;
        }
    }
    
}





//=====================================//
// Graphs
//=====================================//

void _DrawGraph(CRYPTOCURRENCY *currency){
    int i = 0;
    int j = 0;
    float maxValue = 0;
    float minValue = 0; 
    char emptySpot = '-';
    int column[10];

    printf("Tracking: $CRYPTO\n\n");

    for(i = 0; i < 11; i++){

        printf("\n");
        
        for(j = 0; j < 19; j++){
            if(j == 0){
                printf(" %2d ", 10 - i);
            }
            else if(i == 10){
                //printf(" %2d ", j);
                printf("____");
            }
            else{
                printf(" %2c ", emptySpot);
            }
        }
    }
}