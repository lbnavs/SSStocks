#pragma once

#include "Stock.h"

class CommonStock : public Stock
{
public:
   CommonStock(std::string symbol, double lastDividend, double fixedDividend, double parValue);
  ~CommonStock();

   //"Common"
   const char* GetType();

   //Calculations: DividendYield, P/E Ratio and Volume Weighted Stock Price
   double calculateDividendYield(double price) const;
};

