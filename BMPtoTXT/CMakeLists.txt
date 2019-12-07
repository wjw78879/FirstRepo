cmake_minimum_required(VERSION 3.10)
project(BMPtoTXT)

set(CMAKE_CXX_FLAGS "-g")

set(bmptotxt_lib_src bmpHolder.cpp)
add_library(bmptotxt_lib ${bmptotxt_lib_src})

add_executable(test_bmptotxt test.cpp)
target_link_libraries(test_bmptotxt bmptotxt_lib)