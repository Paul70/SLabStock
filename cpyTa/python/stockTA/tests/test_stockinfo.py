import os
import sys
import pytest
import pandas as pd
from datetime import datetime

sys.path.append(f"{os.getcwd()}/stockTA/stockTA")
from stockinfo import StockInfo

def test_stockinfo_initialization():
    stock = StockInfo(symbol="AAPL", in_possess=True)
    assert stock.symbol == "AAPL"
    assert stock.in_possess is True
    assert stock.name is None
    assert isinstance(stock.time_stamp, datetime)
    assert isinstance(stock.price_history_3d, pd.DataFrame)
    assert stock.price_history_3d.empty
    
    # Check default DataFrame fields
    assert isinstance(stock.revenue_history, pd.Series)
    assert stock.revenue_history.empty
    assert isinstance(stock.gross_profit_history, pd.Series)
    assert stock.gross_profit_history.empty
    assert isinstance(stock.ebit_history, pd.Series)
    assert stock.ebit_history.empty
    assert isinstance(stock.ebt_history, pd.Series)
    assert stock.ebt_history.empty
    assert isinstance(stock.net_income_history, pd.Series)
    assert stock.net_income_history.empty
    assert isinstance(stock.opc_history, pd.Series)
    assert stock.opc_history.empty
    assert isinstance(stock.capex_history, pd.Series)
    assert stock.capex_history.empty
    assert isinstance(stock.total_dept_history, pd.Series)
    assert stock.total_dept_history.empty
    assert isinstance(stock.stockholders_equity_history, pd.Series)
    assert stock.stockholders_equity_history.empty
    assert isinstance(stock.interest_expense_history, pd.Series)
    assert stock.interest_expense_history.empty

def test_invalid_symbol():
    with pytest.raises(ValueError, match="Stock symbol must be a non-empty string."):
        StockInfo(symbol="", in_possess=True)
    with pytest.raises(ValueError, match="Stock symbol must be a non-empty string."):
        StockInfo(symbol=None, in_possess=True)
    with pytest.raises(ValueError, match="Stock symbol must be a non-empty string."):
        StockInfo(symbol=123, in_possess=True)

def test_invalid_in_possess():
    with pytest.raises(ValueError, match="in_possess must be a boolean value."):
        StockInfo(symbol="AAPL", in_possess="yes")
    with pytest.raises(ValueError, match="in_possess must be a boolean value."):
        StockInfo(symbol="AAPL", in_possess=1)


if __name__ == "__main__":
    pytest.main()