from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps

class Recipe(ConanFile):
    requires = ["arrow/21.0.0"]

    generators=[
            "CMakeDeps",
            "CMakeToolchain",
            ]
 
    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    
