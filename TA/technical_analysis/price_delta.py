import yfinance
from datetime import datetime, timedelta

def price_delta(stock_sign = None):
    if not stock_sign:
        stock_sign = 'AAPL'

    stock = yfinance.Ticker(stock_sign)
    stock_price = stock.info['regularMarketPrice']

    return stock_price

price_delta()