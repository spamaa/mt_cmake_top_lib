# CMakeList.txt : CMake project for CMaleLibTop, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CMakeLibTop")

# Add source to this project's executable.
add_library (${PROJECT_NAME} STATIC "CMakeLibTop.cpp" )

set (PUBLIC_INC_DIR include)

target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_INC_DIR})

# TODO: Add tests and install targets if needed.


install(TARGETS ${PROJECT_NAME})
install(DIRECTORY ${PUBLIC_INC_DIR} DESTINATION ${CMAKE_INSTALL_PREFIX})

message (STATUS "!!!! CMAKE_INSTALL_PREFIX: '${CMAKE_INSTALL_PREFIX}' !!!!")
message (STATUS "!!!! CMAKE_INSTALL_INCLUDEDIR: '${CMAKE_INSTALL_INCLUDEDIR}' !!!!")
message (STATUS "!!!! CMAKE_CURRENT_SOURCE_DIR: '${CMAKE_CURRENT_SOURCE_DIR}' !!!!")
#install(DIRECTORY include  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

