import yfinance
from datetime import datetime
from stockinfo import StockInfo
from http import HTTPStatus

class HttpRequestStatus:
    status_keys = ["http_code", "http_msg", "detail"]

    def __init__(self):
        self.status = {
            self.status_keys[0]: HTTPStatus.OK,
            self.status_keys[1]: HTTPStatus(HTTPStatus.OK).phrase,
            self.status_keys[2]: ""
        }
    
    def set(self, http_code: HTTPStatus, detail: str = None):
        self.status[self.status_keys[0]] = http_code
        self.status[self.status_keys[1]] = HTTPStatus(http_code).phrase
        if detail:
            self.status[self.status_keys[2]] = detail
        pass

    def isOK(self):
        if self.status[self.status_keys[0]] == HTTPStatus.OK:
            return True
        else:
            return False


class StockInfoCollector:
    yfinance_keys = {
        "revenue": "Total Revenue",
        "gross_profit": "Gross Profit",
        "ebit": "EBIT",
        "ebt": "Pretax Income",
        "net_income": "Net Income",
        "depts": "Total Debt",
        "sh_equity": "Stockholders Equity",
        "interest_exp": "Interest Expense"
    }

    def __init__(self, stock_info: StockInfo):
        self.stock_info = stock_info
        self.request_status = HttpRequestStatus()
        self.stock_ticker: yfinance.Ticker = None

    def __update__(self):
        self.stock_info.time_stamp = datetime.now()

        try:
            self.stock_ticker = yfinance.Ticker(self.stock_info.symbol)
        except Exception as e:
            self.request_status.set(400, str(e))    
        return self.request_status
    
    
    def updateInfo(self) -> HttpRequestStatus:
        self.__update__()
        if not self.request_status.isOK:
            return self.request_status
        
        financials = self.stock_ticker.financials
        balance_sheet = self.stock_ticker.balance_sheet

        try:
            self.stock_info.name = self.stock_ticker.info['longName']
            self.stock_info.last_price = self.stock_ticker.fast_info.last_price
            self.stock_info.price_history_3d = self.stock_ticker.history(period='3d')
            self.stock_info.revenue_history = financials.loc[self.yfinance_keys['revenue']]
            self.stock_info.gross_profit_history = financials.loc[self.yfinance_keys['gross_profit']]
            self.stock_info.ebit_history = financials.loc[self.yfinance_keys['ebit']]
            self.stock_info.ebt_history = financials.loc[self.yfinance_keys['ebt']]
            self.stock_info.net_income_history = financials.loc[self.yfinance_keys['net_income']]
            self.stock_info.total_dept_history = balance_sheet.loc[self.yfinance_keys['depts']]
            self.stock_info.stockholders_equity_history = balance_sheet.loc[self.yfinance_keys['sh_equity']]
            self.stock_info.interest_expense_history = financials.loc[self.yfinance_keys['interest_exp']]
        except Exception as e:
            self.request_status.set(404, str(e))
        return self.request_status
    

    def getInfo(self) -> StockInfo:
        return self.stock_info

        
if __name__ == "__main__":
    info = StockInfo(symbol="TSLA", in_possess=True)
    collector = StockInfoCollector(info)
    collector.updateInfo()
    print(info.price_history_3d)
    print('\n')
    print(info.last_price)

    



        

        


