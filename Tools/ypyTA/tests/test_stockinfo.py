import os
import sys
import pytest
import pandas as pd
from datetime import datetime

from ypyTA.stockdata import StockInfo, StockPrice

def test_stockprice():
    ts_now= datetime.now
    sym = "AAPL"
    interval = "5d"
    stockprice = StockPrice(symbol=sym, time_stamp=ts_now, time_interval=interval)
    assert stockprice.current_price == None
    assert stockprice.mean_high == None
    assert stockprice.mean_low == None
    assert stockprice.time_interval == interval
    assert stockprice.symbol == sym
    assert stockprice.time_stamp == ts_now
    assert isinstance(stockprice.price_history, pd.Series)
    assert stockprice.price_history.empty
    pass

def test_stock_price_to_dict():
    now= datetime.now()
    sym = "AAPL"
    interval = "5d"
    stock_price = StockPrice(symbol=sym, time_stamp=now, time_interval=interval)

    default_dict_stock_price = {
        'symbol': sym,
        'time_stamp': stock_price.time_stamp.isoformat(),
        'time_interval': interval, 
        'price_history': {},
        'current_price': None,
        'mean_high': None,
        'mean_low': None 
    }

    assert default_dict_stock_price == stock_price.to_dict()
    pass

def test_stockinfo_initialization():
    stock_info = StockInfo(symbol="AAPL", in_possess=True)
    assert stock_info.symbol == "AAPL"
    assert stock_info.in_possess is True
    assert stock_info.name is None
    assert isinstance(stock_info.time_stamp, datetime)
    assert isinstance(stock_info.price_data, StockPrice)
    
    assert stock_info.price_data.symbol == "AAPL"
    assert stock_info.price_data.time_interval == "5d"
    
    # Check default DataFrame fields
    assert isinstance(stock_info.revenue_history, pd.Series)
    assert stock_info.revenue_history.empty
    assert isinstance(stock_info.gross_profit_history, pd.Series)
    assert stock_info.gross_profit_history.empty
    assert isinstance(stock_info.ebit_history, pd.Series)
    assert stock_info.ebit_history.empty
    assert isinstance(stock_info.ebt_history, pd.Series)
    assert stock_info.ebt_history.empty
    assert isinstance(stock_info.net_income_history, pd.Series)
    assert stock_info.net_income_history.empty
    assert isinstance(stock_info.opc_history, pd.Series)
    assert stock_info.opc_history.empty
    assert isinstance(stock_info.capex_history, pd.Series)
    assert stock_info.capex_history.empty
    assert isinstance(stock_info.total_dept_history, pd.Series)
    assert stock_info.total_dept_history.empty
    assert isinstance(stock_info.stockholders_equity_history, pd.Series)
    assert stock_info.stockholders_equity_history.empty
    assert isinstance(stock_info.interest_expense_history, pd.Series)
    assert stock_info.interest_expense_history.empty
    pass

def test_invalid_symbol():
    with pytest.raises(ValueError, match="Stock symbol must be a non-empty string."):
        StockInfo(symbol="")
    with pytest.raises(ValueError, match="Stock symbol must be a non-empty string."):
        StockInfo(symbol=None)
    with pytest.raises(ValueError, match="Stock symbol must be a non-empty string."):
        StockInfo(symbol=123)
    pass

def test_to_dict():
    stock_info = StockInfo(symbol="AAPL", in_possess=True)
    stock_price_dict = stock_info.price_data.to_dict()

    default_dict = {
        'symbol': 'AAPL', 
        'in_possess': True, 
        'name': None, 
        'time_stamp': stock_info.time_stamp.isoformat(),
        'time_interval': "5d", 
        'price_data': stock_price_dict, 
        'revenue_history': {}, 
        'gross_profit_history': {}, 
        'ebit_history': {}, 
        'ebt_history': {}, 
        'net_income_history': {}, 
        'opc_history': {}, 
        'capex_history': {}, 
        'total_dept_history': {}, 
        'stockholders_equity_history': {}, 
        'interest_expense_history': {}
    }
    
    assert default_dict == stock_info.to_dict()
    pass

    

if __name__ == "__main__":
    pytest.main()