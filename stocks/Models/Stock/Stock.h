#pragma once

#include "../Trade/Trade.h"
#include <string>
#include <list>

class Stock
{
public:
   Stock(std::string symbol, double lastDividend, double fixedDividend, double parValue);
  ~Stock();

  //Record a trade, with timestamp, quantity of shares, buy or sell indicator and traded price
  void buy (unsigned long qtyShares, double tradedPrice);
  void sell(unsigned long qtyShares, double tradedPrice);

  //Calculations: DividendYield, P/E Ratio and Volume Weighted Stock Price
  virtual double calculateDividendYield   (double         price     ) const = 0;
          double calculatePERatio         (double         price     ) const;
          double calculateVolWeightedPrice(unsigned long pastMin = 15);

   //Get's
           std::string       GetSymbol       ();
   virtual const char*       GetType         () = 0;
           double            GetLastDividend ();
           double            GetFixedDividend();
           double            GetParValue     ();
           std::list<Trade>& GetTrades       ();

   //Set's
   void SetSymbol       (std::string sy);
   void SetLastDividend (double       ld);
   void SetFixedDividend(double       fd);
   void SetParValue     (double       pv);

   //
   void print();
   void printTrades();

protected:
   std::string      m_symbol       ;
   double           m_lastDividend ;
   double           m_fixedDividend;
   double           m_parValue     ;
   std::list<Trade> m_trades       ;

   void trade(unsigned long qtyShares, Trade::tradeType type, double tradedPrice);
};

