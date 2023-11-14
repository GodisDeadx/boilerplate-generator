cmake_minimum_required(VERSION 3.10)
project(boilerplate-generator CXX)

add_compile_options(-std=c++17)

# Add source files to the project
add_executable(gen ./src/main.cpp)