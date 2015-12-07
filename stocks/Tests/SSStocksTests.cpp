#include <iostream>
#include <time.h>
#include <ctime>
#include "../Models/Stock/PreferredStock.h"
#include "../Models/Stock/CommonStock.h"
#include "../Models/StockMarket/StockMarket.h"
#include "SSStocksTests.h"
#define doublePrecision 0.001

using namespace std;

int SSStocksTests::testDividendYield(Stock& st, double price, double expected)
{
   return testVal(st.GetSymbol(), "Dividend Yield", st.calculateDividendYield(price), price, expected);
}

int SSStocksTests::testPERatio(Stock& st, double price, double expected)
{
   return testVal(st.GetSymbol(), "PERatio", st.calculatePERatio(price), price, expected);
}

int SSStocksTests::testVal(string& symbol, const char* calc, double val, double price, double expected)
{
   int errors = 0;
   cout << "Stock " << symbol;
   cout << " (Price: " << price << "): ";
   cout << calc << ": " << val;
   cout << " => Expected: " << expected << endl;
   string correct = "Correct";
   if (!compareDouble(val, expected))
   {
      correct = "Incorrect";
      errors++;
   }
   cout << "Result: " << correct << endl;
   cout << endl;
   return errors;
}

int SSStocksTests::testTrade(Stock& st, int expectedBuy, int expectedSell, double expectedVolWPrice)
{
   int errors = 0, countBuy = 0, countSell = 0;
   std::list<Trade>& trades = st.GetTrades();
   for (list<Trade>::iterator it = trades.begin(); it != trades.end(); it++)
   {
      Trade& curr = *it;
      switch (curr.getType())
      {
         case Trade::ttBuy : countBuy++ ; break;
         case Trade::ttSell: countSell++; break;
      }
   }

   double volWPrice = st.calculateVolWeightedPrice();

   cout << "Stock " << st.GetSymbol() << ":" << endl;
   cout << " - Buy: "              << countBuy  << " => Expected: " << expectedBuy       << endl;
   cout << " - Sell: "             << countSell << " => Expected: " << expectedSell      << endl;
   cout << " - VolWeightedPrice: " << volWPrice << " => Expected: " << expectedVolWPrice << endl;
   string correct = "Correct";
   if (countBuy != expectedBuy || countSell != expectedSell || !compareDouble(volWPrice, expectedVolWPrice))
   {
      correct = "Incorrect";
      errors++;
   }
   cout << "Result: " << correct << endl;
   cout << endl;

   return errors;
}

int SSStocksTests::testTradeTimestamps(StockMarket& sm)
{
   int errors = 0;
   CommonStock   stTest("TES", 13, 0, 250);
   sm.AddStock(&stTest);

   //Add a trade (buy and sell) before the limit timestamp
   stTest.buy(100, 100);
   stTest.sell(50, 50);

   //Add a trade (buy) after the limit timestamp
   Trade tr(100, Trade::ttBuy, 100);
   unsigned long limit = 15;
   time_t now = time(NULL);
   std::tm stTimeLimit;
   localtime_s(&stTimeLimit, &now);
   stTimeLimit.tm_min -= (limit+1);
   time_t timeLimit = mktime(&stTimeLimit);
   tr._testTimestamp(timeLimit);
   stTest.GetTrades().push_front(tr);

   //Compare results
   double volWeightedPric = stTest.calculateVolWeightedPrice(limit);
   double expected        = 83.333;

   cout << "VolWeightedPrice (time stamp):" << volWeightedPric << " => Expected: " << expected << endl;
   string correct = "Correct";
   if (!compareDouble(volWeightedPric, expected))
   {
      correct = "Incorrect";
      errors++;
   }
   cout << "Result: " << correct << endl;
   cout << endl;

   sm.DeleteStock("TES");
   return errors;
}

int SSStocksTests::testAllShareIndex(StockMarket& sm, double expectedAllShareIndex)
{
   int errors = 0;

   double allShareIndex = sm.calculateIndex();
   cout << "GBCE All Share Index:" << allShareIndex << " => Expected: " << expectedAllShareIndex << endl;
   string correct = "Correct";
   if (!compareDouble(allShareIndex, expectedAllShareIndex))
   {
      correct = "Incorrect";
      errors++;
   }
   cout << "Result: " << correct << endl;
   cout << endl;

   return errors;
}

bool SSStocksTests::compareDouble(double d1, double d2)
{

   return abs(d1 - d2) < doublePrecision;
}

