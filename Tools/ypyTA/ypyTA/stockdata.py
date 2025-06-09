import re
from dataclasses import dataclass, field, asdict
from datetime import datetime
from typing import Optional
import pandas as pd

class Helper:
    PERIOD_REGEX = re.compile(r"^(1d|5d|1mo|3mo|6mo|1y|2y|5y|10y|ytd|max)$", re.IGNORECASE)

    @staticmethod
    def is_valid_period(period: str) -> bool:
        return bool(Helper.PERIOD_REGEX.match(period))


@dataclass
class StockPrice:
    """
    A data class to store stock-related financial information, including price history,
    financial indicators, and balance sheet data.
    """

    # --- Stock price info, related to the given date and period ---
    symbol: str
    time_stamp: datetime 
    time_interval: str 

    # price history data
    price_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float))

    # explicit price data 
    current_price: float = None
    mean_high: float = None
    mean_low: float = None

    def to_dict(self) -> dict:
        """
        Converts the StockPrice object to a dictionary.
        - Converts Pandas Series to dictionnaries for serialization.
        - Ensures the timestamp is formatted as an ISO 8601 string.
        """
        data = asdict(self)  # Convert dataclass to dictionary

        # Convert timestamp to a string (ISO format)
        data["time_stamp"] = self.time_stamp.isoformat()

        # Convert Pandas Series to dictionaries (timestamp: value)
        for key, value in data.items():
            if isinstance(value, pd.Series):
                data[key] = value.to_dict()  # Convert Series to dict for serialization

        return data
    


@dataclass
class StockInfo:
    """
    A data class to store stock-related financial information, including price history,
    financial indicators, and balance sheet data.
    """

    # Stock symbol (e.g., "AAPL" for Apple) and optional, full company name
    symbol: str
    name: Optional[str] = None

    # Boolean flag indicating whether the stock is currently in possession
    # Defaults to False if not provided.
    in_possess: bool = False

    # Timestamp and time interval used for stock analyzation
    time_stamp: datetime = field(default_factory=datetime.now)
    time_interval: str = '5d' 

    # The last recorded stock price at the given timestamp
    #last_price: Optional[float] = None


    # 3-day stock price history stored as a Pandas Series (timestamps as index)
    #price_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float))
    price_data: StockPrice = field(default_factory=lambda: StockPrice(symbol="", time_stamp=datetime.now, time_interval=""))


    # --- Financial Indicators (Annual) ---

    # Revenue history (company earnings before expenses)
    revenue_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float))

    # Gross profit history (revenue - cost of goods sold)
    gross_profit_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float))

    # Earnings before interest & taxes (EBIT)
    ebit_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float))

    # Earnings before taxes (EBT)
    ebt_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float))

    # Net income history (company's total profit)
    net_income_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float))


    # --- Cash Flow Data ---

    # Operating cash flow history (cash generated from core operations)
    opc_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float))

    # Capital expenditures (CAPEX) history (funds used for asset maintenance/improvement)
    capex_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float))


    # --- Balance Sheet Data ---

    # Total debt history (company's outstanding liabilities)
    total_dept_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float))

    # Shareholders' equity history (company's net worth)
    stockholders_equity_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float))

    # Interest expenses history (cost of borrowed funds)
    interest_expense_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float))


    def __post_init__(self) -> None:
        """
        Post-initialization method to validate required fields if necessary.
        Ensures that 'symbol' is always set and trims whitespace.
        """
        if not isinstance(self.symbol, str):
            raise ValueError("Stock symbol must be a non-empty string.")
        if not self.symbol:
            raise ValueError("Stock symbol must be a non-empty string.")
        
        if not Helper.is_valid_period(period=self.time_interval):
            raise ValueError(f"Aanalysis period {self.time_interval} not valid. \n \
                               Examples for valid periods: 1d, 5d, 1mo, 3mo, 6mo, 1y, 2y, 5y, 10y, ytd, max")
         
        self.symbol = self.symbol.strip().upper()
        self.price_data.symbol = self.symbol
        self.price_data.time_stamp = self.time_stamp
        self.price_data.time_interval = self.time_interval
    

    def to_dict(self) -> dict:
        """
        Converts the StockInfo object to a dictionary.
        - Converts Pandas Series to dictionaries for serialization.
        - Ensures the timestamp is formatted as an ISO 8601 string.
        """
        data_dict = asdict(self)  # Convert dataclass to dictionary

        # Convert timestamp to a string (ISO format)
        data_dict["time_stamp"] = self.time_stamp.isoformat()

        # Convert Pandas Series to dictionaries (timestamp: value)
        for key, value in data_dict.items():
            if isinstance(value, pd.Series):
                data_dict[key] = value.to_dict()  # Convert Series to dict for serialization

        # Convert dataclass members using their 'to_dict()' method 
        data_dict["price_data"] = self.price_data.to_dict()

        return data_dict
    

