#include <iostream>
#include <sstream>
#include "Tests/SSStocksTests.h"
#include "Models/StockMarket/StockMarket.h"
#include "Models/Stock/CommonStock.h"
#include "Models/Stock/PreferredStock.h"
#include "SSStocksApp.h"

using namespace std;

SSStocksApp::SSStocksApp()
{
   FillDefaults();
}

void SSStocksApp::startApp()
{
   cout << "------Welcome to Super Simple Stocks------" << endl;
   cout << endl;
   string strRc;
   int rc = 0;
   while (rc != 3)
   {
      int option = 1;
      cout << "Please select input mode:" << endl;
      cout << " (" << option++ << ") - Run Automatic Tests: Run predefined tests and see the results" << endl;
      cout << " (" << option++ << ") - Manual User Input: Interact with Super Simple Stocks" << endl;
      cout << " (" << option++ << ") - Exit: Closes App"                                              << endl;
      cout << endl;
      cout << "Select Number: ";
      cin >> strRc;
      cout << endl;

      stringstream data;
      data.str(strRc);
      data >> rc;

      switch (rc)
      {
         case 1:
         {
            SelectAutomTests();
            break;
         }
         case 2:
         {
            SelectManualTests();
            break;
         }
      }
   }
}

void SSStocksApp::SeeAllStocks()
{
   m_sm.print();
}

void SSStocksApp::CalcDivYield()
{
   string symbol;
   double price = 0;
   cout << "Calculate Dividend Yield" << endl;
   cout << " - Symbol: ";
   cin >> symbol;
   cout << " - Price: ";
   cin >> price;
   Stock* st = m_sm.FindStock(symbol);
   if (st == NULL)
   {
      cout << "Stock Not Found" << endl;
      cout << endl;
      return;
   }

   double result = st->calculateDividendYield(price);
   cout << "Dividend Yield: " << result << endl;
   cout << endl;
}


void SSStocksApp::CalcPERatio()
{
   string symbol;
   double price = 0;
   cout << "Calculate PE Ratio" << endl;
   cout << " - Symbol: ";
   cin >> symbol;
   cout << " - Price: ";
   cin >> price;
   Stock* st = m_sm.FindStock(symbol);
   if (st == NULL)
   {
      cout << "Stock Not Found" << endl;
      cout << endl;
      return;
   }

   double result = st->calculatePERatio(price);
   cout << "PE Ratio: " << result << endl;
   cout << endl;
}

void SSStocksApp::CalcVolWeightedPrice()
{
   string symbol;
   cout << "Calculate VolWeightedPrice" << endl;
   cout << " - Symbol: ";
   cin >> symbol;
   Stock* st = m_sm.FindStock(symbol);
   if (st == NULL)
   {
      cout << "Stock Not Found" << endl;
      cout << endl;
      return;
   }

   double result = st->calculateVolWeightedPrice();
   cout << "VolWeightedPrice: " << result << endl;
   cout << endl;
}

void SSStocksApp::TradeStock()
{
   string symbol, buySell;
   double price = 0;
   int qty = 0;
   cout << "Trade Stock:" << endl;
   cout << " - Symbol: ";
   cin >> symbol;
   cout << " - Buy ('B') or Sell ('S'): ";
   cin >> buySell;
   cout << " - Price: ";
   cin >> price;
   cout << " - Quantity: ";
   cin >> qty;
   Stock* st = m_sm.FindStock(symbol);
   if (st == NULL)
   {
      cout << "Stock Not Found" << endl;
      cout << endl;
      return;
   }

   if (buySell.compare("B") == 0)
   {
      st->buy(qty, price);
   }
   else if (buySell.compare("S") == 0)
   {
      st->buy(qty, price);
   }
   else
   {
      cout << "Stock Not Found" << endl;
      cout << endl;
      return;
   }

   cout << "Stock Traded Successfully" << endl;
   cout << endl;
}

