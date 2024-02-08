message(STATUS "-------------COMPILE SETTING-------------")

# CPP Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "CXX Standard: ${CMAKE_CXX_STANDARD}")

# keep Compatibility in different compilers
set(CMAKE_CXX_EXTENSIONS OFF)

# Build Type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# libc++ or libstdc++&clang
option(BUILD_WITH_LIBCXX "Build with libc++" OFF)
if(BUILD_WITH_LIBCXX)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_compile_options(-stdlib=libc++)
    else()
        set(BUILD_WITH_LIBCXX "OFF" CACHE FORCE)
        message(FATAL_ERROR "use LIBCXX with Clang together")
    endif()
endif()
message(STATUS "BUILD_WITH_LIBCXX: ${BUILD_WITH_LIBCXX}")

# force use lld if your compiler is clang
option(BUILD_WITH_LLD_LINKER "Build with lld linker with clang" OFF)
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_link_options(-fuse-ld=lld)
endif()

# ccache
option(USE_CCACHE "use ccache to faster compile when develop" OFF)
if(USE_CCACHE)
    find_program(CCACHE_FOUND ccache)
    if(CCACHE_FOUND)
        set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
        set(CMAKE_C_COMPILER_LAUNCHER ccache)
        #set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache) # ccache for link is useless
    else()
        message(WARNING "ccache not found")
    endif()
endif()
message(STATUS "USE_CCACHE: ${USE_CCACHE}")

# see more Information when compile
option(CMAKE_VERBOSE_MAKEFILE "use ccache to faster compile when develop" ON)
#


include(CheckCXXCompilerFlag)

# --------------------- GCC
# report compile time
add_compile_options(-ftime-report)


# --------------------- Clang

# --------------------- Msvc
check_cxx_compiler_flag(/permissive HAS_PERMISSIVE_FLAG)
if(HAS_PERMISSIVE_FLAG)
    set(OPTIONS ${OPTIONS} /permissive-)
endif()
