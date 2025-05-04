import os
import shutil
import subprocess
import sys
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout

required_conan_version = ">=2.0.0"

class SlabstockConanFile(ConanFile):

    # Package binray configuration and metadata
    # Settings: project-wide configuration that cannot be defaulted in recipes
    #           See alos devopsfile.py which maintains settings
    # Options:  package-specific configurations which can be defaulted in recipes (no operating 
    #           related settings)
    name = "slabstock"
    version = "0.0.1"
    package_type = "shared-library"
    author = "Paul Heidenreich"
    description = "SLabStock - Simulation Laboratory for Stock evaluation and prediction"
    license = ""
    url = ""
    settings = "os", "compiler", "build_type", "arch" 
    options = {
        "shared": [True, False],
        "fPIC": [True, False]
    } 
    default_options = {
        "shared": True,
        "fPIC": True
    }
    no_copy_source = True
    
    # Requirements for build (tool_requires) and host (requires) context 
    def requirements(self):
        self.requires("gtest/1.14.0")
        self.requires("mariadb-connector-c/3.3.3")
        self.requires("neargye-semver/0.3.0")
        self.requires("zlib/1.2.11")
        self.requires("pybind11/2.13.6")
        self.requires("protobuf/5.27.0")
        pass

    def build_requirements(self):
        self.tool_requires("cmake/3.27.7")
        self.tool_requires("ninja/1.11.1")
        pass

    def create_runtime_venv(self):
        print(os.getcwd())

        #runtime_bin = "./build/Debug/bin" # ist eig conan build_folder
        runtime_bin = os.path.join(self.build_folder, 'Debug/bin')
        venv_path = os.path.join(runtime_bin, '.venv')
        assert os.path.isdir(runtime_bin)
        
        if not os.path.isdir(venv_path):
            subprocess.run(['python3', '-m', 'venv', '.venv'], cwd=runtime_bin, capture_output=False)
        
        try:
            shutil.copy("./requirements.txt", venv_path)
            pip_path = os.path.join(venv_path, 'bin', 'pip')
            subprocess.run([pip_path, "install", "-r", "requirements.txt"], capture_output=False)
        except Exception as e:
            print(f"Error copying file: {e}")
            return
        pass

    
    # Packaging - how to build this package 
    def config_options(self):
        self.conanfilePrint("conanfile.py ("+ self.name +"/" + self.version+"): Calling config_options()")
        if self.settings.os == "Windows":
            del self.options.fPIC
        pass

    def layout(self):
        cmake_layout(self)
        pass

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self, generator="Ninja")
        tc.generate()
        self.create_runtime_venv()
        pass

    def build(self):
        cmake = CMake(self)
        cmake.configure()

        # Actual cmake call ("cmake -DC...=conan_toolchain.cmake") happens here
        cmake.build()        
        pass

    def package(self):
        cmake = CMake(self)
        cmake.install()
        pass

    def package_info(self):
        self.cpp_info.libs = [
            "dutil"
        ]
        pass


    ###############################################################################################
    #
    # Helper methods used in this conanfile 
    #
    ###############################################################################################

    # we print to stderr since we do not want to alter conan fucntion stdoout output
    def conanfilePrint(self, string):
        print(string, file=sys.stderr)
        pass
    

