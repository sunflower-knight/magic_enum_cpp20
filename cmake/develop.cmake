message(STATUS "-------------DEVELOP SETTING-------------")

# examples
option(BUILD_EXAMPLES "Build examples" ON)
message(STATUS "BUILD_EXAMPLES: ${BUILD_EXAMPLES}")

# unit test
option(BUILD_UNIT_TESTS "Build unit tests" ON)
message(STATUS "BUILD_UNIT_TESTS: ${BUILD_UNIT_TESTS}")
if(BUILD_UNIT_TESTS)
    enable_testing()
endif()

# Enable address sanitizer
option(ENABLE_SANITIZER "Enable sanitizer(Debug+Gcc/Clang/AppleClang)" OFF)
if(ENABLE_SANITIZER AND NOT MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    endif()
endif()

# warning
option(ENABLE_WARNING "Enable warning for all project " OFF)
if(ENABLE_WARNING)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        list(APPEND MSVC_OPTIONS "/W4")
        if(MSVC_VERSION GREATER 1900) # Allow non fatal security warnings for msvc 2015
            list(APPEND MSVC_OPTIONS "/WX")
        endif()
        add_compile_options(MSVC_OPTIONS)
    else()
        add_compile_options(
#                -Wall
#                -Wextra
#                -Wconversion
#                -pedantic-errors
#                -pedantic
#                -Werror
#                -Wfatal-errors
        )
    endif()
endif()
