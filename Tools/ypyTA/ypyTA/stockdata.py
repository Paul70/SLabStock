from dataclasses import dataclass, field, asdict
from datetime import datetime
from typing import Optional
import pandas as pd

@dataclass
class StockInfo:
    """
    A data class to store stock-related financial information, including price history,
    financial indicators, and balance sheet data.
    """

    # Stock symbol (e.g., "AAPL" for Apple)
    symbol: str

    # Boolean flag indicating whether the stock is currently in possession
    # Defaults to False if not provided.
    in_possess: bool = False

    # Full company name (optional)
    name: Optional[str] = None

    # Timestamp representing the last update time of stock data
    time_stamp: datetime = field(default_factory=datetime.now)

    # The last recorded stock price at the given timestamp
    last_price: Optional[float] = None

    # 3-day stock price history stored as a Pandas Series (timestamps as index)
    price_history: pd.Series = field(default_factory=lambda: pd.Series(dtype=float))


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

        self.symbol = self.symbol.strip().upper()
    
    def to_dict(self) -> dict:
        """
        Converts the StockInfo object to a dictionary.
        - Converts Pandas Series to dictionaries for serialization.
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
class StockPrice:

    # --- Stock price info, related to the given date and period ---

    # Stock
    company: str = None
    symbol: str = None

    # Timestamp representing the last update time of stock data
    time_stamp: datetime = None
    period: str = None

    # Price data 
    current_price: float = None
    mean_high: float = None
    mean_low: float = None
