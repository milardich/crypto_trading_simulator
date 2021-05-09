#include<stdio.h>
#include<stdlib.h>
//#include "general_tools.h"

//general write char to file function
void _WriteCharToFile(FILE *file, char c){
    fputc(c, file);
    printf("\nData written to files (%c)\n", c);
    //printf("\n\nDA FUNCTION\n\n");
}
