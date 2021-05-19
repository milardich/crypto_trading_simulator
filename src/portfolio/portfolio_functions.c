#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../stats/stats_header.h"
//#include "../../tools/StringConcat/string_functions.h"


//initialize portfolio
void _InitializePortfolio(CRYPTOCURRENCY *currency){
    char *filename;
    int i = 0;

    for(i = 0; i < 5; i++){
        filename = concat(3, "../out/files/portfolio/", (currency + i)->name, "_amount.txt");
        printf("\nDEBUG - fileName: %s", filename);
    }

    free(filename);
    filename = NULL;
}

//display portfolio


