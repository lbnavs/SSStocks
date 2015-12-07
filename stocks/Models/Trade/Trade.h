#pragma once

#include <time.h>

class Trade
{
public:
   enum tradeType
   {
      ttBuy , //Buy  Stocks
      ttSell, //Sell Stocks
   };

   Trade(unsigned long qtyShares, tradeType type, double tradedPrice);
  ~Trade();

   //Get's
   time_t        getTimestamp  ();
   unsigned long getQtyShares  ();
   tradeType     getType       ();
   double        getTradedPrice();

   //print trade data
   void          print();

   //function for tests only
   void          _testTimestamp(time_t ts);

private:
   time_t        m_timestamp  ;
   unsigned long m_qtyShares  ;
   tradeType     m_type       ;
   double        m_tradedPrice;
};

