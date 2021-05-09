#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include "../../tools/StringConcat/string_functions.h"
#include "stats_header.h"


void test_Stats(){
    printf("\n----\nSTATS FUNCTION TEST\n----\n");
}


//=====================================//
// Check if cryptos are already generated
//=====================================//

int _CheckCurrenciesGenerated(FILE *checkFile){
    int c = 0;
    c = fgetc(checkFile);
    c = c - 48;
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
    printf("\nCurrencies generated.\n");
    for(i = 0; i < 5; i++){
        printf("\n$%s: ", (currency + i)->name);
        printf("%.2f", (currency + i)->startValue);
    }
}

void _SaveCurrenciesToFiles(CRYPTOCURRENCY *currency){
    int i = 0;
    char *fileName;

    /*
    FILE * file;
    file = fopen("../out/files/currencies/testfile.txt", "w");
    if(file == NULL){
        printf("\n\nError openning a file\n\n");
    }
    fclose(file);
    */

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
        fprintf(file, "\n%s", (currency + i)->name);
        fclose(file);
    }
    free(fileName);
    fileName = NULL;
}