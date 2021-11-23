cmake_minimum_required(VERSION 3.16)
project(edumenagementsys)

set(CMAKE_CXX_STANDARD 14)

add_executable(edumenagementsys main.cpp header_files/helper_functions.h source_files/helper_functions.cpp ./database_class/Database.cpp ./database_class/Database.h)