from jinja2 import Environment, FileSystemLoader

class HtmlViewer:

    @staticmethod
    def getPriceInfoHtmlTable(price_info_array):
        print(price_info_array)

        # load html template, assumes template is in the same directory
        env = Environment(loader=FileSystemLoader('./templates/html/')) 
        template = env.get_template("priceinfotable.html")

        #price_infos = [price_infos, price_infos, price_infos]
        html_output = template.render(priceInfos=price_info_array)

         # Save the output to a new HTML file
        with open("output_price_info.html", "w", encoding="utf-8") as f:
            f.write(html_output)

        print("Email HTML generated successfully!")
        return html_output
