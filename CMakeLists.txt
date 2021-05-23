cmake_minimum_required(VERSION 3.16)
project(mivnei_netunim_ex2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(mivnei_netunim_ex2
        AlgorithmsAndMinHeap.h
        Entry.h
        InputOutput.cpp
        InputOutput.h
        main.cpp
        MinHeap.h
        MinHeapADT.h
        my_algorithms.h)
