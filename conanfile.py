from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import get
import sys

# this check needs a conan version >= 1.28
required_conan_version = ">=1.43.0"                                             

class SLabStockRecipe(ConanFile):
    name = "slabstock"
    version = "0.1.0"
    package_type = "application"

    ###############################################################################################
    #
    # Package metadata
    #
    ###############################################################################################
    author = "Paul Heidenreich"
    description = "SLabStock - Simulation Laboratory for Stock evaluation and prediction"

    ###############################################################################################
    #
    # Binary configuration - set only options which have a default value.
    # Settings: project-wide configuration that cannot be defaulted in recipes
    # Options: package-specific configuration and can be defaulted in recipes 
    #
    ###############################################################################################
    no_copy_source = True
    settings = "os", "compiler", "build_type", "arch" 
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "default_config": [True, False],
        "project_config_id": ["ANY"],
        "use_cached_cmake": [True, False],
    } 
    default_options = {
        "shared": False,
        "fPIC": True,
        "default_config": False,
        "project_config_id": 2,
        "use_cached_cmake": True,
    }                     
    

    ###############################################################################################
    #
    # conan install section - Setup Dependency Graph of SLabsStock
    # to only run this section of the recipe, execute "conan install ." within the root folder.
    #
    ###############################################################################################
    def requirements(self):
        self.requires("zlib/1.2.11")
        self.requires("neargye-semver/0.3.0")

    def build_requirements(self):
        self.tool_requires("cmake/3.27.7")
        self.tool_requires("ninja/1.11.1") # das muss ich noch ins preset file nehmen


    ###############################################################################################
    #
    # conan package section - Setup build process of current SLabsStock package in conan cache!
    # run "conan create ." within the root folder to install all dependencies and build 
    # the package inside the local conan cache.
    #
    ###############################################################################################
    #def source(self):
    #    print("conanfile.py ("+ self.name +"/" + self.version+"): Calling source()")
    #    pass
        #get(self, "main.zip", strip_root = True)

    def config_options(self):
        self.conanfilePrint("conanfile.py ("+ self.name +"/" + self.version+"): Calling config_options()")
        self.conanfilePrint(self.settings.os)
        self.conanfilePrint(self.settings.build_type)
        
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        #print("conanfile.py ("+ self.name +"/" + self.version+"): Calling layout()")
        cmake_layout(self)
    

    def generate(self):      
        deps = CMakeDeps(self)
        deps.generate()

        tc = CMakeToolchain(self, generator="Ninja")
        tc.generate()

    def build(self):
        cmake = CMake(self)

        # forward options from conan to CMake
        # example: cmake.definitions["USE_COMPASS_SCPI_SYSTEM"] = "ON" if self.options.scpi_system == "Compass" else "OFF"

        cmake.configure()

        # Actual cmake call ("cmake -DC...=conan_toolchain.cmake") happens here
        cmake.build()


    # ConanFile Packaging: Copy artifacts (headers, lib binaries (.so/.dll etc.)) from build folder to 
    # the final package folder
    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        pass

    def conanfilePrint(self, string):
        print(string, file=sys.stderr)
        pass
  


