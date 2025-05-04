from ypyTA.stockdata import StockInfo
from ypyTA.yfinancehelper import YfinanceHelper
from ypyTA.techanalysis import StockPriceAnalyzer
from ypyTA.htmlviewer import HtmlViewer

def test_calculate_priceinfo_and_get_html_tableview():
    symbol = "AAPL"

    stock_info = StockInfo(symbol=symbol, in_possess=False)

    print("Calculationg price info ...")

    analyzer = StockPriceAnalyzer([stock_info])
    price_info = analyzer.get_price_info()

    HtmlViewer.getPriceInfoHtmlTable(price_info_array=price_info)
    pass