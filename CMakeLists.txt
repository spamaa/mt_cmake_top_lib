# CMakeList.txt : CMake project for CMaleLibTop, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

# TEST_BEGIN
message (STATUS "!!!! Inside cmake-top-lib cmake - BEGIN !!!!")
message (STATUS "!!!! CMAKE_TOOLCHAIN_FILE: '${CMAKE_TOOLCHAIN_FILE}' !!!!")
message (STATUS "!!!! VCPKG_OVERLAY_TRIPLETS: '${VCPKG_OVERLAY_TRIPLETS}' !!!!")
message (STATUS "!!!! VCPKG_TARGET_TRIPLET: '${VCPKG_TARGET_TRIPLET}' !!!!")
message (STATUS "!!!! Inside cmake-top-lib cmake - BEGIN !!!!")
# TEST_END

# check if toolchain file is set
if (NOT DEFINED  CMAKE_TOOLCHAIN_FILE)
    message (FATAL_ERROR "!!!! VCPKG INTEGRATION IS NOT ENABLED !!!!")
else()
    if (NOT EXISTS "${CMAKE_TOOLCHAIN_FILE}")
        message (FATAL_ERROR "!!!! cmake toolchain file does not exists: '${CMAKE_TOOLCHAIN_FILE}' !!!!")
    else()
        message (STATUS "Using cmake toolchain file: '${CMAKE_TOOLCHAIN_FILE}'")
    endif()
endif()

# check if triplets directory exists
if (NOT DEFINED VCPKG_OVERLAY_TRIPLETS)
    message (FATAL_ERROR "!!!! TRIPLET DEFINITION LOCATION IS NOT SPECFIED !!!!")
else()
    if(NOT IS_DIRECTORY "${VCPKG_OVERLAY_TRIPLETS}")
        message (FATAL_ERROR "!!!! triplets directory not exists: '${VCPKG_OVERLAY_TRIPLETS}' !!!!")
    else()
        message (STATUS "Using triplets from: '${VCPKG_OVERLAY_TRIPLETS}'")
    endif()
endif()

# check if triplet is set
if (NOT DEFINED VCPKG_TARGET_TRIPLET)
    message (FATAL_ERROR "!!!! TRIPLET TYPE IS NOT SELECTED !!!!")
else()
    message (STATUS "Using triplet: '${VCPKG_TARGET_TRIPLET}'")
endif()
if (NOT DEFINED VCPKG_FEATURE_FLAGS)
    message (FATAL_ERROR "!!!! VCPKG manifest and register mode is not enabled !!!!")
endif()

project ("CMakeTopLib")

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

find_package(cmake-static-lib CONFIG REQUIRED)

# Add source to this project's executable.
add_library(CMakeTopLib src/CMakeTopLib.cpp )
add_library(CMakeTopLib::CMakeTopLib ALIAS CMakeTopLib)

if (MSVC)
    # enable sanitizer
    if (MSVC_ENABLE_ASAN)
        message (STATUS "Enablling MSVC address sanitizer.")
        target_compile_options(${PROJECT_NAME} PRIVATE
            /fsanitize=address
        )
        target_compile_definitions(${PROJECT_NAME} PUBLIC
            MSVC_ASAN_ENABLED
        )
    else()
        message (STATUS "MSVC address sanitizer is disabled.")
    endif()
endif()

if(BUILD_SHARED_LIBS AND WIN32)
	target_compile_definitions(CMakeTopLib
		PRIVATE "CMAKETOPLIB_EXPORT=__declspec(dllexport)"
		INTERFACE "CMAKETOPLIB_EXPORT=__declspec(dllimport)")
endif()

target_compile_features(CMakeTopLib PUBLIC cxx_std_17)
target_include_directories(CMakeTopLib
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(CMakeTopLib PUBLIC CMakeStaticLib::CMakeStaticLib)

configure_package_config_file(cmake/config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/cmake-top-lib-config.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake-top-lib
	NO_SET_AND_CHECK_MACRO)

target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_INC_DIR})

install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/cmake-top-lib-config.cmake
	DESTINATION
		${CMAKE_INSTALL_DATADIR}/cmake-top-lib)

install(TARGETS CMakeTopLib EXPORT cmake-top-lib-targets)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT cmake-top-lib-targets
	NAMESPACE CMakeTopLib::
	DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake-top-lib)
