# CMakeList.txt : CMake project for CMaleLibTop, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

project ("CMakeLibTop")
include(CMakePackageConfigHelpers)

# Add source to this project's executable.
add_library (${PROJECT_NAME} STATIC "CMakeLibTop.cpp" )
add_library(CMakeLibTop::CMakeLibTop ALIAS CMakeLibTop)

set (PUBLIC_INC_DIR include)

target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_INC_DIR})

# TODO: Add tests and install targets if needed.

configure_package_config_file(cmake/config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/CMakeLibTop-config.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/CMakeLibTop
	NO_SET_AND_CHECK_MACRO)


install(TARGETS ${PROJECT_NAME} EXPORT CMakeLibTop-targets)
install(DIRECTORY ${PUBLIC_INC_DIR} DESTINATION ${CMAKE_INSTALL_PREFIX})
install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/CMakeLibTop-config.cmake
	DESTINATION
		${CMAKE_INSTALL_DATADIR}/CMakeLibTop)


message (STATUS "!!!! CMAKE_INSTALL_PREFIX: '${CMAKE_INSTALL_PREFIX}' !!!!")
message (STATUS "!!!! CMAKE_INSTALL_INCLUDEDIR: '${CMAKE_INSTALL_INCLUDEDIR}' !!!!")
message (STATUS "!!!! CMAKE_CURRENT_SOURCE_DIR: '${CMAKE_CURRENT_SOURCE_DIR}' !!!!")
#install(DIRECTORY include  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

