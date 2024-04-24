cmake_minimum_required(VERSION 3.28)

project(sgbd_trabalho1_hash)
set(CMAKE_CXX_STANDARD 17)

include_directories(includes)
add_executable(sgbd_trabalho1_hash src/main.cpp
        includes/HashTable.h
        src/HashTable.cpp
        includes/Bucket.h
        src/Bucket.cpp
)
