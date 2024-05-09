class DBCommand:

    # all methods require as input 
    # - the database table name we want to modify
    # - a tuple of configuration parameters describing a value in a database table.
    #
    # A single database table entry in a column is characterized by
    # - the column name, 
    # - its value type,
    # - if it references a value in another database table identified by the database table name
    #   and the column,
    # - and if the entrie's value is automatically generated or gets an explicit input value.  


    # todo 
    # const variablen fuer die indices anlegen

    @staticmethod
    def createMariaDBTable(input_table_name, input_table_columns_definition):
        column_def_str = ""
        foreign_key_def_str = ""
        for str_tuple in input_table_columns_definition:
            column_def_str += f"{str_tuple[0]} {str_tuple[1]}, "
            if str_tuple[2]:
                foreign_key_def_str +=f"FOREIGN KEY ({str_tuple[0]}) REFERENCES {str_tuple[2][1]}({str_tuple[2][2]}), "

        # remove last comma
        if column_def_str:
            column_def_str = ''.join([column_def_str[:-2], ""])
        if foreign_key_def_str:
            foreign_key_def_str = ''.join([foreign_key_def_str[:-2], ""])
        
        # put everything together
        if foreign_key_def_str:
            mariadb_cmd = f"CREATE TABLE {input_table_name} ({column_def_str}, {foreign_key_def_str});"
        else:
            mariadb_cmd = f"CREATE TABLE {input_table_name} ({column_def_str});"
        return mariadb_cmd
    
    @staticmethod
    def removeMariaDBTable(input_table_name):
        mariadb_cmd = f"DROP TABLE {input_table_name};"
        return mariadb_cmd

    @staticmethod 
    def selcetExistMariaDBTable(input_database_name, input_table_name):
        mariadb_cmd = f"SELECT COUNT(*) FROM information_schema.TABLES WHERE TABLE_SCHEMA = '{input_database_name}' AND TABLE_NAME = '{input_table_name}';"
        return mariadb_cmd

    
    @staticmethod
    def checkValueExistenceInMariaDBTable(input_table_name ,input_column, input_value):
        mariadb_cmd = f"SELECT COUNT(*) FROM {input_table_name} WHERE {input_column} = '{input_value}'"
        return mariadb_cmd
    
    @staticmethod
    def selectAllMariaDBTable(input_table_name):
        mariadb_cmd = f"SELECT * FROM {input_table_name}"
        return mariadb_cmd
    
    @staticmethod
    def selectAllOrderedAscendingMariaDBTable(input_table_name, input_column_name):
        mariadb_cmd = f"SELECT * FROM {input_table_name} ORDER BY {input_column_name} ASC;"
        return mariadb_cmd
    
    @staticmethod
    def selectAllOrderedDescendingMariaDBTable(input_table_name, input_column_name):
        mariadb_cmd = f"SELECT * FROM {input_table_name} ORDER BY {input_column_name} DESC;"
        return mariadb_cmd
    
    @staticmethod
    def insertDataIntoMariaDBTable(input_table_name, input_table_columns_definition, input_data):
        column_str = ""
        value_str = ""
        index = 0

        for str_tuple in input_table_columns_definition:

            # not a referenced, not automatically generated value
            # value must be in data array
            if not str_tuple[2] and not str_tuple[3]:
                column_str += str_tuple[0] + ","
                
                # check if data value is string type or not (for setting it in apostrophes)
                #value_str += input_data[index] + ","
                if isinstance(input_data[index], str):
                    value_str += f"'{input_data[index]}',"
                else:
                    value_str += f"{input_data[index]},"
                index += 1 

            # a referenced value, assmeble command to insert this type of value
            # example: (SELECT <referenced_column> FROM <referenced_table> WHERE <identifying_column> = '<given_value>')
            if str_tuple[2]:
                column_str += str_tuple[0] + ","
                value_str += f"(SELECT {str_tuple[2][2]} FROM {str_tuple[2][1]} WHERE {str_tuple[2][0]} = '{input_data[index]}')," 
                index += 1
                
        
        # remove last comma
        column_str = ''.join([column_str[:-1], ""])
        value_str = ''.join([value_str[:-1], ""])

        # assemble complete command
        mariadb_cmd = f"INSERT INTO {input_table_name} ({column_str}) VALUES ({value_str});"
        return mariadb_cmd
    
    @staticmethod
    def updateSingleValueMariaDBTable(input_table_name, input_column, input_value, input_condition):
        mariadb_cmd = f"UPDATE {input_table_name} SET {input_column} = '{input_value}' WHERE id = {input_condition};"
        return mariadb_cmd
    
    @staticmethod
    def deleteRowFromMariaDBTable(input_table_name, input_condition):
        mariadb_cmd = f"DELETE FROM {input_table_name} WHERE id={input_condition};"
        return mariadb_cmd


    


    
