import contextlib
import json
import os

import slab_sqlDB_operations



class IsinParser:

    def __init__(self, input_file = None):
        self.file_name = ""
        if not input_file:
            cwd_list = os.listdir(os.getcwd())
            files = [file for file in cwd_list if os.path.isfile(os.path.join(os.getcwd(), file))]

            for file in files:
                if file == "isin_mapping.json":
                    self.file_name = file
        else:
            self.file_name = input_file

        try:
            self.json_file = open(self.file_name, mode='r')
            self.json_data_dict = json.load(self.json_file)
        except Exception as e:
            print(e)
        
        pass


    def close(self):
        if self.json_file:
            self.json_file.close()
            self.json_file = None
        pass


    def updateIsinTable(self):
        # Get the map from the JSON data
        map_list = self.json_data_dict["map"]
        table_name = "isin_mapping"

        # iterate over map in json dict
        with contextlib.closing(slab_sqlDB_operations.SqlOperations("slabstock_db_config.json")) as db_program:
            if db_program.doesTableExist(table_name) != slab_sqlDB_operations.StateCMD.SUCCESS_CMD_TRUE:
                db_program.createTable(table_name)

            for entry in map_list:
                isin_data = []
                for key, value in entry.items():
                    # update isin mapping table
                    # -isin_number(string)-> key:"isin" 
                    # -number(int)-> key: "company", 
                    # -stock_price(decimal)-> key: "ta-key", 
                    # -currency(string)-> key: "holdings", 
                    isin_data.append(value)
                db_program.insertDataIntoTable(table_name, isin_data)
        pass 


with contextlib.closing(IsinParser()) as isin_parser:
    isin_parser.updateIsinTable()