void SSStocksApp::AddStock()
{
   string symbol, type;
   double lastDiv = 0, fixedDiv = 0, parVal = 0;
   cout << "Adding Stock" << endl;
   cout << " - Symbol: ";
   cin >> symbol;
   cout << " - Type (C=Common;P=Prefered): ";
   cin >> type;
   cout << " - Last Dividend: ";
   cin >> lastDiv;
   cout << " - Fixed Dividend: ";
   cin >> fixedDiv;
   cout << " - Par Value: ";
   cin >> parVal;
   cout << endl;

   int rc = 0;
   
   Stock *st = NULL;
   if (type.compare("C") == 0)
   {
      st = new CommonStock(symbol, lastDiv, fixedDiv, parVal);
   }
   else if (type.compare("P") == 0)
   {
      st = new PreferredStock(symbol, lastDiv, fixedDiv, parVal);
   }
   else
   {
      cout << "Stock Type Error. 'C' for Common Stocks and 'P' for Prefered Stocks";
      return;
   }

   string confirm;
   cout << "The following stock will be added: " << endl;
   st->print();
   cout << "Confirm ('A'=Abort; Any other key to add): ";
   cin >> confirm;

   if (confirm.compare("A") != 0)
   {
      m_sm.AddStock(st);
      cout << "Stock Added Successfully" << endl;
      cout << endl;
   }
}
void SSStocksApp::DeleteStock()
{
   string userOption;
   cout << "Select Symbol:";
   cin >> userOption;

   int rc = m_sm.DeleteStock(userOption);
   if (rc != 0)
   {
      cout << "Delete Stock Error";
   }
   cout << endl;
}
void SSStocksApp::SeeAllTrades()
{
   m_sm.printAllTrades();
}

void SSStocksApp::SelectManualTests()
{
   string userOption;
   int rc = 0;
   bool userHasEnded = false;
   while (!userHasEnded)
   {
      int option = 1;
      cout << "Select Option" << ":" << endl;
      cout << " (" << option++ << ") - " << "See All Stocks"            << endl;
      cout << " (" << option++ << ") - " << "See All Trades"            << endl;
      cout << " (" << option++ << ") - " << "Add Stock"                 << endl;
      cout << " (" << option++ << ") - " << "Delete Stock"              << endl;
      cout << " (" << option++ << ") - " << "CalculateDivYield"         << endl;
      cout << " (" << option++ << ") - " << "CalculatePERatio"          << endl;
      cout << " (" << option++ << ") - " << "CalculateVolWeightedPrice" << endl;
      cout << " (" << option++ << ") - " << "Trade Stock"               << endl;
      cout << " (" << option   << ") - " << "Go Back"                   << endl;
      cout << endl;
      cout << "Select Number: ";
      cin >> userOption;
      cout << endl;

      stringstream data;
      data.str(userOption);
      data >> rc;

      switch (rc)
      {
         case 1: SeeAllStocks        (); break;
         case 2: SeeAllTrades        (); break;
         case 3: AddStock            (); break;
         case 4: DeleteStock         (); break;
         case 5: CalcDivYield        (); break;
         case 6: CalcPERatio         (); break;
         case 7: CalcVolWeightedPrice(); break;
         case 8: TradeStock          (); break;
         default: userHasEnded = true; break;
      }
   }
}

void SSStocksApp::SelectAutomTests()
{
   SSStocksTests stockTests;
   int errors = stockTests.runTests();

   cout << "Automatic Tests Results: " << endl;
   if (errors > 0)
   {
      cout << errors << " Errors." << endl;
   }
   else
   {
      cout << "No Errors." << endl;
   }
   cout << endl;
}

void SSStocksApp::FillDefaults()
{
   CommonStock*    st1 = new CommonStock  ("TEA",  0, 0, 100);
   CommonStock*    st2 = new CommonStock  ("POP",  8, 0, 100);
   CommonStock*    st3 = new CommonStock  ("ALE", 23, 0,  60);
   PreferredStock* st4 = new PreferredStock("GIN",  8, 2, 100);
   CommonStock*    st5 = new CommonStock  ("JOE", 13, 0, 250);

   m_sm.AddStock(st1);
   m_sm.AddStock(st2);
   m_sm.AddStock(st3);
   m_sm.AddStock(st4);
   m_sm.AddStock(st5);
}


