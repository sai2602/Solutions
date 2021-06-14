# CMakeList.txt : CMake project for BIT_VM_Tool, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source to this project's executable.
add_executable (BIT_VM_Tool "main.cpp" "BIT_VM_Tool.h" "BIT_Functions.cpp" "BIT_Functions.h")

# TODO: Add tests and install targets if needed.
