# examples
if(NOT BUILD_EXAMPLES)
    return()
endif()

link_libraries(${CMAKE_PROJECT_NAME})

function(make_example target)
    add_executable(${target} ${target}.cpp)
endfunction()

make_example(example)
make_example(example_custom_name)
