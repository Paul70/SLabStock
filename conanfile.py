from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout

# this check needs a conan version >= 1.28
required_conan_version = ">=1.43.0"                                             

class SLabsStockRecipe(ConanFile):
    name = "SLabsStock"
    author = "Paul Heidenreich"
    description = "SLabStock conan recipe file"
    version = "0.0.1"
    settings = "os", "compiler", "build_type", "arch"
    no_copy_source = True 
    options = {
        "default_config": [True, False],
        "project_config_id": ["ANY"],
        "cmake": [True, False],
    } 
    default_options = {
        "default_config": False,
        "project_config_id": 0,
        "cmake": True,
    }                     
    

    def requirements(self):
        self.requires("zlib/1.2.11")
        self.requires("neargye-semver/0.3.0")

    def build_requirements(self):
        self.tool_requires("cmake/3.27.7")

    # Configuration of your project's home repository layout
    def layout(self):
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

        #cmake.verbose = True
        cmake.configure()
        cmake.build()


    # ConanFile Packaging: Copy artifacts (headers, lib binaries (.so/.dll etc.)) from build folder to 
    # the final package folder
    def package(self):
        cmake = CMake(self)
        cmake.install()
  


