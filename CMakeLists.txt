# CMakeList.txt : CMake project for CMaleLibTop, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

# this must be set if you want to compile direct from vstudio
#set(VCPKG_TARGET_TRIPLET x64-windows-static)
#set(VCPKG_OVERLAY_TRIPLETS c:/work/repos/matterfi/VcpkgPortProject/triplets)
#set(VCPKG_FEATURE_FLAGS "registries,manifest")


project ("CMakeTopLib")

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

find_package(cmake-static-lib CONFIG REQUIRED)

# Add source to this project's executable.
add_library(CMakeTopLib src/CMakeTopLib.cpp )
add_library(CMakeTopLib::CMakeTopLib ALIAS CMakeTopLib)

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
