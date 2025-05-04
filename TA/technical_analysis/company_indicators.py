import yfinance
import pandas as pd
from datetime import datetime

class CompanyIndicators():

    def __init__(self, ticker):
        self.ticker = ticker
        self.stock_price = None
        self.refernce_date = None
        self.revenue = None
        self.gross_profit = None
        self.gross_profit_margin = None
        self.FCF = None # free cash flow
        self.OPC = None # operating cash flow
        self.CapEx = None # capital expenditures
        self.ebit = None
        self.ebt = None
        self.net_income = None
        self.net_debt = None
        self.ruel_of_40 = None
        self.gearing_ratio = None
        self.interest_coverage_ratio = None

        # calculation of all data
        company = yfinance.Ticker(ticker)
        income_statement = company.financials

        # latest stock price
        try:
            self.stock_price = company.info.get('regularMarketPrice', None)  # Use .get() to avoid KeyError
            if self.stock_price is None:
                self.stock_price = company.history(period="1d", interval="1m")['Close'][-1]
        except Exception as e:
            print(f"An error occurred: {e}")

        self.revenue = income_statement.loc['Total Revenue']
        self.refernce_date = self.revenue.index[0]
        self.gross_profit = income_statement.loc['Gross Profit']
        self.gross_profit_margin = self.gross_profit.iloc[0] / self.revenue.iloc[0]

        # OPC, CapEx, FCF
        cash_flow_info = company.cashflow
        self.OPC = cash_flow_info.loc['Cash Flow From Continuing Operating Activities']
        self.CapEx = cash_flow_info.loc['Capital Expenditure']
        self.FCF = self.OPC.iloc[0] - self.CapEx.iloc[0]

        # ebit, ebt, net income
        self.ebit = income_statement.loc['EBIT']
        self.ebt = income_statement.loc['Pretax Income']
        self.net_income = income_statement.loc['Net Income']

        # rule of 40
        # yfinance publishing data of anual company data is 20xx-09-30
        revnue_current = self.revenue.iloc[0]
        revnue_previous = self.revenue.iloc[1]


        # check if publishing data is already over in this year
        #if datetime(datetime.now().year, 9, 30) < datetime.now(): 
        #    revnue_previous = income_statement.loc[datetime(datetime.now().year - 1, 9, 30)]
        #else:
        #    revnue_previous = income_statement.loc[datetime(datetime.now().year - 2, 9, 30)]
        #    revnue_previous = income_statement.loc['Total Revenue', '2022']
            
        revenue_growth = (revnue_current-revnue_previous) / (revnue_previous/100)
        fcf_margin = self.FCF / revnue_current
        self.ruel_of_40 = revenue_growth + fcf_margin

        # gearing ratio
        # Fetch balance sheet data (annual data)
        balance_sheet = company.balance_sheet
        self.net_debt = balance_sheet.loc['Total Debt']
        # Extract Total Equity/Eigenkapital (=Stockholders Equity)
        total_equity = balance_sheet.loc['Stockholders Equity']
        self.gearing_ratio = (self.net_debt.iloc[0] / total_equity.iloc[0]) * 100

        #interest coverage ratio
        # Extract Interest Expense
        interest_expense = income_statement.loc['Interest Expense']
        self.interest_coverage_ratio = self.ebit.iloc[0] / interest_expense.iloc[0]

        print("Referende Date: " + str(self.refernce_date))
        print("Revenue: " + str(self.revenue.iloc[0]))
        print("Gross profit: " + str(self.gross_profit.iloc[0]))
        print("Gross profit margin: " + str(self.gross_profit_margin))
        print("FCF: " + str(self.FCF))
        print("OPC: " + str(self.OPC.iloc[0]))
        print("CapEx: " + str(self.CapEx.iloc[0]))
        print("EBIT: " + str(self.ebit.iloc[0]))
        print("EBT: " + str(self.ebt.iloc[0]))
        print("Net income: " + str(self.net_income.iloc[0]))
        print("Total debt: " + str(self.net_debt.iloc[0]))
        print("Rule of 40: " + str(self.ruel_of_40))
        print("Gearing ratio: " + str(self.gearing_ratio))
        print("Interest covareage ratio: " + str(self.interest_coverage_ratio))
        print("Stock Price: " + str(self.stock_price))

        pass

indicators = CompanyIndicators("AAPL")
