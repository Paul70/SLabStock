#! /usr/bin/python3

import subprocess

###############################################################################################
#
# devopsfile.py - Managing project system settings for your whole host machine
#
# devopsfile.py is similar to conanfile.py, however it does not manage a single porject's
# dependencies and packaging, instead it maintains porject system settings like compiler toolchain
# and other build tools.
# It is designed to work well together with conan.
#
# handling all system settings to build this project for every 
# operating system defined in this list or maybe even define containers here to 
# deal with this project.
#
###############################################################################################

class SLabStockDevopsRecipe():
    name = "slabstock-devops"
    version = "0.1.0"
    author = "Paul Heidenreich"

    os_list = [
        "ubuntu_22_04"
    ]

    options = {
        "settings_profile": ["ANY"] 
    } 

    default_options = {
        "settings_profile": "default"
    }

    def checkOS(self):
        # hole mir operating system settings
        # check if we have a recipe
        pass

    def generate(self):
        pass


    subprocess.run(["python3 ./devops/run-build.py --help"], shell = True, capture_output = False, text = False)


###############################################################################################
#
# devops
###############################################################################################
