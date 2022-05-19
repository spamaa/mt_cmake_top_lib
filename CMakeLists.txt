# CMakeList.txt : CMake project for CMaleLibTop, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

project ("CMakeTopLib")

# this include must be after project
include ("${VCPKG_INSTALLED_DIR}/${MATTERFI_CMAKE_HOST_TRIPLET}/${MATTERFI_CMAKE_CONFIG_FILE}")

# check if toolchain file is set
matterfi_check_toolchain_file()
matterfi_check_triplet_is_set()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

find_package(cmake-static-lib CONFIG REQUIRED)

# build statdard library version
add_library(CMakeTopLib src/CMakeTopLib.cpp )
add_library(CMakeTopLib::CMakeTopLib ALIAS CMakeTopLib)


matterfi_enable_msvc_asan(CMakeTopLib)

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

target_include_directories(CMakeTopLib PUBLIC ${PUBLIC_INC_DIR})

# build extended library version
add_library(CMakeTopLib-ext src/CMakeTopLib.cpp )
add_library(CMakeTopLib::CMakeTopLib-ext ALIAS CMakeTopLib-ext)

matterfi_enable_msvc_asan(CMakeTopLib-ext)

target_compile_definitions(CMakeTopLib-ext PRIVATE
	CMAKETOPLIB_EXT
)


if(BUILD_SHARED_LIBS AND WIN32)
	target_compile_definitions(CMakeTopLib-ext
		PRIVATE "CMAKETOPLIB_EXPORT=__declspec(dllexport)"
		INTERFACE "CMAKETOPLIB_EXPORT=__declspec(dllimport)")
endif()

target_compile_features(CMakeTopLib-ext PUBLIC cxx_std_17)
target_include_directories(CMakeTopLib-ext
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(CMakeTopLib-ext PUBLIC CMakeStaticLib::CMakeStaticLib)

target_include_directories(CMakeTopLib-ext PUBLIC ${PUBLIC_INC_DIR})

# install
configure_package_config_file(cmake/config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/cmake-top-lib-config.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake-top-lib
	NO_SET_AND_CHECK_MACRO)

install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/cmake-top-lib-config.cmake
	DESTINATION
		${CMAKE_INSTALL_DATADIR}/cmake-top-lib)

install(TARGETS CMakeTopLib EXPORT cmake-top-lib-targets)
install(TARGETS CMakeTopLib-ext EXPORT cmake-top-lib-targets)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT cmake-top-lib-targets
	NAMESPACE CMakeTopLib::
	DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake-top-lib
)

enable_testing()

