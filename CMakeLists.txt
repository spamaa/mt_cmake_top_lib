# CMakeList.txt : CMake project for CMaleLibTop, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

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

# check if triplet is set
if (NOT DEFINED VCPKG_TARGET_TRIPLET)
    message (FATAL_ERROR "!!!! TRIPLET TYPE IS NOT SELECTED !!!!")
else()
    message (STATUS "Using triplet: '${VCPKG_TARGET_TRIPLET}'")
endif()

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

target_include_directories(CMakeTopLib PUBLIC ${PUBLIC_INC_DIR})

# build msvc with sanitizer lib
if (MSVC)

	# Add source to this project's executable.
	add_library(CMakeTopLib-asan src/CMakeTopLib.cpp )
	add_library(CMakeTopLib::CMakeTopLib-asan ALIAS CMakeTopLib-asan)

	# add sanitizer 
    target_compile_options(CMakeTopLib-asan PRIVATE
        /fsanitize=address
    )
    target_compile_definitions(CMakeTopLib-asan PRIVATE
        MSVC_ASAN_ENABLED
    )

	if(BUILD_SHARED_LIBS AND WIN32)
		target_compile_definitions(CMakeTopLib-asan
			PRIVATE "CMAKETOPLIB_EXPORT=__declspec(dllexport)"
			INTERFACE "CMAKETOPLIB_EXPORT=__declspec(dllimport)")
	endif()

	target_compile_features(CMakeTopLib-asan PUBLIC cxx_std_17)
	target_include_directories(CMakeTopLib-asan
		PUBLIC
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
			$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
	)

	target_link_libraries(CMakeTopLib-asan PUBLIC CMakeStaticLib::CMakeStaticLib)

	target_include_directories(CMakeTopLib-asan PUBLIC ${PUBLIC_INC_DIR})

endif()

install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/cmake-top-lib-config.cmake
	DESTINATION
		${CMAKE_INSTALL_DATADIR}/cmake-top-lib)

install(TARGETS CMakeTopLib EXPORT cmake-top-lib-targets)
if (MSVC)
	install(TARGETS CMakeTopLib-asan EXPORT cmake-top-lib-targets)
endif()

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT cmake-top-lib-targets
	NAMESPACE CMakeTopLib::
	DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake-top-lib)
