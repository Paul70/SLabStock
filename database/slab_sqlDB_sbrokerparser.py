import contextlib
import csv
import json
import os
import shutil

from datetime import datetime
from unidecode import unidecode

import slab_sqlDB_operations

class SbrokerParser:

    # __replaceUmlaute__(txt_string)
    #
    # Description:
    # The __replaceUmlaute__() method replaces German umlaut characters (ä, ö, ü, Ä, Ö, Ü) 
    # with their respective ASCII equivalents (ae, oe, ue, Ae, Oe, Ue) in the provided text string.
    #
    # Parameters:
    #
    # txt_string: A string containing text possibly containing German umlaut characters.
    #
    # Returns:
    # A new string with German umlaut characters replaced by their ASCII equivalents.
    @staticmethod
    def __replaceUmlaute__(txt_string):
        new_string = txt_string.replace("ä", "ae"). \
                                replace("ö", "oe"). \
                                replace("ü", "ue"). \
                                replace("Ä", "Ae"). \
                                replace("Ö", "Oe"). \
                                replace("Ü", "Ue")
        return new_string
    

    @staticmethod
    def __removeHeader__(input_file):
        output_file = input_file

        # Specify the number of lines to remove
        lines_to_remove = 4

        # Open the input file for reading
        with open(input_file, 'r', encoding='utf-8') as infile:
            # Read all lines from the input file
            lines = infile.readlines()

        # Open the output file for writing
        with open(output_file, 'w', encoding='utf-8') as outfile:
            # Write the lines after the specified number of lines to the output file
            outfile.writelines(lines[lines_to_remove:])
        return output_file



    @staticmethod
    def __createFileWithRemovedUmlaute__(input_file):
        try:
            # Extract file name and extension
            name, extension = os.path.splitext(input_file)

            # Output file name with "_no_Umlaute" suffix
            output_file = f"{name}_no_Umlaute{extension}"

            # Open input file for reading
            with open(input_file, 'r', encoding='windows-1252') as infile:
                # Open output file for writing
                with open(output_file, 'w', newline='', encoding='utf-8') as outfile:
                    # Create CSV reader and writer objects
                    csv_reader = csv.reader(infile, delimiter=';')
                    csv_writer = csv.writer(outfile, delimiter=';')

                    # Skip the first 3 lines
                    for _ in range(4):
                        next(infile)

                    # Iterate over rows in the input CSV file
                    #for row in reversed(csv_reader):
                    for row in csv_reader:
                        # Replace umlauts in each cell of the row
                        modified_row = [unidecode(cell) for cell in row]

                        # Write the modified row to the output CSV file
                        csv_writer.writerow(modified_row)

            return output_file
        except Exception as e:
            print(f"An error occurred while removing Umlaute: {e}")
        return None
    

    # __replaceUmlauteInCurrentDirectoryFileNames__()
    #
    # Description:
    # The __replaceUmlauteInCurrentDirectoryFileNames__() method replaces German
    # umlaut characters (ä, ö, ü, Ä, Ö, Ü) in the filenames of all files in the current working 
    # directory with their respective ASCII equivalents (ae, oe, ue, Ae, Oe, Ue).
    #
    # Parameters:
    # None.
    #
    # Returns:
    # None.
    @staticmethod
    def __replaceUmlauteInCurrentDirectoryFileNames__():
        files_in_directory = os.listdir(os.getcwd())
        for file in files_in_directory:
            new_file = SbrokerParser.__replaceUmlaute__(file)
            if file != new_file:
                print(new_file)
                os.rename(file,new_file)
        pass
        


    
    # __init__()
    #
    # Constructor of SbrokerParser class.
    # Reads a Transaktionsuebersicht.csv (downloaded from Sbroker accournt)file, creates a 
    # dictionary containing csv data and initilizes all class members. Assumes, that the file name
    # does not have umlaute. In case of umlaute, repplace them with
    # __replaceUmlauteInCurrentDirectoryFileNames__() before creating an instance of this class.  
    #
    # Parameters:
    # input_fiel: csv file name to parse, default value is None.
    #
    # Returns:
    # None.
    def __init__(self, input_file = None):
        SbrokerParser.__replaceUmlauteInCurrentDirectoryFileNames__()
        self.file_name = ""
        if not input_file:
            file_keys = ["Transaktionsuebersicht", ".csv"]
            indices = []
            # List all files and directories in the current directory and filter out directories
            files_in_directory = os.listdir(os.getcwd())
            files = [file for file in files_in_directory if os.path.isfile(os.path.join(os.getcwd(), file))]

            for index, string in enumerate(files):
                if file_keys[0] in string and file_keys[1] in string:
                    indices.append(index)
        
            if len(indices) == 0 or len(indices) > 1:
                print("Error")
            else:
                self.file_name = files[indices[0]]
        else:
            SbrokerParser.__replaceUmlaute__(input_file)
            self.file_name = input_file

        #SbrokerParser.__removeHeader__(self.file_name)
        

        #######################################################
        # for testing
        self.file_name_prepared = SbrokerParser.__createFileWithRemovedUmlaute__(self.file_name)
        #self.file_name_prepared = "sbroker_test.csv"
        #######################################################

        self.csv_file = open(self.file_name_prepared, mode='r', encoding='utf-8', errors='replace')
        self.csv_data_dict = csv.DictReader(self.csv_file, delimiter=';')

        # Converting a dictionary into a list is more convenient since we do not have 
        # to reset the file coutner after iterating over the dictionary data structure.
        self.csv_data_list = list(self.csv_data_dict)

        # Read each row and automatically convert numbers to appropriate data types
        for row in self.csv_data_list:
            # Things to consider:
            # - access columns by column names, not by index since we are using csv DictReader
            # - replace comma decimal seperator with dot and remove dot marking kilo
            row["Nominal / Stuck"] = int(row["Nominal / Stuck"])  
            row["Umsatz"] = float(row["Umsatz"].replace('.','').replace(',','.'))  
            row["Ausfuhrungskurs"] = float(row["Ausfuhrungskurs"].replace('.','').replace(',','.')) 
            row["Ausmachender Betrag"] = float(row["Ausmachender Betrag"].replace('.','').replace(',','.')) 

            # transform the date values in english date format
            row["Handelsdatum"] = datetime.strptime(row["Handelsdatum"], "%d.%m.%Y").strftime("%Y-%m-%d")
            row["Valutadatum"] = datetime.strptime(row["Valutadatum"], "%d.%m.%Y").strftime("%Y-%m-%d")
            row["Ausfuhrungsdatum"] = row["Ausfuhrungsdatum"][:-6]
            row["Ausfuhrungsdatum"] = datetime.strptime(row["Ausfuhrungsdatum"], "%d.%m.%Y").strftime("%Y-%m-%d")
        pass



    def __replaceUmlauteInCsvData__(self):
        for row in self.csv_data_list:
            for data in row:
                data = SbrokerParser.__replaceUmlaute__(data)
        pass

    def __moveToArchive__(self):
        if not os.path.exists("archive_sbroker"):
            os.makedirs("archive_sbroker")
        try:
            shutil.move(self.file_name, "archive_sbroker")
            shutil.move(self.file_name_prepared, "archive_sbroker")
        except Exception as e:
            print("file already exists.")
        pass


    def __updateSlabstockTransactionsTable__(self, input_database, input_row_data):
        input_row_data.insert(0, 'sbroker')
        input_database.insertDataIntoTable("transactions", input_row_data)
        pass


    def __updateSlabstockStockIsinBuy__(self, input_database, input_row_data):
        # check if we already hold stocks from this company
        # if not, create a tabel named with the isin as a unique identifier with no
        # speciak characters and whitspaces
        table_name = input_row_data[3]
        if input_database.doesTableExist(table_name) == slab_sqlDB_operations.StateCMD.SUCCESS_CMD_FALSE:
            if input_database.createTable("company_isin", table_name) != slab_sqlDB_operations.StateCMD.SUCCESS_CMD_TRUE:
                return
        # update isin tables
        # inserting following data into the table:
        # -trade_date(string)->col:0, 
        # -number(int)-> col:7, 
        # -stock_price(decimal)->col:10, 
        # -currency(string)->11, 
        # -oder_number(string)->col:16, 
        # -depot(string), here we treat csv data from sbroker depot exclusively
        stock_data = [input_row_data[0],input_row_data[7],input_row_data[10],input_row_data[11],input_row_data[16],'sbroker']
        input_database.insertDataIntoTable(table_name, stock_data, "company_isin")
        pass

    def __updateSlabstockStockIsinSell__(self, input_database, input_row_data):
        table_name = input_row_data[3]
        input_row_index_number = 7
        if input_database.getTableRowsSortedByTradeDateAscending(table_name) == slab_sqlDB_operations.StateCMD.SUCCESS_CMD_TRUE:
            index = 0
            orderd_result = input_database.getLastDBActionResult()[0]
            row = orderd_result[index]

            # table columns (ordered_result):
            # col 1: id (index 0)
            row_index_id = 0
            # col 2: trade_date (index 1)
            # col 3: number (index 2)
            row_index_number = 2
            # col 4: stock_price (index 3)
            # col 5: currency (index 4)
            # col 6: order_number (index 5)
            # col 7: depot (index 6)
            difference = row[row_index_number] - input_row_data[input_row_index_number]

            while True:
                if difference == 0:
                    input_database.deleteRowFromTable(table_name, row[row_index_id])
                    break
                elif difference < 0:
                    input_database.deleteRowFromTable(table_name, row[row_index_id])
                    index += 1
                    row = orderd_result[index] 
                else:
                    input_database.updateValue(table_name, "number", difference, row[row_index_id])
                    break 
                difference += orderd_result[index][2]

        # delete table if empty
        if input_database.isTableEmpty(table_name):
            input_database.removeTable(table_name)   
        pass

    
    # close(self)
    #
    # Description:
    # The close() method closes the CSV file associated with the object instance, 
    # if it is open. It ensures that resources are released properly and that the file 
    # is no longer accessed by the object.
    #
    # Parameters:
    # None.
    #
    # Returns:
    # None.
    def close(self):
        if self.csv_file:
            self.csv_file.close()
            self.csv_file = None
        self.__moveToArchive__()
        pass  



    # jsonCsvExport(self)
    #
    # Description:
    # The jsonCsvExport() method exports the data stored in a list of dictionaries, typically
    # representing CSV data, to a JSON file. It generates a filename for the JSON file by 
    # replacing the extension of the original filename (assumed to be a CSV file) with .json.
    #
    # Parameters:
    # None.
    #
    # Returns:
    # None.
    def jsonCsvExport(self):
        file_name_json = self.file_name_prepared[:-3] + "json"
        print(file_name_json)
        # Writing the list of dictionaries to a JSON file
        with open(file_name_json, 'w') as json_file:
            json.dump(self.csv_data_list, json_file)
        pass


    
    def updateSlabstockDatabase(self):
        #row_index = 1  # Index of the row you want to extract (zero-based index)
        with contextlib.closing(slab_sqlDB_operations.SqlOperations("slabstock_db_config.json")) as db_program:

            for index in enumerate(reversed(self.csv_data_list)):
                index_reversed = len(self.csv_data_list) - index[0] -1
                row_data = list(self.csv_data_list[index_reversed].values())

                # check if it is a buy transaction, transaction type is in column number 5 (zero indexed)
                if row_data[5] == 'Kauf':
                    self.__updateSlabstockStockIsinBuy__(db_program, row_data)
                
                if row_data[5] == 'Verkauf':
                    self.__updateSlabstockStockIsinSell__(db_program, row_data)
                
                # Must be last since we insert new data string in the data row.
                if row_data[5] != 'Ausschuttung':
                    self.__updateSlabstockTransactionsTable__(db_program, row_data)
        pass
        


    def printRows(self, table_name):
        with contextlib.closing(slab_sqlDB_operations.SqlOperations("slabstock_db_config.json")) as db_program:
            db_program.getTableRowsSortedByTradeDateAscending(table_name)
            result = db_program.getLastDBActionResult()
            for row in result[0]:
                print(row)
                print('\n')



    