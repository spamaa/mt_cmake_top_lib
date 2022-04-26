# CMakeList.txt : CMake project for CMaleLibTop, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CMakeLibTop")

# Add source to this project's executable.
add_library (${PROJECT_NAME} STATIC "CMakeLibTop.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC .)

# TODO: Add tests and install targets if needed.
