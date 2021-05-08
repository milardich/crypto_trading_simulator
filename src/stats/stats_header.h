#ifndef STATS_HEADER_H
#define STATS_HEADER_H

    typedef struct cryptocurrency{
        char name[3];
        float startValue;
    }CRYPTOCURRENCY;

    //void test_Stats();

    //Memory allocation
    CRYPTOCURRENCY *_Allocate(int);
    void _FreeMemory(CRYPTOCURRENCY*);

    //Currency generation
    void _GenerateCurrencies(CRYPTOCURRENCY*);
    void _DisplayCurrencies(CRYPTOCURRENCY*);
    void _SaveCurrenciesToFiles(CRYPTOCURRENCY*);


#endif