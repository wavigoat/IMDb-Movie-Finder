cmake_minimum_required(VERSION 3.27)
project(IMDb-Movie-Finder)

set(CMAKE_CXX_STANDARD 17)

add_executable(IMDb-Movie-Finder main.cpp
        algorithms/nodes.cpp
        algorithms/heap_sort.h
        algorithms/heap_sort.cpp
        algorithms/insertion_sort.h
        algorithms/insertion_sort.cpp
        algorithms/merge_sort.h
        algorithms/merge_sort.cpp
        algorithms/shell_sort.h
        algorithms/shell_sort.cpp
)
