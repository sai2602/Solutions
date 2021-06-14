# CMakeList.txt : CMake project for Travelling_Salesman_Problem, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source to this project's executable.
add_executable (Travelling_Salesman_Problem "main.cpp"  "TSP.cpp" "TSP.h" "Default_Defines.h")

# TODO: Add tests and install targets if needed.
