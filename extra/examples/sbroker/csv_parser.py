import contextlib
import csv
import json
import mysql.connector
import os


class DBConnector:
    def __init__(self):
        self.db_name = "slabstock_test"
        self.db_user = "test_user"
        self.db_host = "localhost"

        # open database
        self.mariaDB_connector = mysql.connector.connect(
            host=self.db_host,
            user=self.db_user,
            password="123test",
            database=self.db_name
        )

        # Create a cursor object to execute SQL queries and commands
        self.mariaDB_cursor = self.mariaDB_connector.cursor()
        pass


    def close(self):
        self.mariaDB_cursor.close()
        self.mariaDB_cursor = None
        self.mariaDB_connector.close()
        self.mariaDB_connector = None
        pass


class DBController:
    def __init__(self):
        pass

    def createTabel(self, table_name, tabel_fields_array):
        fields_str = "( "
        for str_pair in tabel_fields_array:
            fields_str += str_pair[0] + " " + str_pair[1] + ", "

        # remove last whitespace and comma and replace them with ");"
        fields_str = ''.join([fields_str[:-2], ' );'])
        
        mariadb_cmd = f"CREATE TABLE {table_name} {fields_str}"
        print(mariadb_cmd)

        # execute command via connector
        pass

    def addToTable(self, table_columns, values):
        # insert command machen
        pass


class DBTable:
    def __init__(self):
        self.name = "depots"
        self.fields = [
                        ("id", "INT AUTO_INCREMENT PRIMARY KEY"),
                        ("name", "VARCHAR(255) UNIQUE")
                    ]
        self.inputCols = ["name"]
        pass

    def getName(self):
        return self.name

    def getFields(self):
        return self.fields

    def getListOfInputColumns(self):
        return self.inputCols





class SlabStockDataBaseConnector:


# mysql -u test_user -p


    def __init__(self):
        self.db_name = "slabstock_test"
        self.db_user = "test_user"
        self.db_host = "localhost"
        self.db_tables_list = {
            'depots': "depots",
            'transactionsBuy': "transactions_buy",
            'companies': "companies"
        }

        self.mariaDB_connector = mysql.connector.connect(
            host=self.db_host,
            user=self.db_user,
            password="123test",
            database=self.db_name
        )

        # Create a cursor object to execute SQL queries and commands
        self.mariaDB_cursor = self.mariaDB_connector.cursor()
        pass


    def close(self):
        self.mariaDB_cursor.close()
        self.mariaDB_cursor = None
        self.mariaDB_connector.close()
        self.mariaDB_connector = None
        pass
        

    def createTableBrokerCmd(self):
        table_title = self.db_tables_list["depots"]
        mariadb_cmd_str = "CREATE TABLE " + table_title + """ ( id INT AUTO_INCREMENT PRIMARY KEY, 
                                                                name VARCHAR(255) UNIQUE );"""

        # hier muss ich so einen try catch einbauen noch
        cmd = "use slabstock_test"
        print(cmd)
        self.mariaDB_cursor.execute("USE slabstock_test;")
        self.mariaDB_cursor.execute(mariadb_cmd_str)

        
        results = self.mariaDB_cursor.fetchall()

        # Print the results
        for row in results:
            print(row)
        pass

    def createTableTransactionBuy(self):
        table_name = self.db_tables_list["stock_transactions_buy"]
        mariadb_cmd_str = "CREATE TABLE " + table_name + """ (  id INT AUTO_INCREMENT PRIMARY KEY,  
                                                                depot_Id INT,
                                                                depot_name VARCHAR(255),
                                                                trade_date DATE,
                                                                valute_date DATE,
                                                                name VARCHAR(255),
                                                                ISIN VARCHAR(12),
                                                                WKN VARCHAR(6),
                                                                trading_place VARCHAR(255),
                                                                number DECIMAL(10,2),
                                                                sales_volume DECIMAL(10,2),
                                                                currency VARCHAR(3),
                                                                execution_price DECIMAL(10,2),
                                                                exchange_rate_currency VARCHAR(3),
                                                                execution_date DATETIME,
                                                                amount_loan DECIMAL(10,2),
                                                                trade_currency VARCHAR(3),
                                                                order_state VARCHAR(255),
                                                                order_number VARCHAR(255),
                                                                FOREIGN KEY (depot_id) REFERENCES depots(id),
                                                                FOREIGN KEY (depot_name) REFERENCES depots(name));"""


        # hier muss ich so einen try catch einbauen noch
        self.mariaDB_cursor.execute(mariadb_cmd_str)        
        pass






    def addDepotTable(self, name):
        check_cmd = f"SELECT COUNT(*) FROM depots WHERE name = '{name}'"

        try:
            self.mariaDB_cursor.execute(check_cmd)
            result = self.mariaDB_cursor.fetchone()
            if result[0] == 0:  # If name doesn't exist
                insert_cmd = f"INSERT INTO depots (name) VALUES ('{name}')"
                self.mariaDB_cursor.execute(insert_cmd)
                self.mariaDB_connector.commit()  # Commit the transaction
                print("Insertion successful.")
            else:
                print("Name already exists, skipping insertion.")
        except Exception as e:
            print("Error executing SQL statement:", e)

        #string_list = ["INSERT INTO", 
        #               "depots", 
        #               "(name)",
        #               "VALUES (",
        #               "'"+name+"'",
        #               ");"]
        

        #cmd = " ".join(string_list)
        #print(cmd)


        #self.mariaDB_cursor.execute(cmd)


        #INSERT INTO transactions (Handelsdatum, Valutadatum, ISIN, Transaktionsart, Handelsplatz, `Nominal / Stück`, Umsatz, Währung, Ausführungskurs, Kurswährung, Ausführungsdatum, `Ausmachender Betrag`, Handelswährung, Orderstatus, Ordernummer)
        #VALUES ('2024-04-18', '2024-04-21', 'US1234567890', 'Buy', 'Stock Exchange', 10, 500.00, 'USD', 50.00, 'USD', '2024-04-18 10:00:00', 5000.00, 'USD', 'executed', '12345');
        pass

    def showTable(self, name):
        string_list = ["SELECT * FROM", name, ";"]
        cmd = " ".join(string_list)
        print(cmd)
        self.mariaDB_cursor.execute(cmd)
        # Fetch the results
        results = self.mariaDB_cursor.fetchall()

        # Print the results
        for row in results:
            print(row)

        pass















