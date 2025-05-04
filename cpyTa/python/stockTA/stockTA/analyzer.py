from datetime import datetime
from stockinfo import StockInfo
from stockinfocollector import StockInfoCollector
from stockanalytics import StockAnalytics
from jinja2 import Environment, FileSystemLoader
import os



class StockPrice:
    html_price: dict = {
        "date": "",
        "stock": "",
        "current_price": "",
        "mean_high": "",
        "mean_low": ""
    }

    def __init__(self, stock_info: StockInfo ):
        self.stock_info = stock_info
        self.html_price = StockPrice.html_price.copy() 
        pass

    def getPriceInfo(self):
        self.html_price["date"] = self.stock_info.time_stamp.strftime("%m-%d-%Y, %H:%M:%S")
        self.html_price["stock"] = self.stock_info.name
        self.html_price["current_price"] = self.stock_info.last_price
        self.html_price["mean_high"] = self.stock_info.price_history_3d['High'].mean()
        self.html_price["mean_low"] = self.stock_info.price_history_3d['Low'].mean()
        return self.html_price


if __name__ == "__main__":
    print(os.getcwd())

    # hier als input eine list von symbols
    # array von stock_infos

    # und dann kann ich das für jeden stock_info machen

    # brauch das html dict
    stock_info = StockInfo(symbol="AAPL", in_possess=True)
    stock_info_collector = StockInfoCollector(stock_info)
    result = stock_info_collector.updateInfo()
    if(result.isOK):
        stock_price = StockPrice(stock_info)
        price_infos = stock_price.getPriceInfo()

        print(price_infos)

        # load html template
        env = Environment(loader=FileSystemLoader('./stockTA/html/'))  # Assumes template is in the same directory
        template = env.get_template("stocktable.html")




        price_infos = [price_infos, price_infos, price_infos]
        html_output = template.render(priceInfos=price_infos)

         # Save the output to a new HTML file
        with open("output_email.html", "w", encoding="utf-8") as f:
            f.write(html_output)

        print("Email HTML generated successfully!")
    

    else:
        print("no stock info available")

    

