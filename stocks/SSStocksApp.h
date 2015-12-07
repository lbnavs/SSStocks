#pragma once

#include "Models/StockMarket/StockMarket.h"

class SSStocksApp
{
public:
   SSStocksApp();

   //Start Super Simple Stocks App
   void startApp();

protected:
   //StockMarket object
   StockMarket m_sm;

   //App Main Options
   void SelectManualTests();
   void SelectAutomTests();

   //Manual Test Options
   void SeeAllStocks        ();
   void SeeAllTrades        ();
   void AddStock            ();
   void DeleteStock         ();
   void CalcDivYield        ();
   void CalcPERatio         ();
   void CalcVolWeightedPrice();
   void TradeStock          ();

   //Fill App Default Data
   void FillDefaults        ();
};

