#include <iostream>
#include <string>
#include "Trade.h"

#define dateStrSize 80
using namespace std;

Trade::Trade(unsigned long qtyShares, tradeType type, double tradedPrice)
{
   m_timestamp   = time(0)    ;
   m_qtyShares   = qtyShares  ;
   m_type        = type       ;
   m_tradedPrice = tradedPrice;
}

Trade::~Trade()
{

}

time_t Trade::getTimestamp()
{
   return m_timestamp;
}

unsigned long Trade::getQtyShares()
{
   return m_qtyShares;
}

Trade::tradeType Trade::getType()
{
   return m_type;
}

double Trade::getTradedPrice()
{
   return m_tradedPrice;
}

void Trade::print()
{
   time_t t = getTimestamp();
   char str[dateStrSize];
   ctime_s(str, dateStrSize, &t);
   cout << getQtyShares  () << "\t| "
        << getType       () << "\t| "
        << getTradedPrice() << "\t| "
        << str;
}

void Trade::_testTimestamp(time_t ts)
{
   m_timestamp = ts;
}


