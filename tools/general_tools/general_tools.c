#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
//#include "general_tools.h"

//general write char to file function
void _WriteCharToFile(FILE *file, char c){
    fputc(c, file);
    printf("\nData written to files (%c)\n", c);
    //printf("\n\nDA FUNCTION\n\n");
}

//position cmd cursor (used for refreshing console)
BOOL _setCursorPosition(){
    HANDLE hStdout;
    COORD destCoord;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    destCoord.X = 0;
    destCoord.Y = 0;

    return SetConsoleCursorPosition(hStdout, destCoord);
}