int SSStocksTests::runTests()
{
   int totalErrors = 0;
   CommonStock    st1("TEA",  0, 0, 100);
   CommonStock    st2("POP",  8, 0, 100);
   CommonStock    st3("ALE", 23, 0,  60);
   PreferredStock st4("GIN",  8, 2, 100);
   CommonStock    st5("JOE", 13, 0, 250);

   StockMarket sm;
   sm.AddStock(&st1);
   sm.AddStock(&st2);
   sm.AddStock(&st3);
   sm.AddStock(&st4);
   sm.AddStock(&st5);

   cout << "--------------" << endl;
   cout << "Use Case 1: For a given stock, Given any price as input, calculate the dividend yield" << endl;
   cout << "--------------" << endl;

   totalErrors += testDividendYield(st1, 50,     0);
   totalErrors += testDividendYield(st2, 50, 0.160);
   totalErrors += testDividendYield(st3, 50, 0.460);
   totalErrors += testDividendYield(st4, 50, 0.040);
   totalErrors += testDividendYield(st5, 50, 0.260);

   totalErrors += testDividendYield(st1, 100,     0);
   totalErrors += testDividendYield(st2, 100, 0.080);
   totalErrors += testDividendYield(st3,  60, 0.383);
   totalErrors += testDividendYield(st4, 100, 0.020);
   totalErrors += testDividendYield(st5, 250, 0.052);

   totalErrors += testDividendYield(st1, 500,    0);
   totalErrors += testDividendYield(st2, 500, 0.016);
   totalErrors += testDividendYield(st3, 500, 0.046);
   totalErrors += testDividendYield(st4, 500, 0.004);
   totalErrors += testDividendYield(st5, 500, 0.026);

   cout << "-------" << endl;
   cout << "Use Case 2: For a given stock, Given any price as input, calculate the P/E Ratio" << endl;
   cout << "-------" << endl;

   totalErrors += testPERatio(st1,  50,  0    );
   totalErrors += testPERatio(st1, 100,  0    );
   totalErrors += testPERatio(st1, 500,  0    );
   totalErrors += testPERatio(st2,  50,  6.25 );
   totalErrors += testPERatio(st2, 100, 12.5  );
   totalErrors += testPERatio(st2, 500, 62.5  );
   totalErrors += testPERatio(st3,  50,  2.174);
   totalErrors += testPERatio(st3,  60,  2.609);
   totalErrors += testPERatio(st3, 500, 21.739);
   totalErrors += testPERatio(st4,  50,  6.25 );
   totalErrors += testPERatio(st4, 100, 12.5  );
   totalErrors += testPERatio(st4, 500, 62.5  );
   totalErrors += testPERatio(st5,  50,  3.846);
   totalErrors += testPERatio(st5, 250, 19.231);
   totalErrors += testPERatio(st5, 500, 38.461);

   cout << "-----------------------------------------------------------" << endl;
   cout << "Use Case 3: For a given stock, Record a trade, with timestamp, quantity of shares, buy or sell indicator and traded price" << endl;
   cout << "Use Case 4: For a given stock, Calculate Volume Weighted Stock Price based on trades in past 15 minutes" << endl;
   cout << "Use Case 5: Calculate the GBCE All Share Index using the geometric mean of prices for all stocks" << endl;
   cout << "-----------------------------------------------------------" << endl;

   totalErrors += testTrade(st1, 0, 0, 0);
   totalErrors += testAllShareIndex(sm, 0);
   st1.buy(100,  90);
   st1.buy(150, 100);
   st1.buy(200,  80);
   totalErrors += testTrade(st1, 3, 0, 88.889);
   totalErrors += testAllShareIndex(sm, 88.889);
   st1.sell(100, 110);
   st1.sell(140, 120);
   st1.sell(180, 100);
   totalErrors += testTrade(st1, 3, 3, 98.621);
   totalErrors += testTrade(st2, 0, 0, 0);
   totalErrors += testAllShareIndex(sm, 98.621);
   st2.sell(100,  90);
   st2.sell(150, 100);
   st2.sell(200,  80);
   totalErrors += testTrade(st2, 0, 3, 88.889);
   totalErrors += testAllShareIndex(sm, 93.628);
   st2.buy(100, 110);
   st2.buy(140, 120);
   st2.buy(180, 100);
   totalErrors += testTrade(st2, 3, 3, 98.621);
   totalErrors += testAllShareIndex(sm, 98.621);

   totalErrors += testTradeTimestamps(sm);

   return totalErrors;
}

