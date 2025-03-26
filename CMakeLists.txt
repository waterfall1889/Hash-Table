cmake_minimum_required(VERSION 3.29)
project(Hash_Table)

set(CMAKE_CXX_STANDARD 20)

add_executable(Hash_Table main.cpp
        Hash.h
        HashTable.h
        HashNode.h
        HashTable.cpp)
