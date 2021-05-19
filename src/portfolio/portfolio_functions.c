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
        _WriteCharToFile(portfolioCheckFile, '1');
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

//display portfolio
void _DisplayPortfolio(CRYPTOCURRENCY *currency, float currencyAmountInPortfolio[5]){
    int i = 0;

    for(i = 0; i < 5; i++){
        printf("$%s: %.5f\n", (currency + i)->name, currencyAmountInPortfolio[i]);
    }
}

