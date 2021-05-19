#include<stdio.h>
#include<windows.h>
//#include<dirent.h>

int main(){
    system("gcc ../../src/menu/*.c -o ../../out/menu");
    printf("menu built\n");

    system("gcc ../../src/control/*.c ../../src/stats/stats_functions.c ../StringConcat/string_concat.c ../general_tools/general_tools.c ../../src/portfolio/portfolio_functions.c -o ../../out/control");
    printf("control built\n");

    system("gcc ../../src/portfolio/*.c ../../src/stats/stats_functions.c ../StringConcat/string_concat.c ../general_tools/general_tools.c -o ../../out/portfolio");
    printf("portfolio built\n");

    system("gcc ../../src/stats/*.c ../StringConcat/string_concat.c ../general_tools/general_tools.c -o ../../out/stats");
    printf("stats built\n");

    return 0;
}