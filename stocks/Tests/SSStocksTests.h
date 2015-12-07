#pragma once

#include <list>

class Stock;
class StockMarket;

class SSStocksTests
{
public:
   //Run Tests and return the number of errors
   int runTests();

protected:
   int  testDividendYield  (Stock& st, double price, double expected);
   int  testPERatio        (Stock& st, double price, double expected);
   int  testVal            (std::string& symbol, const char* calc, double val, double price, double expected);
   int  testTrade          (Stock& st, int expectedBuy, int expectedSell, double expectedVolWPrice);
   int  testAllShareIndex  (StockMarket& sm, double expectedAllShareIndex);
   int  testTradeTimestamps(StockMarket& sm);

   bool compareDouble      (double d1, double d2);
};

