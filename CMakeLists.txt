cmake_minimum_required(VERSION 3.10)
project(TiledGemm)

# This tells CMake to find all .cpp files and bundle them into 'main'
add_executable(main main.cpp matrix_math.cpp)