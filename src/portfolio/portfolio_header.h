#include "../stats/stats_header.h"
#ifndef PORTFOLIO_HEADER_H
#define PORTFOLIO_HEADER_H
    void _InitializePortfolio(CRYPTOCURRENCY*, float[5]);
    void _ReadCurrencyAmounts(CRYPTOCURRENCY*, float[5]);
    void _DisplayPortfolio(CRYPTOCURRENCY*, float[5]);
    void _AddAmountToPortfolio(CRYPTOCURRENCY*, char[3], float);
    void _ShowFiatWalletAmount();
    void _SubtractAmountFromPortfolio(CRYPTOCURRENCY*, char[3], float);

#endif