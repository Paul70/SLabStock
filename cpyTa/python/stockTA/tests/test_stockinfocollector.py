import os
import sys
import pytest
from datetime import datetime
import pandas as pd
import unittest
import unittest.mock
from http import HTTPStatus

sys.path.append(f"{os.getcwd()}/stockTA/stockTA")
from stockinfo import StockInfo
from stockinfocollector import StockInfoCollector

@pytest.fixture
def mock_stock_info():
    """Fixture to provide a StockInfo instance."""
    return StockInfo(ticker="AAPL", in_possess=True)

class MockTicker:
    def __init__(self, symbol: str):
        self.symbol = symbol
        pass

    def history(self, *args, **kwargs) -> pd.DataFrame:
        # *args:    The function can accept any number of positional arguments.
        #           These arguments will be captured as a tuple.
        # **kwargs: The function can accept any number of keyword arguments.
        #           These arguments will be captured as a dictionary.
        default_kwargs = {"period": "3d"}
        default_kwargs.update(kwargs)

        print("Positional yfinance history method args:", args)
        print("Key word yfinance history method args:", kwargs)

        stock_price_history = {
            "Date": [datetime(2025, 1, 1), datetime(2025, 1, 2), datetime(2025, 1, 3)],
            "Open": [10.0, 20.0, 30.0],
            "High": [10.0, 20.0, 30.0],
            "Low": [10.0, 20.0, 30.0],
            "Close": [10.0, 20.0, 30.0],
            "Volume": [10, 20, 30],
            "Dividends": [0.0, 0.0, 0.0],
            "Stock Splits": [0.0, 0.0, 0.0],
        }
        return stock_price_history

    
class Test_StockInfoCollector(unittest.TestCase):

    #@patch("yfinance.Ticker", side_effect=MockTicker)
    #@mock.patch()
    def test_initialization(mock_stock_info):
        # mocked initialization
        mock_stock_info = unittest.mock.create_autospec(StockInfo)
        stock_info_collector = StockInfoCollector(mock_stock_info)
        assert stock_info_collector.stock_info == mock_stock_info
        
        # real initialization
        stock_info_collector = StockInfoCollector(StockInfo(symbol="AAPL", in_possess=True))
        assert stock_info_collector.request_status.isOK() == True
        assert stock_info_collector.stock_info.symbol == "AAPL"
        pass

    @unittest.mock.patch('stockinfocollector.yfinance.Ticker')
    def test_updataInfo(self, mock_yfinance_ticker):
        stock_info = StockInfo(symbol="AAPL", in_possess=True)
        stock_info_collector = StockInfoCollector(stock_info)
        request_state = stock_info_collector.updateInfo()
        mock_yfinance_ticker.assert_called_with(stock_info_collector.stock_info.symbol)
        #assert isinstance(request_state, HttpRequestStatus)
        assert (request_state.status["http_code"] == HTTPStatus.OK)
        pass



if __name__ == "__main__":
    pytest.main()

