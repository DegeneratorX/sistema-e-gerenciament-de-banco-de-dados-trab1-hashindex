cmake_minimum_required(VERSION 3.28)

project(trabalho_1_hashing)
set(CMAKE_CXX_STANDARD 17)

include_directories(includes)
add_executable(trabalho_1_hashing src/main.cpp
        src/hashtable.cpp)
