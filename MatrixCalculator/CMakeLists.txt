cmake_minimum_required(VERSION 3.10)
project(MatrixCalculator)

set(mat_lib_src MatricesHolder.cpp Matrix.cpp)
add_library(mat_lib ${mat_lib_src})

add_executable(MatrixCalculator MatrixTest.cpp)
target_link_libraries(MatrixCalculator mat_lib)