class SBroker:
    @staticmethod
    def replaceUmlaute(txt_string):
        new_string = txt_string.replace("ä", "ae").replace("ö", "oe").replace("ü", "ue").replace("Ä", "Ae").replace("Ö", "Oe").replace("Ü", "Ue")
        return new_string

    @staticmethod
    def replaceUmlauteInFileNames():
        files_in_directory = os.listdir(os.getcwd())
        for file in files_in_directory:
            new_file = SBroker.replaceUmlaute(file)
            if file != new_file:
                print(new_file)
                os.rename(file,new_file)
        pass

    def __init__(self):
        self.file_name = ""
        file_keys = ["Transaktionsuebersicht", ".csv"]
        indices = []
        # List all files and directories in the current directory and filter out directories
        files_in_directory = os.listdir(os.getcwd())
        files = [file for file in files_in_directory if os.path.isfile(os.path.join(os.getcwd(), file))]

        for index, string in enumerate(files):
            if file_keys[0] in string and file_keys[1] in string:
                indices.append(index)
        
        if len(indices) > 1:
            print("Error")
        else:
            self.file_name = files[indices[0]]
        

        self.csv_file = open(self.file_name, mode='r', encoding='utf-8', errors='replace')
        self.csv_data_dict = csv.DictReader(self.csv_file, delimiter=';')

        # Converting a dictionary into a list is more convenient since we do not have 
        # to reset the file coutner after iterating over the dictionary data structure.
        self.csv_data_list = list(self.csv_data_dict)
        self.replaceUmlauteInCsvData()
        pass


    def replaceUmlauteInCsvData(self):
        for row in self.csv_data_list:
            for data in row:
                data = SBroker.replaceUmlaute(data)
        pass

    def jsonCsvExport(self):
        file_name_json = self.file_name[:-3] + "json"
        print(file_name_json)
        # Writing the list of dictionaries to a JSON file
        with open(file_name_json, 'w') as json_file:
            json.dump(self.csv_data_list, json_file)
        pass



    def updateMariaDB(self):
        # connect to mariadb database

        # how to create a user for a database in mariadb
        #CREATE USER 'username'@'localhost' IDENTIFIED BY 'password';
        #GRANT ALL PRIVILEGES ON `database_name`.* TO 'username'@'localhost';
        #FLUSH PRIVILEGES;

        db_name = "slabstock_test"


        DB_connection = mysql.connector.connect(
            host="localhost",
            user="test_user",
            password="123test",
            database="slabstock_test"
        )
        # Create a cursor object to execute SQL queries and commands
        cursor = DB_connection.cursor()

        # Example query: select all rows from a table
        cursor.execute("show databases;")

        # Fetch the results
        results = cursor.fetchall()

        # Print the results
        for row in results:
            print(row)

        # check if table exists in database
        command_string = "SELECT * FROM information_schema.tables WHERE table_schema = '" + db_name + "' AND table_name = ' your_table_name';" 
        cursor.execute(command_string)
        results = cursor.fetchall()

        if results:
            print("The table exists.")
        else:
            print("The table does not exist.")
        
        # Close the cursor and connection
        cursor.close()
        DB_connection.close()
        pass


    def close(self):
        if self.csv_file:
            self.csv_file.close()
            self.csv_file = None
        pass  


# test section




os.system('clear')
SBroker.replaceUmlauteInFileNames()

table = DBTable()
n = table.getName()
f = table.getFields()

cont = DBController()
cont.createTabel(n,f)


paired_values = [("hallo", "welt"), ("hey","jude")]
print(paired_values[0])

#with contextlib.closing(SlabStockDataBaseConnector()) as program:
    #program.addDepotTable("ING")
    #program.createTableBrokerCmd()
    #program.showTable("depots")

#with contextlib.closing(SBroker()) as program:
#    program.jsonCsvExport()
#    program.updateMariaDB()
    








