# CMakeList.txt : CMake project for ConnMysqlTest, include source and define
# project specific logic here.
#
project(wormhole-examples)
cmake_minimum_required(VERSION 3.22)
set(CMAKE_VERBOSE_MAKEFILE ON)

include(CheckCXXCompilerFlag)

function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
        unset(flag_supported CACHE)
    endif()
endfunction()

# example usage
enable_cxx_compiler_flag_if_supported("-Wall")
enable_cxx_compiler_flag_if_supported("-Wextra")
enable_cxx_compiler_flag_if_supported("-Werror")
enable_cxx_compiler_flag_if_supported("-pedantic")
enable_cxx_compiler_flag_if_supported("-pedantic-errors")
enable_cxx_compiler_flag_if_supported("-Wno-unused-variable")
enable_cxx_compiler_flag_if_supported("-Wno-unused-parameter")
enable_cxx_compiler_flag_if_supported("-Wno-literal-suffix")

find_package(Boost REQUIRED COMPONENTS headers)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

# Add source to this project's executable.
add_executable (basic-example "basic-example.cpp" )

set_property(TARGET basic-example PROPERTY CXX_STANDARD 23)

target_include_directories(basic-example PRIVATE ../include)

target_link_libraries(basic-example PRIVATE Boost::headers Threads::Threads OpenSSL::Crypto OpenSSL::SSL)
# TODO: Add tests and install targets if needed.
