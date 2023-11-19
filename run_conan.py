#! /usr/bin/python3

import subprocess
import json  

class DevOps:

    def __init__(self) -> None:
        self.cmake = False
        self.cmake_bin = ""
        self.idUserConfig = "" 
        pass

    # Prepare build step:
    # Read conanfile.py settings and options and set DevOps attributes. 
    def bootstrap(self):
        print("If exists, delete CMakeLists.txt.user file ...")
        subprocess.run(["rm CMakeLists.txt.user"], shell = True, capture_output = False, text = False)
        print("Deleting already existing CMakeUserPrests.jsony file since it can cause trouble.")
        subprocess.run(["rm CMakeUserPresets.json"], shell = True, capture_output = False, text = False)

        print("Loading settings and options from conanfile.py ...")
        result = subprocess.run(["conan inspect . --format=json"], shell = True, capture_output = True, text = True)        
        if result.stderr:
            print(result.stderr)
            return False
        
        dictionary = json.loads(result.stdout)
        self.cmake = dictionary["options"]["cmake"]
        self.idUserConfig = int(dictionary["options"]["project_config_id"])
        pass
        

    def build(self):
        print("Conan install ...")
        result = subprocess.run(["conan install . -pr ./conanprofile -f json"], shell = True, capture_output = True, text = True)
        if result.stderr:
            print(result.stderr)
        
        if not result.stdout:
            print("Error: conan install ...")
            return False

        print("Creating CMakeUserPresets.json ...")
        dictionary = json.loads(result.stdout)
        if(self.cmake):
            # access conan json dependency graph
            for iter in dictionary["graph"]["nodes"]:
                if "cmake/" in dictionary["graph"]["nodes"][iter]["label"]:
                    self.cmake_bin = dictionary["graph"]["nodes"][iter]["cpp_info"]["root"]["bindirs"][0] + "/cmake" 

        self.__createConfig()  
        pass

    # Write a CMakeUserPresets.json file with user defined settings.
    # We will update the conan generated CMakeUserPresets.json and add additonal parameters from 
    # our PorjectUserConfig.json. The latter file deals with settings which are not handled by conan directly. 
    def __createConfig(self):
        with open("./ProjectUserConfig.json") as projectUserConfig:
            dictionary = json.load(projectUserConfig)
        projectUserConfig.close()

        dict_root = "project_config"
        dict_kits = "kits"

        # read general settings
        label = dictionary[dict_root][dict_kits][self.idUserConfig]["label"]
        description = dictionary[dict_root][dict_kits][self.idUserConfig]["description"]

        # read cmake cache variables
        cpp = dictionary[dict_root][dict_kits][self.idUserConfig]["cmakeCacheVariables"]["compiler_cpp"]
        cpp_ar = dictionary[dict_root][dict_kits][self.idUserConfig]["cmakeCacheVariables"]["compiler_cpp_ar"]
        cpp_ranlib = dictionary[dict_root][dict_kits][self.idUserConfig]["cmakeCacheVariables"]["compiler_cpp_ranlib"]
        c = dictionary[dict_root][dict_kits][self.idUserConfig]["cmakeCacheVariables"]["compiler_c"]
        c_ar = dictionary[dict_root][dict_kits][self.idUserConfig]["cmakeCacheVariables"]["compiler_c_ar"]
        c_ranlib = dictionary[dict_root][dict_kits][self.idUserConfig]["cmakeCacheVariables"]["compiler_c_ranlib"]

        # read cmake build presets
        jobs = dictionary[dict_root][dict_kits][self.idUserConfig]["cmakeBuildPreset"]["jobs"]

        with open("./CMakeUserPresets.json") as conanUserPresets:
            dictionary = json.load(conanUserPresets)
        conanUserPresets.close()

        dictionary.update({
            "configurePresets":[
                {
                    "name": "conan-debug-user",
                    "displayName": label,
                    "description": description,
                    "cmakeExecutable": self.cmake_bin,
                    "inherits": "conan-debug",
                    "cacheVariables": {
                        "CMAKE_CXX_COMPILER": cpp,
                        "CMAKE_CXX_COMPILER_AR": cpp_ar,
                        "CMAKE_CXX_COMPILER_RANLIB": cpp_ranlib,
                        "CMAKE_C_COMPILER": c,
                        "CMAKE_C_COMPILER_AR": c_ar,
                        "CMAKE_C_COMPILER_RANLIB": c_ranlib,
                        "CMAKE_GENERATOR": "Ninja"
                        }
                }
            ],
            "buildPresets":[
                {
                    "name": "conan-user-build",
                    "configurePreset": "conan-debug-user",
                    "jobs": 16
                }
            ]
        })

        with open("CMakeUserPresets.json", "w") as jsonfile:
            json.dump(dictionary, jsonfile)
        jsonfile.close()
        print("Created CMakeUserPresets.json!")
        pass


# run
devops = DevOps()
devops.bootstrap()
devops.build()




