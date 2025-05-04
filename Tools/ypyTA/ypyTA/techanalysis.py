from dataclasses import asdict
from typing import List

from ypyTA.stockdata import StockInfo, StockPrice
from ypyTA.yfinancehelper import YfinanceHelper



class StockPriceAnalyzer():
    def __init__(self, stock_info_list: List[StockInfo]):
        self.stockInfoList = stock_info_list
        self.priceInfoList = list()
        
        pass

    def get_price_info(self, period: str = '3d') -> dict:
        yfhelper = YfinanceHelper(self.stockInfoList)
        yfhelper.fetch_yf_price_info()

        for stockInfo in self.stockInfoList:
            priceInfo = StockPrice()
            priceInfo.company = "was auch immer"
            priceInfo.time_stamp = stockInfo.time_stamp.strftime("%m-%d-%Y, %H:%M:%S")
            priceInfo.period = period
            priceInfo.current_price = stockInfo.last_price
            priceInfo.mean_high = stockInfo.price_history['High'].mean()
            priceInfo.mean_low = stockInfo.price_history['Low'].mean()
            
            print(priceInfo)
            self.priceInfoList.append(priceInfo)
        
        return self.priceInfoList


    