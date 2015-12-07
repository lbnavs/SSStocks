#pragma once

#include <map>
#include "../Stock/Stock.h"

class StockMarket
{
public:
   StockMarket();
   ~StockMarket();

   //Add / Delete a new Stock to the Stck Market
   void   AddStock(Stock* stock);
   int    DeleteStock(std::string sym);

   Stock* FindStock(std::string sym);

   //Calculations: GBCE All Share Index
   double calculateIndex();

   //print stock market data
   void print();
   void printAllTrades();

private:
   std::map<std::string, Stock*> m_stocks;
};

