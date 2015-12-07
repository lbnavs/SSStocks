#include "CommonStock.h"

CommonStock::CommonStock(std::string symbol, double lastDividend, double fixedDividend, double parValue)
            :Stock(symbol, lastDividend, fixedDividend, parValue)
{
}

CommonStock::~CommonStock()
{

}

const char* CommonStock::GetType()
{
   return "Common";
}

double CommonStock::calculateDividendYield(double price) const
{
   double result = 0.0;
   if (price != 0.0)
   {
      result = m_lastDividend / price;
   }
   return result;
}

