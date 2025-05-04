from dataclasses import dataclass, field, asdict
from datetime import datetime
from rich.console import Console
from rich.table import Table
from jinja2 import Template

from stockinfo import StockInfo

#from types import price_data

priceInfos = [
    {"date": "Dec 20, 2019", "title": "Star Wars: The Rise of Skywalker", "budget": "275,000,000", "box_office": "375,126,118"},
    {"date": "May 25, 2018", "title": "Solo: A Star Wars Story", "budget": "275,000,000", "box_office": "393,151,347"},
    {"date": "Dec 15, 2017", "title": "Star Wars Ep. VIII: The Last Jedi", "budget": "262,000,000", "box_office": "1,332,539,889"},
    {"date": "May 19, 1999", "title": "Star Wars Ep. I: The Phantom Menace", "budget": "115,000,000", "box_office": "1,027,044,677"},
]




class StockPrice:

    def __init__(self, stock_info: StockInfo):
        self.time_stamp: datetime 



@dataclass
class StockAnalytics:
    symbol: str = field
    name: str = field
    in_possess: bool = field

    time_stamp: datetime = field(default_factory=datetime.now)

    price_data: dict = field(default_factory=lambda: price_data)


    def __post_init__(self, ):
        if not self.symbol or not isinstance(self.symbol, str):
            raise ValueError("Stock symbol must be a non-empty string.")
        
        if not isinstance(self.in_possess, bool):
            raise ValueError("in_possess must be a boolean value.")
        pass

    
    def prettyPriceData(self) -> str:
        # table anlegen 
        #|      Current Price        |   Stock       |   Mean High       |   Mean Low   | Date 
        #| bold red if < mean low    |  name (isin)  |   value           |     value    |    value
        #| bold green if > mean high |               |                   |              |
        #| normal if in between      |               |                   |              |
        # muss ich noch via pip installieren

        table = Table(title="Star Wars Movies")

        table.add_column("Released", style="cyan", no_wrap=True)
        table.add_column("Title", style="magenta")
        table.add_column("Box Office", justify="right", style="green")

        table.add_row("Dec 20, 2019", "Star Wars: The Rise of Skywalker", "$952,110,690")
        table.add_row("May 25, 2018", "Solo: A Star Wars Story", "$393,151,347")
        table.add_row("Dec 15, 2017", "Star Wars Ep. V111: The Last Jedi", "$1,332,539,889")
        table.add_row("Dec 16, 2016", "Rogue One: A Star Wars Story", "$1,332,439,889")

        print(table.__str__)

        return table.__str__
    


if __name__ == "__main__":
    html_template = """
    <table>
        <tr>
            <th>Date</th>
            <th>Title</th>
            <th>Production Budget</th>
            <th>Box Office</th>
        </tr>
        {% for movie in movies %}
        <tr>
            <td>{{ movie.date }}</td>
            <td>{{ movie.title }}</td>
            <td style="color: red; font-weight: bold;">€{{ movie.budget }}</td>
            <td style="color: red; font-weight: bold;">€{{ movie.box_office }}</td>
        </tr>
        {% endfor %}
    </table>
    """

    movies = [
        {"date": "Dec 20, 2019", "title": "Star Wars: The Rise of Skywalker", "budget": "275,000,000", "box_office": "375,126,118"},
        {"date": "May 25, 2018", "title": "Solo: A Star Wars Story", "budget": "275,000,000", "box_office": "393,151,347"},
        {"date": "Dec 15, 2017", "title": "Star Wars Ep. VIII: The Last Jedi", "budget": "262,000,000", "box_office": "1,332,539,889"},
        {"date": "May 19, 1999", "title": "Star Wars Ep. I: The Phantom Menace", "budget": "115,000,000", "box_office": "1,027,044,677"},
    ]

    template = Template(html_template)
    html_output = template.render(movies=movies)

    print(html_output)











