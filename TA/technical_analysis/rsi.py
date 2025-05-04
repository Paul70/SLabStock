import yfinance
from numpy import nan as npNaN
import pandas_ta as ta
from datetime import datetime, timedelta

def rsi(stock_sign = None):

    # return 0: neither oversold nor overbougth
    # return 1: oversold: rsi <= 30 (buy)
    # return 2: overbought: rsi >= 70 (sell)

    # in case of 1 or 2:
    # trigger price calculation
    # send first price and if price delta is big enough send new price mail

    if not stock_sign:
        stock_sign = 'BCO.F'
        
    print(stock_sign)

    end_date = datetime.today()
    start_date = end_date - timedelta(days=40)

    stock_data = yfinance.Ticker(stock_sign)
    stock_data = yfinance.download(stock_sign, start=start_date, end=end_date)

    stock_data.ta.rsi(append = True)
    stock_data.ta.sma(length=20, append=True)
    stock_data.ta.ema(length=50, append=True)
    stock_data.ta.stoch(append=True)
    stock_data.ta.adx(append=True)
    
    
    print(stock_data['RSI_14'])

    filtered_data = stock_data[stock_data['RSI_14'] < 30]
    if not filtered_data.empty:
        print(filtered_data)
        # write mail
        # one triggers scheduling
        return 1
    return 0

    

rsi()
