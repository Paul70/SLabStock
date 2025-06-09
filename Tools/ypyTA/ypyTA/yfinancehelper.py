import os
import platform
import time
import yfinance as yf

from typing import List
from requests import Session
from requests_cache import CacheMixin, SQLiteCache
from requests_ratelimiter import LimiterMixin, MemoryQueueBucket
from pyrate_limiter import Duration, RequestRate, Limiter

from ypyTA.stockdata import StockInfo


class YfinanceError(Exception):
    """Base class for all custom yfinance-related errors."""

    def __init__(self, symbol, message):
        full_message = f"[{symbol}] {message}"
        super().__init__(full_message)
        self.symbol = symbol
        self.message = message  

class EmptyData(YfinanceError):
    def __init__(self, symbol, message=None):
        if message is None:
            message = "Yfinance request deliverd empty data structure indicating that an error occured or yfinance session is no longer properly set up."
        super().__init__(symbol, message)
        pass

class InvalidTickerError(YfinanceError):
    def __init__(self, symbol, message=None):
        if message is None:
            message = "Yfinacne ticker is invalid or has no market data."
        super().__init__(symbol, message)
        pass


class CachedLimiterSession(CacheMixin, LimiterMixin, Session):
    pass


class YfinanceHelper():
    yf_financial_keys = {
        "revenue": "Total Revenue",
        "gross_profit": "Gross Profit",
        "ebit": "EBIT",
        "ebt": "Pretax Income",
        "net_income": "Net Income",
        "sh_equity": "Stockholders Equity",
        "interest_exp": "Interest Expense"
    }

    yf_balanceSheet_keys = {
        "depts": "Total Debt"
    }

    yf_info_keys = {
        "lname": "longName"
    }

    yf_user_agent = ["Chrome/133.0.0.0 AppleWebKit/537.36 (KHTML, like Gecko) Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_1) Safari/537.36"]


    @staticmethod
    def detect_platform():
        return platform.system()
    
    @staticmethod
    def create_cached_limiter_session():
        session = CachedLimiterSession(
            limiter=Limiter(RequestRate(2, Duration.SECOND*5)), # max 2 requests per 5 seconds
            bucket_class=MemoryQueueBucket,
            backend=SQLiteCache("yfinance.cache"),
        )
        session.headers['User-agent'] = YfinanceHelper.yf_user_agent
        return session
    
    def __init__(self, stock_info_list: List[StockInfo], cache_path:str = None):
        self.stockInfoList = stock_info_list
        self.yfTickers = yf.Tickers(self.__extract_symbols__(), session=YfinanceHelper.create_cached_limiter_session())

        # set (cutstom) yf cache path, default one depends on the os:
        # - Windows = C:/Users/<USER>/AppData/Local/py-yfinance
        # - Linux = /home/<USER>/.cache/py-yfinance
        # - MacOS = /Users/<USER>/Library/Caches/py-yfinance
        if cache_path:
            yf.set_tz_cache_location(cache_path)
        pass

    def __extract_symbols__(self):
        symbols = []
        for stockInfo in self.stockInfoList:
            symbols.append(stockInfo.symbol)
        return symbols

    def fetch_yf_price_info(self, period: str = '5d'):
        for stockInfo in self.stockInfoList:
            try:
                stockInfo.last_price = self.yfTickers.tickers[stockInfo.symbol].get_fast_info().last_price
                if not stockInfo.last_price:
                    raise EmptyData    
            except EmptyData as e:
                # log
                print(e)
            except Exception as e:
                print(e)
            
            # wait unitl next yfinance request is safe
            time.sleep(5)

            try:
                stockInfo.price_history = self.yfTickers.tickers[stockInfo.symbol].history(period=period) 
                if stockInfo.price_history.empty:
                    raise EmptyData    
            except EmptyData as e:
                # log
                print(e)
            except Exception as e:
                print(e)
            
            # wait unitl next yfinance request is safe
            time.sleep(5)
        pass











    def download_yf_data(self, period: str = '5d'):
        if period not in self.yf_valid_periods:
            raise InvalidPeriodError
        
        #history_rate = RequestRate(1, Duration.SECOND*1)
        #limiter = Limiter(history_rate)
        #session = LimiterSession(limiter=limiter)
        #session.headers = {'User-Agent': 'Chrome/133.0.0.0'}

        dat = yf.Ticker("MSFT")
        dat._data.user_agent_headers = {'User-Agent': 'Chrome/133.0.0.0'}
        finfo = dat.get_fast_info()
        print(finfo.last_price)
        info = dat.info
        print(info["longName"])

        dat.calendar
        #dat.analyst_price_targets
        #dat.quarterly_income_stmt
        #dat.history(period='1mo')
        #dat.option_chain(dat.options[0]).calls


        stocks = ["AAPL", "MSFT", "GOOGL"]
        data = yf.download(tickers=stocks, period=period)
        #print(ticker.info["longName"])

        pass

    def fetch_yfhistory(self, period: str = '5d'):
        if period not in self.yf_valid_periods:
            raise InvalidPeriodError
        
        for info in self.stockInfoList:
            try:
                self.yf_ticker = yf.Ticker(ticker=info.symbol)
                yf_histroy = self.yf_ticker.history(period=period)
            except Exception as e:
                if "429" in str(e):
                    print("Too many requests! Waiting 10 seconds...")
                time.sleep(60)
                continue

            try:
                info.price_history= self.history(period)
            except Exception as e:
                print(e)

            time.sleep(20)
        pass        


                



        pass

    def fetch_stockinfo_data(self, period: str = '5d'):
        if period not in self.yf_valid_periods:
            raise InvalidPeriodError
        
        sym = self.stockInfoList[0].symbol
        
        self.yf_ticker = yf.Ticker(ticker=sym)
        bs = self.yf_ticker.history(period=period)
        
        try:
            yf_balance_sheet = self.balance_sheet
            if yf_balance_sheet.empty:
                raise InvalidTickerError(self.stockInfo.symbol)
        except InvalidTickerError as e:
            # in ein log file und weiter machen
            print(e)

        try:    
            yf_financials = self.financials
            if yf_financials.empty:
                raise InvalidTickerError((self.stockInfo.symbol))
        except InvalidTickerError as e:
            # in ein log file und weiter machen
            print(e)

        try:
            yf_info = self.get_info()
            if not yf_info:
                raise InvalidTickerError((self.stockInfo.symbol))
        except InvalidTickerError as e:
            # in ein log file und weiter machen
            print(e)
        
        try:
            yf_fast_info = self.get_fast_info()
            if not yf_fast_info:
                raise InvalidTickerError((self.stockInfo.symbol))
        except InvalidTickerError as e:
            # in ein log file und weiter machen
            print(e)

        try:
            self.stockInfo.name = yf_info['lname']
            self.stockInfo.last_price = yf_fast_info.last_price
            self.stockInfo.price_history= self.history(period)
            self.stockInfo.revenue_history = yf_financials.loc[self.yf_financial_keys['revenue']]
            self.stockInfo.gross_profit_history = yf_financials.loc[self.yf_financial_keys['gross_profit']]
            self.stockInfo.ebit_history = yf_financials.loc[self.yf_financial_keys['ebit']]
            self.stockInfo.ebt_history = yf_financials.loc[self.yf_financial_keys['ebt']]
            self.stockInfo.net_income_history = yf_financials.loc[self.yf_financial_keys['net_income']]
            self.stockInfo.total_dept_history = yf_balance_sheet.loc[self.yf_balanceSheet_keys['depts']]
            self.stockInfo.stockholders_equity_history = yf_balance_sheet.loc[self.yf_financial_keys['sh_equity']]
            self.stockInfo.interest_expense_history = yf_financials.loc[self.yf_financial_keys['interest_exp']]
        except Exception as e:
            print(e)
        pass

    



