#include <iostream>
#include <time.h>
#include <ctime>
#include "Stock.h"

using namespace std;

Stock::Stock(std::string symbol, double lastDividend, double fixedDividend, double parValue)
{
   SetSymbol       (symbol       );
   SetLastDividend (lastDividend );
   SetFixedDividend(fixedDividend);
   SetParValue     (parValue     );
}

Stock::~Stock()
{

}

void Stock::buy(unsigned long qtyShares, double tradedPrice)
{
   trade(qtyShares, Trade::ttBuy, tradedPrice);
}

void Stock::sell(unsigned long qtyShares, double tradedPrice)
{
   trade(qtyShares, Trade::ttSell, tradedPrice);
}

void Stock::trade(unsigned long qtyShares, Trade::tradeType type, double tradedPrice)
{
   Trade trade(qtyShares, type, tradedPrice);
   m_trades.push_front(trade);
}

double Stock::calculatePERatio(double price) const
{
   double result = 0.0;
   double dividend = m_lastDividend;
   if (dividend != 0.0)
   {
      result = price / dividend;
   }
   return result;
}

double Stock::calculateVolWeightedPrice(unsigned long pastMin)
{
   time_t now = time(NULL);
   std::tm stTimeLimit;
   localtime_s(&stTimeLimit, &now);
   stTimeLimit.tm_min -= pastMin;
   time_t timeLimit = mktime(&stTimeLimit);

   auto sumPriceQty = 0.0;
   auto sumQty      = 0.0;
   for (list<Trade>::iterator it = m_trades.begin(); it != m_trades.end(); it++)
   {
      Trade& curr = *it;
      if (curr.getTimestamp() >= timeLimit)
      {
         sumPriceQty += (curr.getTradedPrice() * curr.getQtyShares());
         sumQty      +=  curr.getQtyShares();
      }
   }

   float result = 0.0;
   if (sumQty != 0.0)
   {
      result = static_cast<float>(sumPriceQty / sumQty);
   }
   return result;
}

std::string Stock::GetSymbol()
{
   return m_symbol;
}

double Stock::GetLastDividend()
{
   return m_lastDividend;
}

double Stock::GetFixedDividend()
{
   return m_fixedDividend;
}

double Stock::GetParValue()
{
   return m_parValue;
}

std::list<Trade>& Stock::GetTrades()
{
   return m_trades;
}

void Stock::SetSymbol(string sy)
{
   m_symbol = sy;
}

void Stock::SetLastDividend(double ld)
{
   m_lastDividend = ld;
}

void Stock::SetFixedDividend(double fd)
{
   m_fixedDividend = (fd / 100.0);
}

void Stock::SetParValue(double pv)
{
   m_parValue = pv;
}

void Stock::print()
{
   cout << "| " << GetSymbol       () << "\t| "
                << GetType         () << "\t| "
                << GetLastDividend () << "\t| "
                << GetFixedDividend() << "\t| "
                << GetParValue     () << "\t|"
        << endl;
}

void Stock::printTrades()
{
   for (list<Trade>::iterator it = m_trades.begin(); it != m_trades.end(); it++)
   {
      cout << "| " << GetSymbol() << "\t| ";
      (*it).print();
   }
}
