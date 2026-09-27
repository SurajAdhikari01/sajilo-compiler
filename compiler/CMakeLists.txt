cmake_minimum_required(VERSION 3.20)
project(sajilo)

include(CTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE compiler_src "${CMAKE_SOURCE_DIR}/src/*.cpp")
list(REMOVE_ITEM compiler_src "${CMAKE_SOURCE_DIR}/src/main.cpp")

add_library(sajilo_compiler STATIC ${compiler_src})
target_include_directories(sajilo_compiler PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(sajilo src/main.cpp)
target_link_libraries(sajilo PRIVATE sajilo_compiler)
install(TARGETS sajilo DESTINATION /usr/local/bin/)

if(BUILD_TESTING)
    add_executable(expression_precedence_test tests/expression_precedence_test.cpp)
    target_link_libraries(expression_precedence_test PRIVATE sajilo_compiler)

    add_test(NAME valid_program
        COMMAND sajilo ${CMAKE_SOURCE_DIR}/tests/data/valid.sajilo
    )
    add_test(NAME syntax_error
        COMMAND sajilo ${CMAKE_SOURCE_DIR}/tests/data/syntax_error.sajilo
    )
    set_tests_properties(syntax_error PROPERTIES WILL_FAIL TRUE)

    add_test(NAME semantic_error
        COMMAND sajilo ${CMAKE_SOURCE_DIR}/tests/data/semantic_error.sajilo
    )
    set_tests_properties(semantic_error PROPERTIES WILL_FAIL TRUE)

    add_test(NAME expression_precedence COMMAND expression_precedence_test)
endif()
