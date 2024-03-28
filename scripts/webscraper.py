from urllib.request import urlopen
from bs4 import BeautifulSoup

# get html web page 
url_ = "https://www.boerse.de/aktien/Allianz-Aktie/DE0008404005"
page_object = urlopen(url_)

html_bytes = page_object.read()
html = html_bytes.decode("utf-8")

#print(html)

html_soup = BeautifulSoup(html, "html.parser")

# ich will das span mit dem kurs
spans = html_soup.find_all("span", attrs={'itemprop': 'price'})
print("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++")
print(spans)

# muss dann genau eins sein
print("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++")
for sp in spans:
    print(sp.text)