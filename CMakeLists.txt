cmake_minimum_required(VERSION 3.28)

project(sgbd_trabalho1_hashindex)
set(CMAKE_CXX_STANDARD 17)

include_directories(includes)
add_executable(sgbd_trabalho1_hashindex src/main.cpp
        src/hashtable.cpp
        src/bplustree.cpp
        includes/bplustree.h
        includes/linkedinlist.h
        src/linkedinlist.cpp)
