import yfinance
import pandas_ta as ta
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
from datetime import datetime, timedelta


def tech_anal():



    # Define the stock symbol and timeframe
    # Example for Boeing (BCO.F)
    symbol = 'BCO.F'
    end_date = datetime.today()
    start_date = end_date - timedelta(days=120)  # 4 months before today

    # Fetch stock data using yfinance
    stock = yfinance.Ticker(symbol)
    
    price_now = stock.info.get('currentPrice')
    stock.get_news



    stock_data = yfinance.download(symbol, start=start_date, end=end_date)

    print("Boeing, current price: ",price_now)

    # RSI
    stock_data.ta.rsi(append = True)

    # Calculate additional technical indicators
    stock_data.ta.sma(length=20, append=True)
    stock_data.ta.ema(length=50, append=True)
    stock_data.ta.stoch(append=True)
    stock_data.ta.adx(append=True)


    plt.figure(figsize=(14, 8))

    # price trend chart
    plt.subplot(3, 3, 1)
    plt.plot(stock_data.index, stock_data['Adj Close'], label='Adj Close', color='blue')
    plt.plot(stock_data.index, stock_data['EMA_50'], label='EMA 50', color='green')
    plt.plot(stock_data.index, stock_data['SMA_20'], label='SMA_20', color='orange')
    plt.title("Price Trend")
    plt.gca().xaxis.set_major_formatter(mdates.DateFormatter('%b%d'))  # Format date as "Jun14"
    plt.xticks(rotation=45, fontsize=8)  # Adjust font size
    plt.legend()

    plt.tight_layout()
    plt.show()

    # RSI Plot
    plt.subplot(3, 3, 4)
    plt.plot(stock_data['RSI_14'], label='RSI')
    plt.axhline(y=70, color='r', linestyle='--', label='Overbought (70)')
    plt.axhline(y=30, color='g', linestyle='--', label='Oversold (30)')
    plt.legend()
    plt.gca().xaxis.set_major_formatter(mdates.DateFormatter('%b%d'))  # Format date as "Jun14"
    plt.xticks(rotation=45, fontsize=8)  # Adjust font size
    plt.title('RSI Indicator')

    plt.tight_layout()
    plt.show()
    pass


tech_anal()

