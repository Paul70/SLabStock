import contextlib
import os

import slab_sqlDB_operations
import slab_sqlDB_sbrokerparser

os.system('clear')

with contextlib.closing(slab_sqlDB_operations.SqlOperations("slabstock_db_config.json")) as sql_program:
    list_tables = []
    sql_program.getListOfTables(list_tables)
    for table in list_tables:
        sql_program.removeTable(table)

    depots_table_name = "depots"
    transactions_table_name = "transactions" 
    sql_program.createTable(depots_table_name)
    sql_program.insertDataIntoTable(depots_table_name, ["sbroker"])
    sql_program.createTable(transactions_table_name)

with contextlib.closing(slab_sqlDB_sbrokerparser.SbrokerParser("archive_sbroker/init.csv")) as sbroker_program:
    sbroker_program.updateSlabstockDatabase() 