cmake_minimum_required(VERSION 3.27)
project(IMDb-Movie-Finder)

set(CMAKE_CXX_STANDARD 17)

add_executable(IMDb-Movie-Finder main.cpp
        nodes.cpp
        heap_sort.h
        heap_sort.cpp
        insertion_sort.h
        insertion_sort.cpp
        merge_sort.h
        merge_sort.cpp
        shell_sort.h
        shell_sort.cpp
)
