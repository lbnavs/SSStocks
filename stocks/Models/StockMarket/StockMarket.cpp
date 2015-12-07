#include <iostream>
#include "StockMarket.h"

using namespace std;

StockMarket::StockMarket()
{
}

StockMarket::~StockMarket()
{

}

void StockMarket::AddStock(Stock* stock)
{
   m_stocks.insert(std::pair<std::string, Stock*>(stock->GetSymbol(), stock));
}

Stock* StockMarket::FindStock(string sym)
{
   Stock* result = NULL;
   map<std::string, Stock*>::iterator it = m_stocks.find(sym);
   if (it != m_stocks.end())
   {
      result = it->second;
   }
   return result;
}

int StockMarket::DeleteStock(string sym)
{
   int result = -1;
   map<std::string, Stock*>::iterator it = m_stocks.find(sym);
   if (it != m_stocks.end())
   {
      m_stocks.erase(it);
      result = 0;
   }
   return result;
}

double StockMarket::calculateIndex()
{
   auto tradesPriceMul   = 1.0;
   int  nrStocks         = 0;
   double currStockPrice = 0.0;
   for (std::map<std::string, Stock*>::iterator it = m_stocks.begin(); it != m_stocks.end(); it++)
   {
      Stock* currStock = it->second;
      currStockPrice = currStock->calculateVolWeightedPrice();
      if (currStockPrice != 0)
      {
         tradesPriceMul *= currStockPrice;
         nrStocks++;
      }
   }
   return nrStocks == 0 ? 0 : std::pow(tradesPriceMul, 1.0 / nrStocks);
}

void StockMarket::print()
{
   float tradesPriceMul = 0.0;
   float nrTrades = 0.0;

   cout << "|-------|---------------|-------|-------|-------|" << endl;
   for (std::map<std::string, Stock*>::iterator it = m_stocks.begin(); it != m_stocks.end(); it++)
   {
      Stock* st = it->second;
      st->print();
   }
   cout << "|-------|---------------|-------|-------|-------|" << endl;

   cout << "GBCE All Share Index" << ":" << calculateIndex() << endl;
   cout << endl;
}

void StockMarket::printAllTrades()
{
   cout << "|-------|-------|-------|-------|--------------------------|" << endl;
   for (std::map<std::string, Stock*>::iterator it = m_stocks.begin(); it != m_stocks.end(); it++)
   {
      it->second->printTrades();
   }
   cout << "|-------|-------|-------|-------|--------------------------|" << endl;
   cout << endl;
}
