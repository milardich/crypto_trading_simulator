#ifndef TRANSACTION_HEADER_H
#define TRANSACTION_HEADER_H

    //Buy
    void _BuyCurrency(char[3], float, int);

    //log transactions 
    void _LogTransaction(int, char[3], float, int, float, float);

    //display transactions 
    void _DisplayTransactions();

    //Sell
    void _SellCurrency(char[3], float, int);

    //Track currency (track graph)
    //Track random every few secs
#endif