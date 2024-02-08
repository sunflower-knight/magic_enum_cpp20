cmake_minimum_required(VERSION 3.15)

project(magic_enum
        VERSION "0.9.5"
        HOMEPAGE_URL "todo"
        DESCRIPTION " Imp for magic enum in c++20 standard; A library that provides static reflection for enums, work with any enum type without any macro or boilerplate code."
        LANGUAGES CXX)

#include(cmake/install.cmake)

if(CMAKE_PROJECT_NAME STREQUAL "magic_enum") # if magic_enum is top-level project
    # add include path
    include_directories(include)
    include(cmake/build.cmake)
    include(cmake/develop.cmake)
    # add subdir for example and test
    add_subdirectory(example)
    add_subdirectory(test)
    add_library(magic_enum INTERFACE)
    target_include_directories(magic_enum INTERFACE include) # #include <magic_enum/magic_enum.hpp>
    target_include_directories(magic_enum INTERFACE include/magic_enum) # #include <magic_enum.hpp>
endif()
