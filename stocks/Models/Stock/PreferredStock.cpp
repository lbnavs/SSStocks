#include "PreferredStock.h"

PreferredStock::PreferredStock(std::string symbol, double lastDividend, double fixedDividend, double parValue)
              :Stock(symbol, lastDividend, fixedDividend, parValue)
{
}

PreferredStock::~PreferredStock()
{

}

const char* PreferredStock::GetType()
{
   return "Prefered";
}

double PreferredStock::calculateDividendYield(double price) const
{
   double result = 0.0;
   if (price != 0.0)
   {
      result = (m_fixedDividend * m_parValue) / price;
   }
   return result;
}

