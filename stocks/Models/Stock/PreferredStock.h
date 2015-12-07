#pragma once

#include "Stock.h"

class PreferredStock : public Stock
{
public:
   PreferredStock(std::string symbol, double lastDividend, double fixedDividend, double parValue);
  ~PreferredStock();

   //"Prefered"
   const char* GetType();

   //Calculations: DividendYield, P/E Ratio and Volume Weighted Stock Price
   double calculateDividendYield(double price) const;
};

