import os
import sys
import pytest
import pandas as pd
from datetime import datetime

from ypyTA.stockdata import StockInfo, StockPrice

def test_stockinfo_initialization():
    stockInfo = StockInfo(symbol="AAPL", in_possess=True)
    assert stockInfo.symbol == "AAPL"
    assert stockInfo.in_possess is True
    assert stockInfo.name is None
    assert isinstance(stockInfo.time_stamp, datetime)
    assert isinstance(stockInfo.price_history, pd.Series)
    assert stockInfo.price_history.empty
    pass
    
    # Check default DataFrame fields
    assert isinstance(stockInfo.revenue_history, pd.Series)
    assert stockInfo.revenue_history.empty
    assert isinstance(stockInfo.gross_profit_history, pd.Series)
    assert stockInfo.gross_profit_history.empty
    assert isinstance(stockInfo.ebit_history, pd.Series)
    assert stockInfo.ebit_history.empty
    assert isinstance(stockInfo.ebt_history, pd.Series)
    assert stockInfo.ebt_history.empty
    assert isinstance(stockInfo.net_income_history, pd.Series)
    assert stockInfo.net_income_history.empty
    assert isinstance(stockInfo.opc_history, pd.Series)
    assert stockInfo.opc_history.empty
    assert isinstance(stockInfo.capex_history, pd.Series)
    assert stockInfo.capex_history.empty
    assert isinstance(stockInfo.total_dept_history, pd.Series)
    assert stockInfo.total_dept_history.empty
    assert isinstance(stockInfo.stockholders_equity_history, pd.Series)
    assert stockInfo.stockholders_equity_history.empty
    assert isinstance(stockInfo.interest_expense_history, pd.Series)
    assert stockInfo.interest_expense_history.empty
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
    stockInfo = StockInfo(symbol="AAPL", in_possess=True)

    default_dict = {
        'symbol': 'AAPL', 
        'in_possess': True, 
        'name': None, 
        'time_stamp': stockInfo.time_stamp.isoformat(), 
        'last_price': None, 
        'price_history': {}, 
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
    
    assert default_dict == stockInfo.to_dict()
    pass

def test_stockprice():
    stockprice = StockPrice()
    assert stockprice.company == None
    assert stockprice.current_price == None
    assert stockprice.mean_high == None
    assert stockprice.mean_low == None
    assert stockprice.period == None
    assert stockprice.symbol == None
    assert stockprice.time_stamp == None
    pass



if __name__ == "__main__":
    pytest.main()