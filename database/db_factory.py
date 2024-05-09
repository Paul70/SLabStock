import contextlib
import json
import os

import db_command
import db_connector

from enum import Enum

class StateCMD(Enum):
    NOT_SET           = 0
    SUCCESS_PREPARE   = 1
    ERROR_PREPARE     = 2
    SUCCESS_SQL       = 3
    ERROR_SQL         = 4
    SUCCESS_CMD_TRUE  = 5
    SUCCESS_CMD_FALSE = 6
    pass



# ist ein DataBaseConfigurator
class DBSlabstockFactory:

    @staticmethod 
    def checkConfigurationFileType(table_config):
        try:
            # [0]: base name
            # [1]: extension
            fileType = os.path.splitext(table_config)[1]
            if fileType.lower() != ".json":
                print("Config file " + table_config + " is not json and not supported.")
                return False
            else:
                return True        
        except Exception as e:
            print("Cannot open/read config file:", e)
            return False
        
    @staticmethod
    def checkJsonFormat(json_dict):
        # top json level keys: database, name, tables
        # tables array keys: name, description, column_defintions
        # column_defintions arrey keys: column, type

        # check top level:
        if "name" not in json_dict:
            print("No 'tables' array found in the JSON data.")
            return False
        if "tables" not in json_dict:
            print("No 'tables' array found in the JSON data.")
            return False
        if "column_definitions" in json_dict["tables"]:
            print("No 'column_definitions' found in the JSON data.")
            return False

        # Loop over the "tables" array
        for table in json_dict["tables"]:

            # Loop over column definitions of one table
            for column_definition in table["column_definitions"]:

                # check json format for column, type, is_referenced and auto mode
                if "column" not in column_definition:
                    print("In 'column_definiton', required entry 'column' not found in the JSON data.")
                    return False
                if "type" not in column_definition:
                    print("In 'column_definiton', required entry 'type' not found in the JSON data.")
                    return False
                if "reference" not in column_definition:
                    print("In 'column_definiton', required entry 'reference' not found in the JSON data.")
                    return False
                if "auto" not in column_definition:
                    print("In 'column_definiton', required entry 'auto' not found in the JSON data.")
                    return False

        return True
    
        



            
    

    
    

        
    


    def __init__(self, table_config):
        # muss hier noch die liste an const strings machen

        self.SQL_result = []
        self.SQL_error = []
        self.state = StateCMD.NOT_SET

        self.conntector = db_connector.DBConnector()

        if not self.checkConfigurationFileType(table_config):
            return
        
        self.db_config_file = open(table_config, mode = 'r')
        self.db_config_dict = json.load(self.db_config_file)

        if not self.checkJsonFormat(self.db_config_dict):
            return
        
        pass


    def __advanceState__(self, condition = None):
        if condition == None:
            self.state = StateCMD.NOT_SET
        elif self.state == StateCMD.NOT_SET:
            if condition:
                self.state = StateCMD.SUCCESS_PREPARE
            else:
                self.state = StateCMD.ERROR_PREPARE
        elif self.state == StateCMD.SUCCESS_PREPARE:
            if condition:
                self.state = StateCMD.SUCCESS_SQL
            else:
                self.state = StateCMD.ERROR_SQL
        elif self.state == StateCMD.SUCCESS_SQL:
            if condition:
                self.state = StateCMD.SUCCESS_CMD_TRUE
            else:
                self.state = StateCMD.SUCCESS_CMD_FALSE
        else:
            self.state = StateCMD.NOT_SET
        return




    def __executeAndCheckSQLFetchOne__(self, cmd):
        self.SQL_result.clear()
        self.SQL_error.clear()

        if self.state != StateCMD.SUCCESS_PREPARE:
            return
        
        self.conntector.executeCommandFetchOne(cmd, self.SQL_result, self.SQL_error)

        if self.SQL_error:
            self.__advanceState__(False)
            print("\tSQL Error: "+str(self.SQL_error[0]))
            return

        # if no expected result is given, simply return true
        # no special treatment here
        if len(self.SQL_result) > 1:
            self.__advanceState__(True)
            print("\tResult not suitable for 'FetchOne', use 'FetchAll' instead.")
            return
        else:
            self.__advanceState__(True)
    
        

    def __executeAndCheckSQLFetchAll__(self, cmd):
        self.SQL_result.clear()
        self.SQL_error.clear()

        if self.state != StateCMD.SUCCESS_PREPARE:
            return
        
        self.conntector.executeCommandFetchAll(cmd, self.SQL_result, self.SQL_error)

        if self.SQL_error:
            self.__advanceState__(False)
            print("\tSQL Error: "+str(self.SQL_error[0]))
            return

        # if no expected result is given, simply return true
        # no special treatment here
        if len(self.SQL_result) == 1:
            self.__advanceState__(True)
            print("\tResult not suitable for 'FetchALL', use 'FetchOne' instead.")
            return
        else:
            self.__advanceState__(True)
            return 
        


    def __extractTableConfig__(self, input_table_name):
        cols = 0
        auto_count = 0 
        column_configurations = []

        for table in self.db_config_dict["tables"]:
            
            if table["name"] != input_table_name:
                continue
            else:
                cols = table["number_columns"]
                for column_definition in table["column_definitions"]:
                    config_tuple = (column_definition["column"],
                                    column_definition["type"],
                                    column_definition["reference"],
                                    column_definition["auto"])
                    column_configurations.append(config_tuple)

                    if config_tuple[3]:
                        auto_count += 1

        configuration_dict = {
            'cols': cols,
            'auto_cols': auto_count,
            'config_cols': column_configurations
        }
        return configuration_dict
    



    def __checkNumberOfColumns__(self, input_table_name, input_data_array):
        table_config = self.__extractTableConfig__(input_table_name)
        number_of_cols = table_config["cols"]
        number_of_auto_cols = table_config["auto_cols"]

        if len(input_data_array) == (number_of_cols - number_of_auto_cols):
            self.state = StateCMD.SUCCESS_PREPARE
            return True
        else:
            print("--Error: Mismatch number of data values and table columns. Number of non auto cols: " 
                  + str(number_of_cols - number_of_auto_cols) + ", data size:" + str(len(input_data_array)))
            self.state = StateCMD.ERROR_PREPARE
            return False
        
    
    
        




    def close(self):
        self.conntector.close()
        self.db_config_file.close()
        pass


    def getState(self):
        return self.state
    
    def getLastDBActionResult(self):
        return self.SQL_result
    

    def getLastDBActionError(self):
        return self.last_DBCmd_error




    def createTable(self, input_table_config_name, input_table_name = None):
        self.__advanceState__()

        # if input_table_name is not set, we use the given name in 
        # the configuration as database tabel name
        if not input_table_name:
            input_table_name = input_table_config_name

        table_config = (self.__extractTableConfig__(input_table_config_name))["config_cols"]
        cmd = db_command.DBCommand.createMariaDBTable(input_table_name, table_config)
        self.__advanceState__(True)

        # execute sql cmd
        print("--Creating a new table '" + input_table_name + "' for database'" + self.db_config_dict["name"] + "'")
        print("\tMariadb command:\n\t" + "'" + cmd + "'")
        self.__executeAndCheckSQLFetchAll__(cmd)
        if self.state == StateCMD.SUCCESS_SQL:
            print("\tTable created")
            self.__advanceState__(True)
            return self.state
        else:
            # not error_cmd since we have a sql error and do no cmd validation here
            return self.state
            


    def createTables(self):
        # Loop over the "tables" array
        for table in self.db_config_dict["tables"]:
            if not self.createTable(table["name"]):
                break
        return self.state



    def removeTable(self, input_table_name):
        self.__advanceState__()

        if self.doesTableExist(input_table_name) != StateCMD.SUCCESS_CMD_TRUE:
            print("\tWarning: Table does not exist.")
            return self.state
        self.__advanceState__()
    
        cmd = db_command.DBCommand.removeMariaDBTable(input_table_name)
        self.__advanceState__(True)

        print("--Removing table '" + input_table_name + "' from database'" + self.db_config_dict["name"] + "'")
        print("\tMariadb command:\n\t" + "'" + cmd + "'")

        self.__executeAndCheckSQLFetchAll__(cmd)
        if self.state == StateCMD.SUCCESS_SQL: 
            print("\tTable deleted")
            self.__advanceState__(True)
            
        return self.state
        

    
    def doesTableExist(self, input_table_name):
        self.__advanceState__()

        cmd = db_command.DBCommand.selcetExistMariaDBTable(self.db_config_dict["name"], input_table_name)
        self.__advanceState__(True)
        
        print("--Checking if'" + input_table_name + "' for database' " + self.db_config_dict["name"] + "' already exists.")
        print("\tMariadb command:\n\t" + "'" + cmd + "'")

        # check for a fetch one result:
        # in this case we expect a tuple value where the first value is either '1'
        # indicating that the table exists and has at least one row or '0', indicating
        # that the table does not exist.
        self.__executeAndCheckSQLFetchOne__(cmd)
        if self.state == StateCMD.SUCCESS_SQL:
            if self.SQL_result[0][0] > 0:
                self.__advanceState__(True)
                print("\tTable exists.")
            else:
                self.__advanceState__(False)
                    
        return self.state
    
    
    def isTableEmpty(self, input_table_name):
        self.__advanceState__()

        if self.doesTableExist(input_table_name) != StateCMD.SUCCESS_CMD_TRUE:
            print("\tWarning: Table does not exist.")
            return self.state
        self.__advanceState__()
        
        cmd = db_command.DBCommand.selectAllMariaDBTable(input_table_name)
        self.__advanceState__(True)
        print("--Checking if'" + input_table_name + " is empty.")
        print("\tMariadb command:\n\t" + "'" + cmd + "'")

        self.__executeAndCheckSQLFetchOne__(cmd)
        if self.state == StateCMD.SUCCESS_SQL:
            if self.SQL_result[0][0] == 0:
                self.__advanceState__(True)
                print("\tTable exists.")
            else:
                self.__advanceState__(False)
                    
        return self.state
        
    
    def doesValueExistInTable(self, input_table_name, input_table_col, input_value):
        self.__advanceState__()

        cmd = db_command.DBCommand.checkValueExistenceInMariaDBTable(input_table_name, input_table_col, input_value)
        self.__advanceState__(True)

        print("--Checking if value exists in table.")
        print("\tMariadb command: " + "'" + cmd + "'")

        self.__executeAndCheckSQLFetchOne__(cmd)
        if self.state == StateCMD.SUCCESS_SQL:
            if self.SQL_result[0][0] == 1:
                print("\tFound value.")
                self.__advanceState__(True)
            else:
                print("\tError: Referenced value does not exist or is not unique: Result: " + self.SQL_result)
                self.__advanceState__(False)

        return self.state
    

    def getTableRows(self, input_table_name):
        self.__advanceState__()
        
        if self.doesTableExist(input_table_name) != StateCMD.SUCCESS_CMD_TRUE:
            print("\tWarning: Table does not exist.")
            return self.state
        self.__advanceState__()

        cmd = db_command.DBCommand.selectAllMariaDBTable(input_table_name)
        self.__advanceState__(True)

        print("--Query table data.")
        print("\tMariadb command: " + "'" + cmd + "'")
        self.__executeAndCheckSQLFetchAll__(cmd)
        if self.state == StateCMD.SUCCESS_SQL:
            self.__advanceState__(True)
        return self.state


    def getTableRowsSortedByTradeDateAscending(self, input_table_name):
        self.__advanceState__()
        
        if self.doesTableExist(input_table_name) != StateCMD.SUCCESS_CMD_TRUE:
            print("\tWarning: Table does not exist.")
            return self.state
        self.__advanceState__()

        cmd = db_command.DBCommand.selectAllOrderedAscendingMariaDBTable(input_table_name, "trade_date")
        self.__advanceState__(True)

        print("--Query table data.")
        print("\tMariadb command: " + "'" + cmd + "'")
        self.__executeAndCheckSQLFetchAll__(cmd)
        if self.state == StateCMD.SUCCESS_SQL:
            self.__advanceState__(True)
        return self.state


    # data: mode auto values muessen mit leeren einträgen gefüllt werden
    # data ist ein string array
    def insertDataIntoTable(self, input_table_name, input_data, input_table_config_name = None):
        self.__advanceState__()

        if not input_table_config_name:
            input_table_config_name = input_table_name

        if not self.__checkNumberOfColumns__(input_table_config_name, input_data):
            self.__advanceState__(False)
            return self.state

        table_config = (self.__extractTableConfig__(input_table_config_name))["config_cols"]
        index = 0

        # check if all referenced table values exist
        for str_tuple in table_config:

            # not a referenced or automatically generated value
            # however increase index in this case
            if not str_tuple[2] and not str_tuple[3]:
                index += 1
                continue

            # an automatically generated value, no value for this column 
            # given in data array, do NOT increase index
            elif str_tuple[3]:
                continue

            else:

                # check if all referenced values exist in the corresponding tables
                ref_table_name = str_tuple[2][1]
                ref_table_column = str_tuple[2][0]

                if not self.doesValueExistInTable(ref_table_name, ref_table_column, input_data[index]):
                    self.__advanceState__(False)
                    return self.state

        self.__advanceState__()

        # all referenced values exist, insert data row
        cmd = db_command.DBCommand.insertDataIntoMariaDBTable(input_table_name, table_config, input_data)
        self.__advanceState__(True)

        print("--Inserting data into table '" + input_table_name + "' for database' " + self.db_config_dict["name"] + "'")
        print("\tMariadb command:\n\t" + "'" + cmd + "'")

        self.__executeAndCheckSQLFetchAll__(cmd)
        if self.state == StateCMD.SUCCESS_SQL:
            self.__advanceState__(True)
            print("\tInserted data into table.")
        return self.state
    

    def deleteRowFromTable(self, input_table_name, input_condition):
        self.__advanceState__()
        
        if self.doesTableExist(input_table_name) != StateCMD.SUCCESS_CMD_TRUE:
            print("\tWarning: Table does not exist.")
            return self.state
        self.__advanceState__()

        cmd = db_command.DBCommand.deleteRowFromMariaDBTable(input_table_name, input_condition)
        self.__advanceState__(True)

        print("--Delete table row.")
        print("\tMariadb command: " + "'" + cmd + "'")
        self.__executeAndCheckSQLFetchAll__(cmd)
        if self.state == StateCMD.SUCCESS_SQL:
            self.__advanceState__(True)
        return self.state
    
    def updateValue(self, input_table_name, input_column, input_value, input_condition):
        self.__advanceState__()
        
        if self.doesTableExist(input_table_name) != StateCMD.SUCCESS_CMD_TRUE:
            print("\tWarning: Table does not exist.")
            return self.state
        self.__advanceState__()

        cmd = db_command.DBCommand.updateSingleValueMariaDBTable(input_table_name, input_column, input_value, input_condition)
        self.__advanceState__(True)

        print("--Update table row.")
        print("\tMariadb command: " + "'" + cmd + "'")
        self.__executeAndCheckSQLFetchAll__(cmd)
        if self.state == StateCMD.SUCCESS_SQL:
            self.__advanceState__(True)
        return self.state
        


        
        



        
#  next step das hier aus dem csv holen
# sbroker_data = ["sbroker","2024-04-18", "2024-04-21", "Allianz", "US1234567890", "Buy", "Stock Exchange", 10, 500.00, "USD", 50.00, "USD", "2024-04-18 10:00:00", 5000.00, "USD", "executed", "12345"]

# os.system('clear')

# with contextlib.closing(DBSlabstockFactory("slabstock_db_config.json")) as db_program:

#     # create depots tabel and insert row
#     table_depots = "depots"
#     data_sbroker = ["sbroker"]
#     db_program.createTable(table_depots)
#     db_program.insertDataIntoTable(table_depots, data_sbroker)

#     #hier durchlaufen lassen

#     db_program.createTable("transactions_buy")
#     db_program.insertDataIntoTable("transactions_buy", sbroker_data)

    
#     # order is important
#     db_program.removeTable("transactions_buy")
#     db_program.removeTable("depots")
    


