# extra
option(BUILD_EXAMPLES "Build examples" OFF)
message(STATUS "BUILD_EXAMPLES: ${BUILD_EXAMPLES}")
# unit test
if(NOT BUILD_UNIT_TESTS)
   return()
endif()

include_directories(3rdparty)# doctest
link_libraries(${CMAKE_PROJECT_NAME}) # link interface lib magic-enum

add_executable(test_core test.cpp)
add_test(NAME test_core COMMAND test_core)

function(make_test target)
   add_executable(${target} ${target}.cpp)
   add_test(NAME ${target} COMMAND ${target})
endfunction()

add_executable(crack  crack.cpp)
