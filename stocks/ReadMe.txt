========================================================================
   Super Simple Stocks Application
========================================================================

Developed in C++ using on Visual Studio 2013

How to run: execute "stocks.exe" file.

Folder Description:
Main
|--stocks.cpp: This is the entry point of the application.
|--SSStocksApp.h/.cpp: Super Simple Stocks Application Object. 
|--stocks.exe: executable for testing the app.
|--stocks.sln: Visual Studio Solution
Models
|--Stock
|  |--Stock.h/.cpp: Stock Interface Object
|  |--CommonStock.h/.cpp: Common Stock Object.
|  |--PreferredStock.h/.cpp: Preferred Stock Object.
|--StocksMarket
|  |--StockMarket.h/.cpp: Stock Market Object (Created concept to gather all stocks)
|--Trade
|  |--Trade.h/.cpp: Trade Object (for a specific Stock)
Tests
|--StockTests.h/.cpp: Super Simple Stocks Tests Object. 

/////////////////////////////////////////////////////////////////////////////

Super Simple Stocks UI Options:
Please select input mode:
 (1) - Run Automatic Tests: Run predefined tests and see the results
 (2) - Manual User Input: Interact with Super Simple Stocks Application
		Select Option:
		 (1) - See All Stocks
		 (2) - See All Trades
		 (3) - Add Stock
		 (4) - Delete Stock
		 (5) - CalculateDivYield
		 (6) - CalculatePERatio
		 (7) - CalculateVolWeightedPrice
		 (8) - Trade Stock
		 (9) - Go Back
  (3) - Exit: Closes App

Tests: 
-While I was developing the application, I was testing it using the StockTests Object. 
-The tests started just for the calculation of the dividend yield and the P/E Ratio for Stocks.
-After that, Trades' tests were executed (number of buy and sell trades for a given stock) and also the calculation of the Volume Weighted Stock Price based on Trades for Stocks.
-In the end, the calculations of the GBCE All Share Index using the geometric mean of prices for all Stocks were tested using the StockMarket object.
-The "StockTests.h/.cpp" files are the final result of the tests conducted. Those tests can be executed using the application.

Interpretations/Assumptions:
-Interpretation Doubt: "dividend" in the calculation of the P/E Ratio. Options: Dividend Yield or Last Dividend? => Assumption: Using the Last Dividend for both Common and Preferred Stocks.
-Interpretation Doubt: "price" in "GBCE All Share Index using the geometric mean of prices for all stocks" Options: Volume Weighted Stock Price, Par Value, Every Trade Price? => Assumption: Using the Volume Weighted Stock Price.
-No multi-threading management.
-No overflow handling for "Geometric Mean" and "Volume Weighted Stock Price" intermediate variables.
-No invalid input validation.

