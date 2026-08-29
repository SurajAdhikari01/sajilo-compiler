cmake_minimum_required(VERSION 3.20)
project(sajilo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE app_src "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(sajilo ${app_src})

target_include_directories(sajilo PRIVATE ${CMAKE_SOURCE_DIR}/include)
install(TARGETS sajilo DESTINATION /usr/local/bin/)


