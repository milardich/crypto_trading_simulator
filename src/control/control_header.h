#ifndef CONTROL_HEADER_H
#define CONTROL_HEADER_H

    #define BUY_COMMAND "buy"
    #define SELL_COMMAND "sell"
    #define TRACK_COMMAND "track"
    #define TRANSACTIONS_COMMAND "transactions"
    
    //show commands
    void _DisplayCommands();

    //user input
    void _CommandInput(char[20]);
    void _ProcessCommand(char[20]);


#endif