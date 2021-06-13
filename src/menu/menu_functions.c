#include<stdio.h>
#include<windows.h>
#include<dirent.h>

int _ResetGame(){
    //reset fiat wallet amount
    FILE * fiat_wallet_file = fopen("files/fiat_wallet.txt", "w");
    if(fiat_wallet_file == NULL){
        printf("\nError: fiat_wallet.txt\n");
        return 1;
    }
    fprintf(fiat_wallet_file, "%s", "1000");
    printf("\nFiat wallet amount set to 1000");
    fclose(fiat_wallet_file);
    printf("\n");

    //reset crypto generated stats (to enable new currency generation)
    FILE * cryptogeneratedstatus_file = fopen("files/cryptogeneratedstatus.txt", "w");
    if(cryptogeneratedstatus_file == NULL){
        printf("\nError: cryptogeneratedstatus.txt\n");
        return 1;
    }
    fprintf(cryptogeneratedstatus_file, "%d", 0);
    printf("\nCrypto generated status set to 0");
    fclose(cryptogeneratedstatus_file);
    printf("\n");

    //delete currency values
    DIR *currencies_folder = opendir("files/currencies");
    if(currencies_folder == NULL){
        printf("\nError: currencies folder\n");
        return 1;
    }
    struct dirent *next_file;
    char filepath[256];
    while ( (next_file = readdir(currencies_folder)) != NULL )
    {
        // build the path for each file in the folder
        sprintf(filepath, "%s/%s", "files/currencies", next_file->d_name);
        if(strcmp(filepath, "files/currencies/all_currencies_file.txt") == 0){
            continue;
        }else{
            remove(filepath);
            printf("\nCurrency file: %s", filepath);
        }
        
    }
    closedir(currencies_folder);
    printf("\n");

    //reset portfolio
    DIR *portfolio_folder = opendir("portfolio");
    if(portfolio_folder == NULL){
        printf("\nError: currencies folder\n");
        return 1;
    }
    while ( (next_file = readdir(portfolio_folder)) != NULL )
    {
        // build the path for each file in the folder
        sprintf(filepath, "%s/%s", "portfolio", next_file->d_name);
        if(strcmp(filepath, "portfolio/is_portfolio_generated.txt") == 0){
            continue;
        }else{
            remove(filepath);
            printf("\nPortfolio file: %s", filepath);
        }
    }
    closedir(portfolio_folder);
    FILE * is_portfolio_generated_file = fopen("portfolio/is_portfolio_generated.txt", "w");
    if(is_portfolio_generated_file == NULL){
        printf("\nError: portfolio generated file\n");
        return 1;
    }
    fprintf(is_portfolio_generated_file, "%c", '0');
    printf("\nPortfolio generated status: %d", 0);
    fclose(is_portfolio_generated_file);
    printf("\n");
    return 1;
}