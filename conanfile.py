from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout

# this check needs a conan version >= 1.28
required_conan_version = ">=1.43.0"                                             

class SLabsStockRecipe(ConanFile):
    name = "SLabsStock"
    author = "Paul Heidenreich"
    description = "SLabStock conan recipe file"
    version = "0.0.1"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"                           

    # Do not copy the sources to the package's build dirs (False setting is only
    # necessary for builds, which pollute the source dir).
    no_copy_source = True

    def requirements(self):
        self.requires("zlib/1.2.11")
        self.requires("neargye-semver/0.3.0")

    def build_requirements(self):
        self.tool_requires("cmake/3.26.3")

    # Configuration of your project's home repository layout
    def layout(self):
        cmake_layout(self)
    

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()

        # Configuration of cmake toolchain file (conan_toolchain.cmake)
        # toolchain file defines the CMakePresets.json content
        tc = CMakeToolchain(self, generator="Ninja")
        # if exists cmake user preset set false otherwise set  to true
        tc.user_presets_path = False 
        tc.cache_variables["foo"] = True 
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



    
    #def build(self):
    #    cmake = self._configure_cmake()
    #    cmake.build()

    #def package(self):
    #    cmake = self._configure_cmake()

        # Do not use self.copy, but use CMake's install mechanism, which is not conan
        # specific and can be re-used in other contexts
        # https://docs.conan.io/en/latest/howtos/cmake_install.html#how-to-reuse-cmake-install-for-package-method
        #cmake.install()  


