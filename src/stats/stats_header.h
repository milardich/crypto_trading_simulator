#ifndef STATS_HEADER_H
#define STATS_HEADER_H

    typedef struct cryptocurrency{
        char name[3];
        float startValue;
    }CRYPTOCURRENCY;


    //Memory allocation
    CRYPTOCURRENCY *_Allocate(int);
    void _FreeMemory(CRYPTOCURRENCY*);

    //Currency generation
    void _GenerateCurrencies(CRYPTOCURRENCY*);
    void _DisplayCurrencies(CRYPTOCURRENCY*);
    void _SaveCurrenciesToFiles(CRYPTOCURRENCY*);

    //Check if currencies are generated
    int _IsCurrencyGenerated();

    //initialize already created currencies
    void _InitializeCurrencies(CRYPTOCURRENCY*);

    //random value change
    void _ValueChange(CRYPTOCURRENCY*);

    

#endif