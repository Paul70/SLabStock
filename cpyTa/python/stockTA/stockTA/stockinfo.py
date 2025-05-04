from dataclasses import dataclass, field
from datetime import datetime
from collections import ChainMap
import pandas as pd

@dataclass
class StockInfo:
    symbol: str
    in_possess: bool
    name: str = None

    # time of value determination
    time_stamp: datetime = field(default_factory=datetime.now)

    # current stock price at time stamp
    last_price: float = None

    # 3 day stock price history
    price_history_3d: pd.Series = field(default_factory=pd.DataFrame)

    # annual company indicators
    revenue_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float, index=pd.to_datetime([])))
    gross_profit_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float, index=pd.to_datetime([])))

    ebit_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float, index=pd.to_datetime([])))
    ebt_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float, index=pd.to_datetime([])))
    net_income_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float, index=pd.to_datetime([])))

    opc_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float, index=pd.to_datetime([])))
    capex_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float, index=pd.to_datetime([])))

    total_dept_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float, index=pd.to_datetime([])))
    stockholders_equity_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float, index=pd.to_datetime([])))
    interest_expense_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float, index=pd.to_datetime([])))


    def __post_init__(self):
        if not self.symbol or not isinstance(self.symbol, str):
            raise ValueError("Stock symbol must be a non-empty string.")
        
        if not isinstance(self.in_possess, bool):
            raise ValueError("in_possess must be a boolean value.")
        pass

    def getAsDict(self):
        dict_stock_info = {
            "ticker": self.symbol,
            "possess": self.in_possess,
            "name":self.name,
            "time_stamp": self.time_stamp,
            "price_history": self.price_history_3d.to_dict(),
            "revenue_history": self.revenue_history.to_dict(),
            "gross_profit_history": self.gross_profit_history.to_dict(),
            "ebit_history": self.ebit_history.to_dict(),
            "ebt_history": self.ebt_history.to_dict(),
            "net_income_history": self.net_income_history.to_dict(),
            "opc_history": self.opc_history.to_dict(),
            "capex_history": self.capex_history.to_dict(),
            "total_dept_history": self.total_dept_history.to_dict(),
            "self.stockholders_equity_history": self.stockholders_equity_history.to_dict(),
            "interest_expense_history": self.interest_expense_history.to_dict()   
        }
        return dict_stock_info
