cmake_minimum_required(VERSION 3.21)
project(Data_structures_Lab4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Data_structures_Lab4
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SMMIterator.cpp
        SMMIterator.h
        SortedMultiMap.cpp
        SortedMultiMap.h)
