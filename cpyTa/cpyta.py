import os
import sys
from jinja2 import Environment, FileSystemLoader

sys.path.append(f"{os.getcwd()}/python/stockTA/stockTA")
from stockinfo import StockInfo
from stockinfocollector import StockInfoCollector
from stockanalytics import StockAnalytics

import python.stockTA.stockTA.stockinfo as stockinfo
import protobuf.stock_info_pb2

def cpyta_price_analyis(protobuf_serialized_stocklist):

  # Deserialize the input string
  new_stock_list = stock_info_pb2.StockList()
  new_stock_list.ParseFromString(protobuf_serialized_stocklist)

  for stock in new_stock_list.stocks:
    stock_info = StockInfo(stock.symbol, in_possess=False)
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
  pass


# einen string generieren und den als input verwenden
# dann diese methode zum Laufen bringen
