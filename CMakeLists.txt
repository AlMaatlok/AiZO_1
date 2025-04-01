cmake_minimum_required(VERSION 3.30)
project(ahhh)

set(CMAKE_CXX_STANDARD 20)

add_executable(ahhh main.cpp
        utils/FileHandler.cpp
        utils/FileHandler.h
        utils/Timer.cpp
        utils/Timer.h
        sorting_algorithms/InsertionSort.cpp
        sorting_algorithms/InsertionSort.h
        sorting_algorithms/QuickSort.cpp
        sorting_algorithms/QuickSort.h
        sorting_algorithms/HeapSort.cpp
        sorting_algorithms/HeapSort.h
        sorting_algorithms/ShellSort.cpp
        sorting_algorithms/ShellSort.h
        sorting_algorithms/Sort.cpp
        sorting_algorithms/Sort.h
        utils/NumberGenerator.h)
