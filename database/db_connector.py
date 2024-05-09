import mysql.connector

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
        database=self.db_name)

        # Create a cursor object to execute SQL queries and commands
        self.mariaDB_cursor = self.mariaDB_connector.cursor()
        pass

    
    def executeCommandFetchAll(self, cmd_str, result, error):
        try:
            self.mariaDB_cursor.execute(cmd_str)

            # committing an executed command is necessary to publish the changes
            # especially for insert and update commands
            result.append(self.mariaDB_cursor.fetchall())
            self.mariaDB_connector.commit()
            return True
        except Exception as e:
            error.append(e)
            return False 
        pass

    def executeCommandFetchOne(self, cmd_str, result, error):
        try:
            self.mariaDB_cursor.execute(cmd_str)
            result.append(self.mariaDB_cursor.fetchall()[0])
            self.mariaDB_connector.commit()
            return True
        except Exception as e:
            error.append(e)
            return False
        pass

    def close(self):
        self.mariaDB_cursor.close()
        self.mariaDB_cursor = None
        self.mariaDB_connector.close()
        self.mariaDB_connector = None
        pass