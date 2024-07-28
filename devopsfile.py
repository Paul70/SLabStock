#! /usr/bin/python3
from pathlib import Path

from devops.config_management.devops_file import DevopsFile
from devops.config_management.main import main

"""SLabstock project automation tool based on devops module."""

# global root path vairable
PROJECT_ROOT = Path(
    __file__).parent.absolute() # absolute is required, because debian and ubuntu defaults are different


class SlabstockDevopsFile(DevopsFile):
    project_root = str(PROJECT_ROOT)
    conan_profile_path = str(PROJECT_ROOT) + "/conanprofile"


    def function_of_Slabtock(self):
        print("This is the funciton function_of_Slabtock")
        pass


    # Generate configurations for porject
    def bootstrap(self):
        print(PROJECT_ROOT)
        print("This is the derived class bootstrap method.")
        print("Hier ist Paul")
        pass

    def prepare(self):
        self.create_conan_profile()
        self.conan_install()
        self.create_cmake_user_presets()
        pass

    def build(self):
        print("This is the derived class build method.")
        pass



################################################################################################### 

if __name__ == '__main__':
    main()
