import os
import sys
import dotenv
import importlib.util

def prepare_slabstock_module_import(module_name):
    if not importlib.util.find_spec(module_name):
        venv_home = os.getenv("VIRTUAL_ENV")
        if not venv_home:
            sys.exit("Slabstock venv not activated. Activate venv first.")
        else:
            runtime_bin = os.path.dirname(venv_home)
            sys.path.append(runtime_bin)
    pass

def load_slabstock_dotenv():
    dotenv_file = dotenv.find_dotenv('.env', True, False)
    dotenv.load_dotenv(dotenv_file)
    pass
    
