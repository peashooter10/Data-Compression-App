cmake_minimum_required(VERSION 3.7)
project(Decompresor_Huffman)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

add_executable(Decompresor_Huffman
        main.cpp
        Lista.cpp
)