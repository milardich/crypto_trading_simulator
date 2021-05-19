#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../stats/stats_header.h"
#include "../../tools/StringConcat/string_functions.h"
#include "../../tools/general_tools/general_tools.h"

int _IsPortfolioGenerated(FILE *portfolioCheckFile){
    int c = 0;
    c = fgetc(portfolioCheckFile);
    c = c - 48;
    return c;
}

//initialize portfolio
void _InitializePortfolio(CRYPTOCURRENCY *currency, float currencyAmountInPortfolio[5]){
    char *filename;
    int i = 0;
    int isPortfolioGenerated;

    //check if portfolio is already generated
    FILE *portfolioCheckFile = fopen("portfolio/is_portfolio_generated.txt", "r");
    if(portfolioCheckFile == NULL){
        printf("\nERROR: checkfile could not open\n");
        return;
    }
    isPortfolioGenerated = _IsPortfolioGenerated(portfolioCheckFile);
    fclose(portfolioCheckFile);

    printf("\n>>>>>>>>>>>>openning checkfile\n");

    if(isPortfolioGenerated == 0){
        //generate portfoilo
        for(i = 0; i < 5; i++){
            filename = concat(3, "portfolio/", (currency + i)->name, "_amount.txt");
            printf("\nDEBUG - fileName: %s", filename);

            FILE *file;
            file = fopen(filename, "w");
            if(file == NULL){
                printf("\nERROR: openning file\n");
                //return;
            }else{
                fprintf(file, "%.5f", 0.0);
            }
            fclose(file);
        }

        //write 1 to isportfoliogenerated.txt
        FILE *portfolioCheckFile = fopen("portfolio/is_portfolio_generated.txt", "w");
        if(portfolioCheckFile == NULL){
            printf("\nERROR: checkfile could not open\n");
            return;
        }
        //_WriteCharToFile(portfolioCheckFile, '1');
        fclose(portfolioCheckFile);
        
        
        printf("\n>>>>>>>>>>>>generated portfolio\n");


    }else{
        //initialize portfolio
        for(i = 0; i < 5; i++){
            filename = concat(3, "portfolio/", (currency + i)->name, "_amount.txt");
            printf("\nDEBUG - fileName: %s", filename);

            FILE *file;
            file = fopen(filename, "r");
            if(file == NULL){
                printf("\nERROR: openning file\n");
                //return;
            }else{
                fscanf(file, "%f", &currencyAmountInPortfolio[i]);
            }
            fclose(file);
        }
        printf("\n>>>>>>>>>>>>initialized portfolio\n");
    }
    
    

    free(filename);
    filename = NULL;
}

//read from currency_amount.txt files (refreshes every second in main)
void _ReadCurrencyAmounts(CRYPTOCURRENCY *currency, float currencyAmountInPortfolio[5]){
    char *filename;
    int i = 0;

    for(i = 0; i < 5; i++){
        filename = concat(3, "portfolio/", (currency + i)->name, "_amount.txt");
        //printf("\nDEBUG - fileName: %s", filename);

        FILE *file;
        file = fopen(filename, "r");
        if(file == NULL){
            printf("\nERROR: openning file\n");
            //return;
        }else{
            fscanf(file, "%f", &currencyAmountInPortfolio[i]);
        }
        fclose(file);
    }
}


//display portfolio
void _DisplayPortfolio(CRYPTOCURRENCY *currency, float currencyAmountInPortfolio[5]){
    int i = 0;
    char *currencyFileName;

    //read current currency values
    for(i = 0; i < 5; i++){
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

    for(i = 0; i < 5; i++){
        printf("$%s: %.5f (%.5f in FIAT)\n", (currency + i)->name, currencyAmountInPortfolio[i], currencyAmountInPortfolio[i] * (currency + i)->startValue);
    }
}

void _AddAmountToPortfolio(CRYPTOCURRENCY *currency, char currencyChoice[3], float amount_of_currency){
    //select currency with matching name
    int i = 0;
    for(i = 0; i < 5; i++){
        if(strcmp((currency + i)->name, currencyChoice) == 0){
            break;
        }
    }

    char *filename;
    float oldAmount = 0;
    float newAmount = 0;

    //get file name for chosen currency
    filename = concat(3, "portfolio/", currencyChoice, "_amount.txt");
    if(filename == NULL){
        printf("\nFile %s doesnt exist\n", currencyChoice);
    }
    //printf("\nDEBUG:: filename: %s\n", filename);
    
    //open file and add old and bought value together
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("\nERROR: could not open file\n");
        return;
    }

    fscanf(file, "%f", &oldAmount);
    fclose(file);

    newAmount = oldAmount + amount_of_currency;

    file = fopen(filename, "w");
    if(file == NULL){
        printf("\nERROR: could not open file\n");
        return;
    }
    fprintf(file, "%f", newAmount);
    fclose(file);
    free(filename);
}